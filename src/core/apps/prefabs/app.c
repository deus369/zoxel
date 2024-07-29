ecs_entity_t prefab_app;
ecs_entity_t main_app;

ecs_entity_t spawn_prefab_app(ecs_world_t *world, const int2 window_position, const int2 window_size) {
    zox_prefab()
    zox_prefab_name("prefab_app")
    zox_add_tag(e, App)
    zox_prefab_set(e, WindowPosition, {window_position })
    zox_prefab_set(e, WindowSize, { window_size })
    zox_prefab_set(e, WindowFullscreen, { 0 })
    zox_prefab_set(e, WindowSizeRestore, { window_size })
    prefab_app = e;
    return e;
}
