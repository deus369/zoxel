#include "app.c"

void spawn_prefabs_apps(ecs_world_t *world) {
    spawn_prefab_app(world, default_window_position, default_window_size);
}