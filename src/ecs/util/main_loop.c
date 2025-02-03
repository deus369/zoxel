// forward declare types
extern byte headless;
extern void iterate_time(ecs_world_t *world);
extern void app_update_gpu(ecs_world_t *world);

void update_core(ecs_world_t *world) {
    run_update_loop(world);
    if (debug_pipelines) ecs_log_set_level(1);    // debug system pipelines
    ecs_progress(world, 0);
    // todo: add run_post_update_loop(world);
    iterate_time(world);
    if (!headless) app_update_gpu(world);
    #ifdef zoxel_log_frame_ms
        zox_log(" > frame time [%fms]\n", (float) (zox_delta_time * 1000.0f))
    #endif
}
