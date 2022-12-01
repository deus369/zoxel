// the ui text entity that holds zigels.
ecs_entity_t spawn_zext_prefab(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "zext_prefab");
    set_unique_entity_name(world, e, "zext_prefab");
    #ifdef zoxel_debug_prefabs
    printf("spawn_prefab zext [%lu].\n", (long int) (e));
    #endif
    zoxel_add_tag(world, e, Zext);
    zoxel_add(world, e, ZextData);
    zoxel_add(world, e, ZextSize);
    zoxel_set(world, e, ZextDirty, { 0 });
    zoxel_add(world, e, Children);
    add_transform2Ds(world, e);
    add_ui_plus_components_invisible(world, e);
    // zoxel_set(world, e, MeshDirty, { 0 });
    // zoxel_add(world, e, AnimateZext);
    ecs_defer_end(world);
    return e;
}

ecs_entity_t spawn_zext(ecs_world_t *world, ecs_entity_t prefab,
    ecs_entity_t parent, int2 position, float2 anchor,
    const char* text, int font_size, unsigned char layer,
    float2 parent_position2D, int2 parent_pixel_size)
{
    ecs_defer_begin(world);
    int textLength = strlen(text);
    int2 zext_size = (int2) { font_size * textLength, font_size };
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab);
    set_unique_entity_name(world, e, "zext");
    #ifdef zoxel_debug_spawns
    printf("Spawned zext [%lu]\n", (long int) e);
    #endif
    ecs_set(world, e, ZextSize, { font_size });
    // ecs_set(world, e, ZextDirty, { 0 });
    float2 position2D = initialize_ui_components_2(world, e,
        parent, position, zext_size, anchor, layer,
        parent_position2D, parent_pixel_size,
        ecs_get(world, main_canvas, PixelSize)->value);
    ZextData zextData = { };
    Children children = { };
    initialize_memory_component_non_pointer(zextData, unsigned char, textLength);
    initialize_memory_component_non_pointer(children, ecs_entity_t, textLength);
    for (int i = 0; i < textLength; i++)
    {
        unsigned char zigel_index = convert_ascii(text[i]);
        zextData.value[i] = zigel_index;
        children.value[i] = spawn_zext_zigel(world, e, layer + 1, i, textLength,
            zigel_index, font_size, position2D, zext_size);
        // printf("Is %i [%lu] valid: %s\n", i, (long int) children.value[i], ecs_is_valid(world, children.value[i]) ? "Yes" : "No");
    }
    ecs_set(world, e, ZextData, { zextData.length, zextData.value });
    ecs_set(world, e, Children, { children.length, children.value });
    ecs_defer_end(world);
    return e;
}