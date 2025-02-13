ecs_entity_t spawn_prefab_label(ecs_world_t *world) {
    zox_prefab_child(prefab_zext)
    zox_prefab_name("prefab_label")
    zox_add_tag(e, Label)
    return e;
}

/*ecs_entity_t spawn_label(ecs_world_t *world, ecs_entity_t prefab, ecs_entity_t parent, ecs_entity_t canvas, int2 position, float2 anchor,  const char* text, int font_size, byte alignment, byte layer, int2 parent_pixel_position_global, int2 parent_pixel_size) {
    ecs_entity_t e = spawn_zext(world, prefab, parent, canvas, position, anchor, byte2_zero, text, font_size, alignment, layer, parent_pixel_position_global, parent_pixel_size, 0);
    zox_name("label")
    return e;
}*/
