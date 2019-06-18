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

#include "d2patch.h"

static void WriteLocalMemory(DWORD addr, LPVOID buf, int len) {
    DWORD prot;

    ::VirtualProtect((void*)addr, len, PAGE_EXECUTE_READWRITE, &prot);
    ::WriteProcessMemory(::GetCurrentProcess(), (void*)addr, buf, len, 0);
    ::VirtualProtect((void*)addr, len, prot, &prot);
}

static void ReadLocalMemory(DWORD addr, void *buf, int len) {
    ::ReadProcessMemory(::GetCurrentProcess(), (void *)addr, buf, len, 0);
}

static void PatchIntercepter(BYTE inst, DWORD oldEntry, DWORD newEntry, int length) {
    BYTE* buffer = (BYTE*)malloc(sizeof(BYTE) * length);
    newEntry -= (oldEntry + 5);

    buffer[0] = inst;
    *(DWORD*)(buffer + 1) = newEntry;

    memset(buffer + 5, INST_NOP, length - 5);
    WriteLocalMemory(oldEntry, buffer, length);
    free(buffer);
}

BOOL diablo::InstallPatches(void) {
    diablo::D2Patch* patch;

    for (patch = diablo::patches; patch->type != 0; patch++) {
        patch->backup = new BYTE[patch->length];
        ReadLocalMemory(patch->addr, patch->backup, patch->length);

        switch (patch->type) {
        case D2PATCH_CALL:
            PatchIntercepter(INST_CALL, patch->addr, patch->stub, patch->length);
        }
    }

    return TRUE;
}

BOOL diablo::UninstallPatches(void) {
    return TRUE;
}