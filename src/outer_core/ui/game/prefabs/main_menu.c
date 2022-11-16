ecs_entity_t main_menu_prefab;

ecs_entity_t spawn_prefab_main_menu(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, window_prefab);
    ecs_add_id(world, e, EcsPrefab);
    ecs_set_name(world, e, "prefab_main_menu");
    zoxel_add_tag(world, e, MainMenu);
    main_menu_prefab = e;
    ecs_defer_end(world);
    return e;
}

ecs_entity_t spawn_main_menu(ecs_world_t *world, const char *menu_name) // int2 position, int2 size, float2 anchor)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, main_menu_prefab);
    // initialize_ui_components(world, e, canvas, position, size, anchor);
    ecs_defer_end(world);
    return e;
}