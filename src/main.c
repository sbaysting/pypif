#include <stdio.h>
#include "open_process.h"

int main(int argc, char** argv)
{
	// Find the first process ID associated with a name
	int proc_id;
	if(argc > 1)
		proc_id = find_process_id(argv[1]);
	else
		proc_id = find_process_id("chrome.exe");
	printf("Found proc ID: %i\n", proc_id);

	// Get a handle to that process
	HANDLE proc = OpenProcess( PROCESS_CREATE_THREAD | PROCESS_VM_WRITE | PROCESS_SUSPEND_RESUME, FALSE, proc_id);
	if(proc == NULL)
		printf("Could not get handle to process!\n");
		return 1;
	else
		printf("Got handle to process!\n");

	// Do something
	

	// Close handle to that process
	CloseHandle(proc);

	// Exit
	return 0;
}
