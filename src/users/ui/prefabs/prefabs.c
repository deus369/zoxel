ecs_entity_t prefab_icon_frame_user;
ecs_entity_t prefab_window_users;
#include "icon_frame_user.c"
#include "window_users.c"

void spawn_prefabs_users_ui(ecs_world_t *world) {
    prefab_icon_frame_user = spawn_prefab_icon_frame_user(world, prefab_icon_frame);
    prefab_window_users = spawn_prefab_window_users(world, prefab_window);
}
