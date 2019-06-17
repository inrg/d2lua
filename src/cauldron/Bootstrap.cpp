/*
 * Copyright (C) 2019 HE Yaowen <he.yaowen@hotmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <exception>
#include "Bootstrap.h"
#include "../../dep/inih/cpp/INIReader.h"
#include "lua.hpp"
#include "ld2api.h"

using namespace cauldron;

Bootstrap* Bootstrap::_instance = NULL;
lua_State* L;

Bootstrap* Bootstrap::getInstance(void) {
    if (_instance == NULL) {
        _instance = new Bootstrap();
    }

    return _instance;
}

void Bootstrap::init(HMODULE hModule) {
    INIReader* ini;
    TCHAR path[MAX_PATH];

    if (_status != bsNotInitialized) {
        throw std::exception("Cauldron already initialized.");
    }

    if (!::GetModuleFileName(hModule, path, MAX_PATH)) {
        throw std::exception("Cannot get filename of cauldron module.");
    }

    module = hModule;
    dllName = std::string(path);
    basePath = dllName.substr(0, dllName.find_last_of('\\'));

    ini = new INIReader(basePath + "\\cauldron.ini");

    config.logging_filename = ini->Get("logging", "filename", basePath + "\\cauldron.log");
    config.logging_level = LogLevel(ini->GetInteger("logging", "level", llInfo));
    config.lua_entryfile = ini->Get("lua", "entryfile", basePath + "\\main.lua");

    delete ini;

    logger = new Logger(config.logging_filename, config.logging_level);

    L = luaL_newstate();
    luaL_openlibs(L);
    luaopen_d2api(L);

    _status = bsUnloaded;

    logger->info("Cauldron initialized.");
} 

void Bootstrap::load(void) {
    switch (_status) {
    case bsNotInitialized:
        throw std::exception("Cauldron not initialized yet.");
        break;
    case bsLoaded:
        throw std::exception("Cauldron already loaded.");
        break;
    }

    logger->info("Cauldron loading.");

    if (luaL_dofile(L, config.lua_entryfile.c_str()) != 0) {
        throw std::exception(("Execute Lua file '" + config.lua_entryfile + "':" + std::string(lua_tostring(L, -1))).c_str());
    }

    _status = bsLoaded;

    logger->info("Cauldron loaded.");
}

void Bootstrap::unload(void) {
    logger->info("Cauldron unloading.");

    _status = bsUnloaded;

    logger->info("Cauldron unloaded.");
}

Bootstrap::Bootstrap(void) {
}
