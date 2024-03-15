ecs_entity_t prefab_app;
ecs_entity_t main_app;

ecs_entity_t spawn_prefab_app(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_app")
    zox_add_tag(e, App)
    zox_prefab_set(e, WindowPosition, { 0, 0 })
    zox_prefab_set(e, WindowSize, { 720, 720 })
    zox_prefab_set(e, WindowFullscreen, { 0 })
    prefab_app = e;
    return e;
}
