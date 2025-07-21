ecs_entity_t prefab_menu_stats;
ecs_entity_t prefab_icon_stat;
ecs_entity_t prefab_statbar2D;
ecs_entity_t prefab_statbar3D;
zox_user_menu_functions_frame_color(Stats, Stat, stats, stat, default_fill_color_frame_stat)
#include "statbar2.c"
#include "statbar3.c"
#include "icon_stat.c"

void spawn_prefabs_ui_stats(ecs_world_t *world) {
    prefab_statbar2D = spawn_prefab_statbar2D(world, prefab_elementbar2D);
    prefab_statbar3D = spawn_prefab_statbar3D(world, prefab_elementbar3D);
    prefab_icon_stat = spawn_prefab_icon_stat(world, prefab_icon_user);
    prefab_menu_stats = spawn_prefab_menu_stats(world, prefab_window_users);
}
