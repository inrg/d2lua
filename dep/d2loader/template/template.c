/*
 *	Copyright (C) 2001 Onlyer (onlyer@263.net)
 *
 *	d2loader plugin template
 *
 */
#include <windows.h>

#include <plugin.h>

PLUGIN_INTERFACE 	Interface;
DWORD	__stdcall 	PluginEntry(DWORD dwReason, LPVOID lpData);

LPPLUGIN_INTERFACE __stdcall QueryInterface(VOID)
{
	Interface.dwMagicword=PLUGIN_MAGICWORD;
	Interface.dwVersion=PLUGIN_VERSION;
	Interface.szDescription="Your description here";
	Interface.fpEntry=PluginEntry;
	return &Interface;
}

DWORD	__stdcall PluginEntry(DWORD dwReason, LPVOID lpData)
{

	LPPLUGIN_DATA_INIT	lpDataInit;
	LPD2PARAM		lpD2Param;

	switch (dwReason) {
		case REASON_INIT:
			lpDataInit=(LPPLUGIN_DATA_INIT)lpData;
			break;

		case REASON_CLEANUP:
			lpD2Param=(LPD2PARAM)lpData;
			break;
			
		default:
		/* for other reasons, you should use & to test if 
		   certain flag is set.
		   e.g: if (dwReason & REASON_ENTER_GAME) {} */
		/*
		case REASON_ENTER_GAME:
		case REASON_ENTER_CHANNEL:
		case REASON_ENTER_MAIN_MENU:
		case REASON_LEAVE_GAME:
		case REASON_LEAVE_CHANNEL:
		case REASON_LEAVE_MAIN_MENU:
			lpD2Param=(LPD2PARAM)lpData;
			break;
		*/
			break;
	}
	return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hDll,DWORD dwReason,LPVOID lpReserved)
{
	switch (dwReason) {
		case DLL_PROCESS_ATTACH:
		case DLL_PROCESS_DETACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		default:
			break;
	}
	return TRUE;
}
