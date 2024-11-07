ecs_entity_t prefab_menu_items;
ecs_entity_t prefab_icon_item;
ecs_entity_t prefab_icon_frame_item;
#include "icon_item.c"
zox_user_menu_functions_frame_color(Items, Item, items, item, default_fill_color_frame_item)

ecs_entity_t spawn_prefab_icon_frame_item(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_icon_frame_item")
    zox_add_tag(e, IconLabel)
    return e;
}

void spawn_prefabs_items_ui(ecs_world_t *world) {
    // todo: set icon frame prefab here
    prefab_icon_item = spawn_prefab_icon_item(world, prefab_icon_user);
    prefab_icon_frame_item = spawn_prefab_icon_frame_item(world, prefab_icon_frame);
    prefab_menu_items = spawn_prefab_menu_items(world, prefab_window_users);
    zox_set(prefab_menu_items, IconFramePrefabLink, { prefab_icon_frame_item })
}
