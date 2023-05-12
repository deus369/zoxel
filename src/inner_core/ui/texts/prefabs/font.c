ecs_entity_t font_prefab;

ecs_entity_t spawn_font_prefab(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "");
    set_unique_entity_name(world, e, "font_prefab");
    zoxel_add_tag(e, Font);
    zoxel_add(world, e, FontData);
    ecs_defer_end(world);
    font_prefab = e;
    #ifdef zoxel_debug_prefabs
        printf("spawn_prefab font [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_font(ecs_world_t *world, const byte2 points[], unsigned char length) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, font_prefab);
    FontData fontData = { };
    initialize_memory_component_non_pointer(fontData, byte2, length);
    for (int i = 0; i < length; i++) {
        fontData.value[i] = (byte2) { points[i].x, points[i].y };
    }
    ecs_set(world, e, FontData, { fontData.length, fontData.value });
    // set_unique_entity_name(world, e, "font");
    ecs_defer_end(world);
    return e;
}