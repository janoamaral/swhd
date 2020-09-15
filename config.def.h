typedef struct {
    unsigned int mod;           // Modifier
    unsigned int key;           // Virtual key
    unsigned int iFunction;     // internal function ID
    const char*  path;          // full program path
} Key;

const int MOD_NOREPEAT = 0x4000;

// KEY VALUES
const int VK_A = 0x41;
const int VK_B = 0x42;
const int VK_C = 0x43;

// CUSTOM FUNCTION ID
const unsigned int FUNCTION_RELOAD = 1;


// HOTKEY DECLARATION
static const Key keys[] = {
    /* modifier/s           key     internal function   program path                 */
    {MOD_WIN,               VK_F2,  NULL,               "C:\\Windows\\notepad.exe"    },
    {MOD_WIN,               VK_F12, FUNCTION_RELOAD,    NULL                          },
    {MOD_WIN | MOD_ALT,     VK_C,   NULL,               "C:\\Windows\\write.exe",     }
};
