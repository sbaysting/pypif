#include "open_process.h"

#include <stdio.h>
#include <tchar.h>
#include <psapi.h>


int compare_process_name( DWORD processID, char* name )
{
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    // Get a handle to the process.
    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, processID );

    // Get the process name.
    if (NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), 
             &cbNeeded) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName, 
                               sizeof(szProcessName)/sizeof(TCHAR) );
        }
    }

    // Compare the process names
    int result = 0;
    if(strcmp(szProcessName, name) == 0)
	    result = 1;

    // Release the handle to the process.
    CloseHandle( hProcess );

    // Return result
    return result;
}


int find_process_id(char* name)
{
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
	{
		return 1;
	}

	// Calculate how many process identifiers were returned.
	cProcesses = cbNeeded / sizeof(DWORD);

	// Check each running process for a matching name
	for ( i = 0; i < cProcesses; i++ )
	{
		if( aProcesses[i] != 0 )
		{
			if(compare_process_name( aProcesses[i], name ) == 1)
				return aProcesses[i];
		}
	}

	return -1;
}
