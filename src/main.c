// profiling: make build/dev && make run-dev-profiler
#include "_includes.c"
#include "zox/zox.c"
#include zox_nexus_game

int run_main(int argc, char* argv[]) {
    int didFail = process_arguments(argc, argv);
    if (didFail == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }
    fetch_pc_info();
    ecs_world_t *world = initialize_ecs(argc, argv, cpu_core_count);
    if (world == NULL) {
        zox_log(" ! engine failed to start\n")
        return EXIT_FAILURE;
    } else {
        zox_import_module(Zox)
        #ifdef zox_mod_game
        zox_import_module(ZoxGame)
        #else
        zox_log(" ! game not loaded\n")
        #endif
        if (boot_event(world) == EXIT_SUCCESS) {
            engine_loop();
        } else {
            zox_log(" ! booting failed\n")
        }
        dispose_zox(world);
    }
    return EXIT_SUCCESS;
}

#ifndef zoxel_on_windows

int main(int argc, char* argv[]) {
    return run_main(argc, argv);
}

#else

#include "main.windows.c"

#endif