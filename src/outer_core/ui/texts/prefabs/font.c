ecs_entity_t font_prefab;
// ecs_entity_t font_entity;

//! meta data for a font character
ecs_entity_t spawn_font_prefab(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "font_prefab");
    #ifdef zoxel_debug_prefabs
    printf("spawn_prefab font [%lu].\n", (long int) (e));
    #endif
    zoxel_add_tag(world, e, Font);
    zoxel_add(world, e, FontData);
    font_prefab = e;
    ecs_defer_end(world);
    return e;
}

ecs_entity_t spawn_font(ecs_world_t *world, const byte2 points[], unsigned char length)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, font_prefab);
    FontData fontData = { };
    initialize_memory_component_non_pointer(fontData, byte2, length);
    for (int i = 0; i < length; i++)
    {
        fontData.value[i] = (byte2) { points[i].x, points[i].y }; // byte2_multiply_int(points[i], 16);
        // fontData.value[i] = byte2_multiply_int(points[i], 1);
    }
    ecs_set(world, e, FontData, { fontData.length, fontData.value });
    ecs_defer_end(world);
    return e;
}