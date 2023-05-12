ecs_entity_t zigel_prefab;

ecs_entity_t spawn_zigel_prefab(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "zigel_prefab");
    set_unique_entity_name(world, e, "zigel_prefab");
    zoxel_add_tag(e, Zigel);
    zoxel_set(world, e, ZigelIndex, { 0 });
    zoxel_add_tag(e, FontTexture);
    add_ui_plus_components(world, e);
    zoxel_set(world, e, Color, {{ 55, 185, 125, 255 }});
    ecs_defer_end(world);
    zigel_prefab = e;
    #ifdef zoxel_debug_prefabs
        printf("spawn_prefab zigel [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_zigel(ecs_world_t *world, ecs_entity_t zext, unsigned char index, int2 position, int2 size,
    float2 anchor, unsigned char layer, float2 parent_position2D, int2 parent_pixel_size, int2 canvas_size) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, zigel_prefab);
    set_unique_entity_name(world, e, "zigel");
    zoxel_set(world, e, ZigelIndex, { index });
    zoxel_set(world, e, Color, {{ 55 + rand() % 60, 150 + rand() % 75, 135 + rand() % 70, 255 }});
    initialize_ui_components_2(world, e, zext, position, size, anchor, layer, parent_position2D, parent_pixel_size, canvas_size);
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
    zoxel_log("Spawned zigel [%lu]\n", (long int) e);
    #endif
    return e;
}