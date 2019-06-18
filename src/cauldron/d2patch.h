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

#ifndef __CAULDRON_D2PATCH_H__
#define __CAULDRON_D2PATCH_H__

#include <Windows.h>

#define D2PATCH_CALL 0x01
#define D2PATCH_JMP 0x02
#define D2PATCH_FILL 0x03
#define D2PATCH_VALUE 0x04

#define INST_NOP 0x90
#define INST_CALL 0xE8

namespace diablo {
    typedef struct {
        int type;
        DWORD addr;
        DWORD stub;
        BYTE length;
        DWORD mask;
        BYTE* backup;
    } D2Patch;

    extern D2Patch patches[];

    BOOL InstallPatches(void);
    BOOL UninstallPatches(void);
}

#endif // __CAULDRON_D2PATCH_H__