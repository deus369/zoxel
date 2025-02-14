void update_ecs() {
    run_update_loop(world);
    if (debug_pipelines) {
        ecs_log_set_level(1);
    }
    ecs_progress(world, 0);
    run_post_update_loop(world);
}