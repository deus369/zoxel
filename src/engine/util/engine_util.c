int engine_begin(int argc, char* argv[]) {
    clear_zoxel_log();
    return begin_core(argc, argv);
}

void on_engine_end(ecs_world_t *world) {
    /*const Children *font_children = ecs_get(world, font_style_entity, Children);
    for (int i = 0; i < font_children->length; i++) zox_delete(font_children->value[i])
    zox_delete(font_style_entity)*/
    close_core();
    #ifdef zoxel_voxels
        dispose_vox_files();
    #endif
}

void engine_update() {
    #ifdef zoxel_time_main_loop
        begin_timing_absolute()
    #endif
    update_core();
    #ifdef zoxel_time_main_loop
        end_timing_cutoff(" - engine update lagged", zoxel_time_main_loop_cutoff)
    #endif
}