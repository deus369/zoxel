ecs_entity_t button_prefab;

ecs_entity_t spawn_prefab_button(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_prefab(world, "ui_prefab_button");
    zoxel_add_component(world, e, Children);
    zoxel_add_tag(world, e, Button);
    // generic
    add_seed(world, e, 666);
    add_dirty(world, e);
    add_texture(world, e, (int2) { });
    add_texture_frame(world, e);
    #ifdef zoxel_transforms2D
    add_transform2Ds(world, e);
    #endif
    add_unique_mesh_components(world, e);
    add_ui_components(world, e);
    button_prefab = e;
    return e;
}

extern ecs_entity_t spawn_zext(ecs_world_t *world, ecs_entity_t parent, int2 pixel_position, float2 anchor, const char* text, int font_size);

ecs_entity_t spawn_button(ecs_world_t *world, ecs_entity_t parent,
    int2 position, int2 size, float2 anchor,
    const char* text, int font_size)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, button_prefab);
    initialize_ui_components(world, e, parent, position, size, anchor);
    Children *children = ecs_get_mut(world, e, Children);
    initialize_memory_component(children, ecs_entity_t, 1);
    children->value[0] = spawn_zext(world, e,
        (int2) { 0, 0 },
        (float2) { 0.5f, 0.5f },
        text, font_size);
    ecs_modified(world, e, Children);
    // printf("Texture ratio: %f - ScaleRatio: %f\n", (size.x / (float) size.y), (scaledSize2D.x / scaledSize2D.y));
    //printf("UI Element Spawned - Position [%ix%i] - Size [%ix%i] - Position(Real) [%fx%f] - ScaledSize [%fx%f]\n",
    //    position.x, position.y, size.x, size.y, position2D.x, position2D.y, scaledSize2D.x, scaledSize2D.y);
    return e;
}