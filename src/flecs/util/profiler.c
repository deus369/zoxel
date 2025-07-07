void initialize_flecs_profiler(ecs_world_t* world) {
    #ifdef zox_using_profiler
    //zox_log("+ flecs profiler enabled\n")
    zox_import_module(FlecsRest)
    zox_import_module(FlecsMonitor)
    ecs_singleton_set(world, EcsRest, {0});
    // ecs_tracing_enable(1);
    ecs_log_set_level(0);
    ecs_measure_frame_time(world, true);
    ecs_measure_system_time(world, true);
    #endif
}