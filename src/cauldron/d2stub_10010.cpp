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
#include "Bootstrap.h"

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

void __declspec(naked) KeyDown_STUB(void) {
    __asm {
        //edi = ptr to (hwnd, msg, wparam, lparam)
        mov cl, [edi + 0x08] //nVirtKey (wparam)
        mov dl, [edi + 0x0c + 3] //lKeyData (lparam)
        and dl, 0x40 //bit 30 of lKeyData (lparam)
        call diablo::cbKeyDown

        //original code
        test byte ptr[edi + 0x0c + 3], 0x40 //bit 30 of lKeyData (lparam)
        ret
    }
}

void __declspec(naked) GamePacketReceived_STUB() {
    __asm {
        // original code
        and ebx, 0xFF;
        lea edx, [ebx + ebx * 2];
        pushad;

        // Call our clean c function
        mov edx, ecx;
        mov ecx, ebp;
        call diablo::cbGamePacketReceived;

        // Return to game
        popad;
        add dword ptr[esp], 4;
        ret;
    }
}

diablo::D2Patch diablo::patches[] = {
    { D2PATCH_CALL, DLLBASE_D2CLIENT + 0x9640, (DWORD)GameLoopStart_STUB, 6, -1 },
    { D2PATCH_CALL, DLLBASE_D2CLIENT + 0xB528, (DWORD)GameLoopEnd_STUB, 5, -1 },
    { D2PATCH_CALL, DLLBASE_D2CLIENT + 0x35A07, (DWORD)KeyDown_STUB, 7, -1 },
    { D2PATCH_CALL, DLLBASE_D2CLIENT + 0x1511A, (DWORD)GamePacketReceived_STUB, 9, -1 },
    { 0 }
};
