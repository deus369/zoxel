#ifndef zox_items_ui
#define zox_items_ui

ecs_entity_t prefab_inventory_menu;
ecs_entity_t prefab_item_icon_frame;
zox_declare_tag(InventoryMenu)
zox_declare_tag(ItemIconFrame)
#include "data/spawn_inventory_menu.c"
#include "prefabs/item_icon_frame.c"
#include "prefabs/inventory_menu.c"

void spawn_prefabs_items_ui(ecs_world_t *world) {
    prefab_item_icon_frame = spawn_prefab_icon_frame_item(world, prefab_icon_frame);
    prefab_inventory_menu = spawn_prefab_inventory_menu(world);
}

zox_begin_module(ItemsUI)
zox_define_tag(InventoryMenu)
zox_define_tag(ItemIconFrame)
    spawn_prefabs_items_ui(world);
zoxel_end_module(ItemsUI)

#endif
