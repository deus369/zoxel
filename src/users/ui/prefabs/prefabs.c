ecs_entity_t prefab_frame_user;
ecs_entity_t prefab_icon_user;
ecs_entity_t prefab_window_users;
#include "frame_user.c"
#include "icon_user.c"
#include "window_users.c"

void spawn_prefabs_users_ui(ecs_world_t *world) {
    if (prefab_icon == 0) {
        zox_log(" ! ui prefab did not spawn\n")
        return;
    }
    prefab_icon_user = spawn_prefab_icon_user(world, prefab_icon);
    prefab_frame_user = spawn_prefab_frame_user(world, prefab_frame);
    prefab_window_users = spawn_prefab_window_users(world, prefab_window_invisible);
    zox_prefab_set(prefab_icon_mouse_follow, UserDataLink, { 0 })
}
