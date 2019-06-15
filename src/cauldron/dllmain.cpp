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

#include <Windows.h>
#include <exception>
#include "Bootstrap.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    static cauldron::Bootstrap* bootstrap = cauldron::Bootstrap::getInstance();

    try {
        switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            ::DisableThreadLibraryCalls(hinstDLL);
            bootstrap->init(hinstDLL);
            bootstrap->load();

            break;

        case DLL_PROCESS_DETACH:
            // If process is terminating
            if (!lpvReserved) {
                bootstrap->unload();
            }

            break;
        }
    }
    catch (const std::exception& e) {
        bootstrap->logger->error(std::string(e.what()));

        MessageBox(NULL, "Error occurred during runtime, see log files for details.", "Cauldron", 0);
        return FALSE;
    }

    return TRUE;
}

// From d2loader plugin SDK
#include "../../dep/d2loader/plugin.h"

DWORD __stdcall PluginEntry(DWORD dwReason, LPVOID pData) {
    return TRUE;
}

// NOTE: needs to be exported
LPPLUGIN_INTERFACE __stdcall QueryInterface() {
    static PLUGIN_INTERFACE Interface = { PLUGIN_MAGICWORD, PLUGIN_VERSION, "CAULDRON", PluginEntry };
    return &Interface;
}
