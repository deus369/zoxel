int engine_begin(int argc, char* argv[]) {
    clear_zoxel_log();
    intialize_game_store();
    return begin_core(argc, argv);
}

void engine_update() {
#ifdef zoxel_time_main_loop
    begin_timing_absolute()
#endif
    update_core(world);
    update_inner_core(world);
#ifdef zoxel_time_main_loop
    end_timing_cutoff(" - engine update lagged", zoxel_time_main_loop_cutoff)
#endif
}
