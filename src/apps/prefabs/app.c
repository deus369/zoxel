ecs_entity_t spawn_prefab_app(ecs_world_t *world, const int2 window_position, const int2 window_size) {
    zox_prefab()
    zox_prefab_name("app")
    zox_add_tag(e, App)
    zox_prefab_set(e, WindowPosition, {window_position })
    zox_prefab_set(e, WindowSize, { window_size })
    zox_prefab_set(e, WindowFullscreen, { 0 })
    zox_prefab_set(e, WindowMaximized, { 0 })
    zox_prefab_set(e, WindowSizeRestore, { int2_zero })
    zox_prefab_set(e, WindowPositionRestore, { int2_zero })
    return e;
}
