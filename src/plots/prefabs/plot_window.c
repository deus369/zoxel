ecs_entity_t spawn_prefab_frame_debugger_ui(ecs_world_t *world) {
    zox_prefab_child(prefab_window)
    zox_prefab_name("prefab_frame_debugger_ui")
    zox_add_tag(e, IgnoreWindowLayering)
    zox_prefab_add(e, PlotDataDouble)
    zox_get_muter(e, PlotDataDouble, data)
    resize_memory_component(PlotDataDouble, data, double, record_frames_count)
    for (int i = 0; i < record_frames_count; i++) data->value[i] = 0;
    prefab_frame_debugger_ui = e;
    return e;
}