void initialize_threads(ecs_world_t* world) {
    zox_logv("Setting Threads [%i]", use_cores);
    if (use_cores > 1 && is_multithreading) {
        ecs_set_threads(world, use_cores);
    } else {
        zox_log("# warning, single threads set");
        ecs_set_threads(world, 0);
    }
}

void initialize_ecs_settings(
    ecs_world_t *world,
    float fps
) {
    initialize_threads(world);
    initialize_flecs_profiler(world);
    ecs_set_target_fps(world, fps);
}