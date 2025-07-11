// profiling: make build/dev && make run-dev-profiler
#include "_.c"
#include "zox/zox.c"
#include zox_nexus_game

int run_main(int argc, char* argv[]) {
    #ifndef zox_mod_game
        zox_log(" ! game not loaded")
        return EXIT_FAILURE;
    #endif
    fetch_pc_info();
    ecs_world_t *world = initialize_ecs(argc, argv, cpu_core_count);
    if (world == NULL) {
        zox_log(" ! ecs failed to initialize.")
        return EXIT_FAILURE;
    }
    zox_import_module(Zox)
    zox_import_module(ZoxGame)
    initialize_ecs_settings(world);
    run_hook_terminal_command(world, argv, argc);
    // todo: pre boot event hook here for loading I/O
    if (!headless && engine_spawn_window(world) == EXIT_SUCCESS) {
        if (boot_event(world) == EXIT_SUCCESS) {
            engine_loop(world);
        } else {
            zox_log("! [boot_event] failed")
        }
    } else {
        zox_log("! [engine_spawn_window] failed")
    }
    dispose_zox(world);
    return EXIT_SUCCESS;
}

#ifndef zoxel_on_windows
    int main(int argc, char* argv[]) {
        return run_main(argc, argv);
    }
#else
    #include "main.windows.c"
#endif
