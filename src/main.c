// profiling: make build/dev && make run-dev-profiler
#include "zox/zox.c"
#include zox_nexus_game

#ifdef zoxel_on_windows
#include <windows.h>
#include <shellapi.h>
#define max_args 64
#define max_arg_len 256

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // int argc = 0;
    //char** argv = NULL;
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
#else
int main(int argc, char* argv[]) {
#endif
    ecs_world_t *world = initialize_ecs(argc, argv);
    if (world == NULL) {
        zox_log(" ! engine failed to start\n")
        return 0;
    }
    zox_import_module(Zox)
#ifdef zox_mod_game
    zox_import_module(ZoxGame)
#else
    zox_log(" ! game not loaded\n")
#endif
    if (boot_event(world) == EXIT_SUCCESS) update_zox();
    else zox_log(" ! booting failed\n")
    dispose_zox(world);
    return 0;
}
