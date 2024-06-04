ecs_entity_t prefab_menu_stats;
// ecs_entity_t prefab_icon_frame_stat;
ecs_entity_t prefab_icon_stat;
#include "statbar2D.c"
#include "statbar3D.c"
#include "stats_menu.c"
#include "icon_stat.c"

void spawn_prefabs_ui_stats(ecs_world_t *world) {
    spawn_prefab_statbar3D(world);
    spawn_prefab_statbar2D(world);
    // prefab_icon_frame_stat = spawn_prefab_icon_frame_stat(world, prefab_icon_frame);
    prefab_icon_stat = spawn_prefab_icon_stat(world, prefab_icon);
    prefab_menu_stats = spawn_prefab_menu_stats(world, prefab_window_users);
}
