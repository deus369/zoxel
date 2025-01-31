// profiling: make build/dev && make run-dev-profiler
#include "zox/zox.c"
#include zox_nexus_game

int run_main(int argc, char* argv[]) {
    ecs_world_t *world = initialize_ecs(argc, argv);
    if (world == NULL) {
        zox_log(" ! engine failed to start\n")
        return 0;
    } else {
        zox_import_module(Zox)
        #ifdef zox_mod_game
        zox_import_module(ZoxGame)
        #else
        zox_log(" ! game not loaded\n")
        #endif
        if (boot_event(world) == EXIT_SUCCESS) {
            update_zox();
        } else {
            zox_log(" ! booting failed\n")
        }
        dispose_zox(world);
    }
    return 0;
}

#ifndef zoxel_on_windows

int main(int argc, char* argv[]) {
    return run_main(argc, argv);
}

#else

#include "main.windows.c"

#endif