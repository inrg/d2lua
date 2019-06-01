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

#include "Bootstrap.h"
#include "../../dep/inih/cpp/INIReader.h"

using namespace cauldron;

Bootstrap* Bootstrap::_instance = NULL;

Bootstrap* Bootstrap::getInstance(void) {
    if (_instance == NULL) {
        _instance = new Bootstrap();
    }

    return _instance;
}

void Bootstrap::load(HMODULE hModule) {
    INIReader* ini;
    TCHAR path[MAX_PATH];

    if (!::GetModuleFileName(hModule, path, MAX_PATH)) {
        throw std::exception("Cannot get filename of cauldron module.");
    }

    module = hModule;
    dllName = std::string(path);
    basePath = dllName.substr(0, dllName.find_last_of('\\'));

    ini = new INIReader(basePath + "\\cauldron.ini");

    config.logging_filename = ini->Get("logging", "filename", basePath + "\\cauldron.log");
    config.logging_level = LogLevel(ini->GetInteger("logging", "level", llInfo));

    delete ini;

    logger = new Logger(config.logging_filename, config.logging_level);

    logger->info("Cauldron loaded.");
} 

void Bootstrap::unload(void) {
    logger->info("Cauldron unloaded.");
}

Bootstrap::Bootstrap(void) {
}
