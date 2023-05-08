int engine_begin(int argc, char* argv[]) {
    clear_zoxel_log();
    return begin_core(argc, argv);
}

void engine_end() {
    zoxel_log(" > ending zoxel_engine\n");
    close_core();
    #ifdef zoxel_voxels
        dispose_vox_files();
    #endif
}

void engine_update() {
    #ifdef zoxel_time_main_loop
        begin_timing()
    #endif
    update_core();
    #ifdef zoxel_time_main_loop
        did_do_timing()
        end_timing_cutoff(" - engine update lagged", zoxel_time_main_loop_cutoff)
    #endif
}