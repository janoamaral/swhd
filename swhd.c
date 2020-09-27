#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <winuser.h>
#include "swhd.h"
#include "config.h"
#include "custcntl.h"

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

void ReloadKeys() {
    UnregisterKeys();
    RegisterKeys();
}

void KillDaemon() {
    UnregisterKeys();
    PostQuitMessage (0);
}

void RunKey(int message) {
    int mMod = message&0xFFFF;
    int mKey = message>>16;

    for (int i = 0; i < sizeof(keys)/sizeof(*keys); i++  ) {
        // Lookup for keys
        if ((mMod ==  keys[i].mod) && (mKey == keys[i].key)) {

            if (keys[i].iFunction == FUNCTION_CLOSE) {
                KillDaemon();
                break;
            }

            if (keys[i].iFunction == FUNCTION_RELOAD) {
                ReloadKeys();
                break;
            }

            // Default program execution
            RunCommand(keys[i].path);
            break;
        }
    }
}
