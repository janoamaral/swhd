typedef struct {
    unsigned int mod;
    unsigned int key;
    const char* path;
} Key;

const int MOD_NOREPEAT = 0x4000;

const int VK_A = 0x41;
const int VK_B = 0x42;
const int VK_C = 0x43;

static const Key keys[] = {
    /* modifier/s           key         function                     */
    {MOD_WIN,               VK_F2,      "C:\\Windows\\notepad.exe"    },
    {MOD_WIN | MOD_ALT,     VK_C,       "C:\\Windows\\write.exe",     }
};
