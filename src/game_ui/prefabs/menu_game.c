ecs_entity_t spawn_prefab_menu_game(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab);
    zox_prefab_name("menu_game");
    zox_add_tag(e, MenuGame);
    zox_prefab_set(e, AnchorSize, { float2_one });
    zox_prefab_set(e, Children, { 0, NULL });
    return e;
}