ecs_entity_t spawn_prefab_frame_debugger_ui(ecs_world_t *world) {
    zox_prefab_child(prefab_window)
    zox_prefab_name("frame_debugger_ui")
    zox_add_tag(e, IgnoreWindowLayering)
    zox_prefab_set(e, PlotDataDouble, { 0, NULL });
    prefab_frame_debugger_ui = e;
    return e;
}