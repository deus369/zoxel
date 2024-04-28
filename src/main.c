// profiling: make build/dev && make run-dev-profiler
// #include "core/ecs/util/profiler_defines.c"
#include "zox/zox.c"

#ifdef zoxel_on_windows
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    int argc = 0;
    char** argv = NULL;
#else
int main(int argc, char* argv[]) {
#endif
    if (engine_begin(argc, argv) == EXIT_SUCCESS) {
        zox_import_module(Zox)
        zox_import_game_module();
        spawn_prefabs_engine(world);    // spawn all our prefabs
        unsigned char result = boot_event(world);
        if (result == EXIT_SUCCESS) engine_loop();
        else zox_logg(" ! booting zoxel failed\n")
        dispose_zox(world);
    } else zox_logg(" ! engine failed to start\n")
    return 0;
}
