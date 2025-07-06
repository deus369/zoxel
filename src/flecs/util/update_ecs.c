uint ecs_run_count = 0;

void update_ecs(ecs_world_t *world) {
    run_update_loop(world);
    if (debug_pipelines) {
        ecs_log_set_level(1);
    }
    ecs_progress(world, 0);
    run_post_update_loop(world);
    ecs_run_count++;
}

void update_ecs_local() {
    update_ecs(local_world);
}