ecs_entity_t prefab_inventory_menu;
ecs_entity_t prefab_item_icon_frame;
#include "item_icon_frame.c"
#include "inventory_menu.c"

void spawn_prefabs_items_ui(ecs_world_t *world) {
    prefab_item_icon_frame = spawn_prefab_icon_frame_item(world, prefab_icon_frame_user);
    prefab_inventory_menu = spawn_prefab_inventory_menu(world, prefab_window_users);
}
