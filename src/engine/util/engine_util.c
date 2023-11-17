int engine_begin(int argc, char* argv[]) {
    clear_zoxel_log();
    return begin_core(argc, argv);
}

void on_engine_end(ecs_world_t *world) {
    close_module_core(world);
#ifdef zoxel_voxels
    dispose_vox_files();
#endif
}

void engine_update() {
#ifdef zoxel_time_main_loop
    begin_timing_absolute()
#endif
    update_core(world);
#ifdef zoxel_time_main_loop
    end_timing_cutoff(" - engine update lagged", zoxel_time_main_loop_cutoff)
#endif
}
