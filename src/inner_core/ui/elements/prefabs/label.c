ecs_entity_t label_prefab;

ecs_entity_t spawn_prefab_label(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, zext_prefab);
    // set_unique_entity_name(world, e, "prefab_label");
    ecs_add_id(world, e, EcsPrefab);
    zoxel_add_tag(world, e, Label);
    ecs_defer_end(world);
    label_prefab = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab label [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_label(ecs_world_t *world, ecs_entity_t prefab, ecs_entity_t parent, int2 position, float2 anchor, const char* text,
    int font_size, unsigned char layer, float2 parent_position2D, int2 parent_pixel_size) {
    ecs_entity_t e = spawn_zext(world, prefab, parent, position, anchor,
        text, font_size, layer, parent_position2D, parent_pixel_size);
    set_unique_entity_name(world, e, "label");
    return e;
}