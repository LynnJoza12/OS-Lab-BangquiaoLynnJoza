#include <stdio.h>
#include <windows.h>

int main() {
    DWORD parentPID = GetCurrentProcessId();
    printf("Parent Process PID: %lu\n", parentPID);
    
    // Prepare command lines for both children
    char commandLine1[256], commandLine2[256];
    sprintf(commandLine1, "child_echo.exe %lu", parentPID);
    sprintf(commandLine2, "child_echo.exe %lu", parentPID);
    
    // Process and startup info for both children
    PROCESS_INFORMATION processInfo1, processInfo2;
    STARTUPINFO startupInfo1, startupInfo2;
    
    // Initialize structures
    ZeroMemory(&processInfo1, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&startupInfo1, sizeof(STARTUPINFO));
    startupInfo1.cb = sizeof(STARTUPINFO);
    
    ZeroMemory(&processInfo2, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&startupInfo2, sizeof(STARTUPINFO));
    startupInfo2.cb = sizeof(STARTUPINFO);
    
    printf("Creating first child process...\n");
    BOOL success1 = CreateProcess(NULL, commandLine1, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo1, &processInfo1);
    
    printf("Creating second child process...\n");
    BOOL success2 = CreateProcess(NULL, commandLine2, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo2, &processInfo2);
    
    if (!success1 || !success2) {
        printf("CreateProcess failed\n");
        return 1;
    }
    
    printf("Both children created successfully!\n");
    printf("Child 1 PID: %lu\n", processInfo1.dwProcessId);
    printf("Child 2 PID: %lu\n", processInfo2.dwProcessId);
    
    // Wait for both children using WaitForMultipleObjects
    HANDLE processes[2] = {processInfo1.hProcess, processInfo2.hProcess};
    printf("Waiting for both children to finish...\n");
    
    WaitForMultipleObjects(2, processes, TRUE, INFINITE);
    
    // Get exit codes
    DWORD exitCode1, exitCode2;
    GetExitCodeProcess(processInfo1.hProcess, &exitCode1);
    GetExitCodeProcess(processInfo2.hProcess, &exitCode2);
    
    printf("Child 1 finished with exit code: %lu\n", exitCode1);
    printf("Child 2 finished with exit code: %lu\n", exitCode2);
    
    // Close handles
    CloseHandle(processInfo1.hProcess);
    CloseHandle(processInfo1.hThread);
    CloseHandle(processInfo2.hProcess);
    CloseHandle(processInfo2.hThread);
    
    return 0;
}