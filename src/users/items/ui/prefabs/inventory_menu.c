// todo: use spawn_icon_grid for all user menus
// todo: spawn a body ui (as regular element) for icons
// todo: fetch highest layer from canvas? save it refreshing stack when spawning a new window

/*ecs_entity_t spawn_prefab_inventory_menu(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_inventory_menu")
    zox_add_tag(e, InventoryMenu)
    return e;
}

ecs_entity_t spawn_menu_items_player(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    SpawnWindowUsers data = get_default_spawn_window_users_data(character, canvas, canvas_size);
    data.window.prefab = prefab_inventory_menu;
    data.window.user_links_id = zox_id(ItemLinks);
    data.header_zext.text = "Inventory";
    // data.icon_frame.prefab = prefab_icon_frame_item;
    data.icon.prefab = prefab_icon_item;
    return spawn_window_users(world, &data);
}
*/
