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

#include "d2callback.h"
#include "Bootstrap.h"
#include "lua.hpp"

using namespace diablo;

BOOL m_GameInit = FALSE;
cauldron::Bootstrap* m_bootstrap = cauldron::Bootstrap::getInstance();

void diablo::cbGameLoopStart(void) {

	if (!m_GameInit) {
		m_GameInit = TRUE;

        if (lua_getglobal(m_bootstrap->L, "__OnGameJoin") && lua_pcall(m_bootstrap->L, 0, 0, 0) != 0) {
            // TODO Failed on calling 'OnGameJoin'
        }
	}
}

void diablo::cbGameLoopEnd(void) {
    m_GameInit = FALSE;

    if (lua_getglobal(m_bootstrap->L, "__OnGameLeave") && lua_pcall(m_bootstrap->L, 0, 0, 0) != 0) {
        // TODO Failed on calling 'OnGameLeave'
    }
}
