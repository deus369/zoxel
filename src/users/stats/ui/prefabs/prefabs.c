ecs_entity_t prefab_menu_stats;
#include "statbar2D.c"
#include "statbar3D.c"
#include "stats_menu.c"

void spawn_prefabs_stats_ui(ecs_world_t *world) {
    spawn_prefab_statbar3D(world);
    spawn_prefab_statbar2D(world);
    prefab_menu_stats = spawn_prefab_menu_stats(world, prefab_window_users);
}
