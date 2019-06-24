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

#include "d2dllbase_10010.h"
#include "d2patch.h"
#include "d2callback.h"

void __declspec(naked) GameLoopStart_STUB(void) {
    __asm {
        pop eax
        sub esp, 0x24
        push edi
        mov edi, ecx
        push eax
        jmp diablo::cbGameLoopStart
    }
}

void __declspec(naked) GameLoopEnd_STUB(void) {
    __asm {
        call diablo::cbGameLoopEnd

        // original codes
        mov ecx, 0xB4
        ret
    }
}

diablo::D2Patch diablo::patches[] = {
    { D2PATCH_CALL, DLLBASE_D2CLIENT + 0x9640, (DWORD)GameLoopStart_STUB, 6, -1 },
    { D2PATCH_CALL, DLLBASE_D2CLIENT + 0xB528, (DWORD)GameLoopEnd_STUB, 5, -1 },
    { 0 }
};
