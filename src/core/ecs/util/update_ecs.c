void update_ecs() {
    #ifdef zoxel_time_main_loop
    begin_timing_absolute()
    #endif
    run_update_loop(world);
    if (debug_pipelines) ecs_log_set_level(1);    // debug system pipelines
    ecs_progress(world, 0);
    run_post_update_loop(world);
    #ifdef zoxel_time_main_loop
    end_timing_cutoff(" - engine update lagged", zoxel_time_main_loop_cutoff)
    #endif
}