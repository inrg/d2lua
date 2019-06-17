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

#include "ld2api.h"
#include "d2func.h"

LPCWSTR c2w(LPCSTR str);

static int d2_PrintMessageAtTop(lua_State* L) {
    const char* msg = luaL_optstring(L, 1, NULL);
    const char* pos = luaL_optstring(L, 2, "TOP");
    lua_Integer color = luaL_optinteger(L, 3, 0);

    if (msg == NULL) {
        return 0;
    }

    diablo::fnPrintMessageAtTop(c2w(msg), (DWORD)color);
    return 0;
}

LPCWSTR c2w(LPCSTR str)  {
    int length = strlen(str) + 1;
    LPWSTR t = (LPWSTR)malloc(sizeof(WCHAR) * length);

    memset(t, 0, length * sizeof(WCHAR));

    MultiByteToWideChar(CP_ACP, 0, str, strlen(str), t, length);

    return t;
}

LUAMOD_API int luaopen_d2api(lua_State* L) {
    lua_register(L, "PrintMessageAtTop", d2_PrintMessageAtTop);

    return 1;
}

