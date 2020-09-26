#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <winuser.h>

void RunCommand(char* command) {
    // additional information
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    // set the size of the structures
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // start the program up
    if ( !CreateProcessA
    (
        NULL,                   // No module name (use command line)
        command,                // Command line
        NULL,                   // Process handle not inheritable
        NULL,                   // Thread handle not inheritable
        FALSE,                  // Set handle inheritance to FALSE
        0,                      // No creation flags
        NULL,                   // Use parent's environment block
        NULL,                   // Use parent's starting directory
        &si,                    // Pointer to STARTUPINFO structure
        &pi)                    // Pointer to PROCESS_INFORMATION structure
    )
    {
        printf("Cannot run");
    }

    // Close process and thread handles.
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}


void SearchSelected()
{
    // This structure will be used to create the keyboard
    // input event.
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    // Pause for 250 milliseconds.
    Sleep(200);


    // Press the "Ctrl" key
    ip.ki.wVk = VK_CONTROL;
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));

    // Press the "C" key
    ip.ki.wVk = 'C';
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));

    // Release the "C" key
    ip.ki.wVk = 'C';
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));

    // Release the "Ctrl" key
    ip.ki.wVk = VK_CONTROL;
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));

    HANDLE h;
    Sleep(200);
    if (!OpenClipboard(NULL))
    printf("Fail to open the clipboard");

    h = GetClipboardData(CF_TEXT);

    CloseClipboard();

    const char* PREFIX = "C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe \"https://duckduckgo.com/?q=";
    const char* POSTFIX = "&t=canonical&ia=web\"";

    int size = strlen(PREFIX) + strlen(h) + strlen(POSTFIX) + 1;
    char *str = malloc(size);
    strcpy (str, PREFIX);
    strcat (str, h);
    strcat (str, POSTFIX);

    printf("%s\n", (char *)str);

    RunCommand(str);
}

