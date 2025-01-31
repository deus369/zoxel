#ifdef zoxel_on_windows

#define max_args 64
#define max_arg_len 256
#include <windows.h>
#include <shellapi.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    int argc = 0;
    wchar_t** argvW = CommandLineToArgvW(GetCommandLineW(), &argc);
    // Array to hold arguments
    static char argv_storage[max_args][max_arg_len];
    static char* argv[max_args];
    for (int i = 0; i < argc && i < max_args; i++) {
        // Convert wide char string to char string
        wcstombs(argv_storage[i], argvW[i], max_arg_len);
        argv_storage[i][max_arg_len - 1] = '\0'; // Ensure null termination
        argv[i] = argv_storage[i];
    }
    LocalFree(argvW); // Free memory allocated by CommandLineToArgvW
    return run_main(argc, argv);
}

#endif