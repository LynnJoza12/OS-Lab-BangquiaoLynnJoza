#include <stdio.h>
#include <windows.h>

int main() {
    DWORD parentPID = GetCurrentProcessId();
    printf("Parent Process PID: %lu\n", parentPID);
    printf("Parent is about to spawn 'cmd /c dir' and exit with same code...\n");
    
    // Command to execute
    char commandLine[] = "cmd /c dir";
    
    PROCESS_INFORMATION processInfo;
    STARTUPINFO startupInfo;
    
    ZeroMemory(&processInfo, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
    startupInfo.cb = sizeof(STARTUPINFO);
    
    printf("Creating process: %s\n", commandLine);
    BOOL success = CreateProcess(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo);
    
    if (!success) {
        printf("CreateProcess failed (%lu)\n", GetLastError());
        return 1;
    }
    
    printf("Process created with PID: %lu\n", processInfo.dwProcessId);
    printf("Parent waiting for child to complete...\n");
    
    // Wait for the spawned process
    WaitForSingleObject(processInfo.hProcess, INFINITE);
    
    // Get the exit code of the spawned process
    DWORD childExitCode;
    GetExitCodeProcess(processInfo.hProcess, &childExitCode);
    
    printf("Child process finished with exit code: %lu\n", childExitCode);
    printf("Parent exiting with same code: %lu\n", childExitCode);
    
    // Close handles
    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);
    
    // Exit with the same code as the spawned process
    return childExitCode;
}