void update_core(ecs_world_t *world) {
    run_update_loop(world);
    if (debug_pipelines) ecs_log_set_level(1);    // debug system pipelines
    ecs_progress(world, 0);
    run_post_update_loop(world);
}