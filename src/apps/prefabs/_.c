ecs_entity_t prefab_app;
ecs_entity_t main_app;

#include "app.c"

void spawn_prefabs_apps(ecs_world_t *world) {
    prefab_app = spawn_prefab_app(world, default_window_position, default_window_size);
}