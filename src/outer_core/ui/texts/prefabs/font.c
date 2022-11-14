ecs_entity_t font_prefab;
// ecs_entity_t font_entity;

//! meta data for a font character
ecs_entity_t spawn_font_prefab(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_prefab(world, "font_prefab");
    #ifdef zoxel_debug_prefabs
    printf("spawn_prefab font [%lu].\n", (long int) (e));
    #endif
    zoxel_add_tag(world, e, Font);
    zoxel_add_component(world, e, FontData);
    font_prefab = e;
    return e;
}

ecs_entity_t spawn_font(ecs_world_t *world, const byte2 points[], unsigned char length)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, font_prefab);
    FontData *fontData = ecs_get_mut(world, e, FontData);
    initialize_memory_component(fontData, byte2, length);
    for (int i = 0; i < length; i++)
    {
        fontData->value[i] = byte2_multiply_int(points[i], 16);
    }
    ecs_modified(world, e, FontData);
    // font_entity = e;
    return e;
}

// fontData->value[0] = (byte2) { 128, 50 };
// fontData->value[1] = (byte2) { 128, 200 };
// fontData->value[2] = (byte2) { 50, 128 };
// fontData->value[3] = (byte2) { 200, 128 };
// fontData->value[4] = (byte2) { 50, 50 };
// fontData->value[5] = (byte2) { 200, 200 };