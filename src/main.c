// profiling: make build/dev && make run-dev-profiler
// #include "core/util/ecs/util/profiler_defines.c"
#include "zoxel/settings/build_settings.c"
#include "engine/engine.c"
#include "zoxel/zoxel.c"

#ifdef zoxel_on_android
    #include <android/log.h>
    #define APPNAME "Zoxel"
#endif

#ifdef zoxel_on_windows
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    int argc = 0;
    char** argv = NULL;
#else
int main(int argc, char* argv[]) {
#endif
    if (engine_begin(argc, argv) == EXIT_SUCCESS) {
        zox_import_module(Zoxel)        // define our components and systems
        spawn_prefabs_engine(world);    // spawn all our prefabs
        if (boot_zoxel_game(world) == EXIT_SUCCESS) {
            engine_loop();
        } else {
            zoxel_log(" ! booting zoxel failed\n");
        }
        engine_end();
    } else {
        zoxel_log(" ! engine failed to start\n");
    }
    return 0;
}