#include <stdio.h>
#include <windows.h>

int main(int argc, char *argv[]) {
    DWORD myPID = GetCurrentProcessId();

    if (argc < 2) {
        printf("Usage: child_echo <parentPID>\n");
        return 1;
    }

    printf("Child: my PID = %lu, parent PID = %s\n", myPID, argv[1]);


    Sleep(100000);

    return 0;
}
