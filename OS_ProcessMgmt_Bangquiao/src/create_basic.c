#include <stdio.h>
#include <windows.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    DWORD parentPID = GetCurrentProcessId();
    printf("Parent: my PID = %lu\n", parentPID);

    char cmdLine[256];
    sprintf(cmdLine, "child_echo.exe %lu", parentPID);

    // Create the child process
    if (!CreateProcess(
            NULL,          // Application name
            cmdLine,       // Command line
            NULL,          // Process security attributes
            NULL,          // Thread security attributes
            FALSE,         // Inherit handles
            0,             // Creation flags
            NULL,          // Use parent's environment
            NULL,          // Use parent's starting directory
            &si,           // Startup info
            &pi)) {        // Process info
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return 1;
    }

    // Wait for child to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);
    printf("Parent: child exited with code %lu\n", exitCode);

    // Close handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
