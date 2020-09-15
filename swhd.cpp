#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <winuser.h>
#include "swhd.h"
#include "config.h"

void RegisterKeys() {
    for (int i = 0; i < sizeof(keys)/sizeof(*keys); i++  ) {
        RegisterHotKey(NULL,1,keys[i].mod, keys[i].key);
    }
}

void UnregisterKeys() {
    for (int i = 0; i < sizeof(keys)/sizeof(*keys); i++  ) {
        UnregisterHotKey(NULL, i);
    }
}

void RunKey(int message) {
    for (int i = 0; i < sizeof(keys)/sizeof(*keys); i++  ) {
        int mMod = message&0xFFFF;
        int mKey = message>>16;

        if ((mMod ==  keys[i].mod) && (mKey == keys[i].key)) {
            // additional information
            STARTUPINFOA si;
            PROCESS_INFORMATION pi;

            // set the size of the structures
            ZeroMemory(&si, sizeof(si));
            si.cb = sizeof(si);
            ZeroMemory(&pi, sizeof(pi));

            // start the program up
            CreateProcessA
            (
                keys[i].path,           // the path
                NULL,                   // Command line
                NULL,                   // Process handle not inheritable
                NULL,                   // Thread handle not inheritable
                FALSE,                  // Set handle inheritance to FALSE
                CREATE_NEW_CONSOLE,     // Opens file in a separate console
                NULL,                   // Use parent's environment block
                NULL,                   // Use parent's starting directory
                &si,                    // Pointer to STARTUPINFO structure
                &pi                     // Pointer to PROCESS_INFORMATION structure
            );
            // Close process and thread handles.
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            break;
        }
    }
}