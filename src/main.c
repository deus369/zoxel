// profiling: make build/dev && make run-dev-profiler
// #include "core/ecs/util/profiler_defines.c"
#include "core/util/settings/build_settings.c"
#include "core/util/settings/build_disables.c"
#include "zox/zox.c"
#ifdef zox_game_zoxel2D
    #include "nexus/zoxel2D/zoxel2D.c"
#else
    #include "nexus/zoxel/zoxel.c"
#endif

#ifdef zoxel_on_windows
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    int argc = 0;
    char** argv = NULL;
#else
int main(int argc, char* argv[]) {
#endif
    if (engine_begin(argc, argv) == EXIT_SUCCESS) {
        zox_import_module(Zox)
#ifdef zox_game_zoxel2D
        zox_import_module(Zoxel2D)
#else
        zox_import_module(Zoxel)
#endif
        spawn_prefabs_engine(world);    // spawn all our prefabs
        unsigned char result = boot_event(world);
        if (result == EXIT_SUCCESS) engine_loop();
        else zox_logg(" ! booting zoxel failed\n")
        dispose_zox(world);
    } else zox_logg(" ! engine failed to start\n")
    return 0;
}
