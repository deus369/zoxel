ecs_entity_t zigel_prefab;

// an individual text character entity.
ecs_entity_t spawn_zigel_prefab(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_prefab(world, "zigel_prefab");
    zoxel_add_tag(world, e, Zigel);
    zoxel_add_component(world, e, ZigelIndex);
    add_seed(world, e, 444);
    add_dirty(world, e);
    add_transform2Ds(world, e);
    add_texture(world, e, (int2) { });
    zoxel_add_tag(world, e, FontTexture);
    // add_texture_frame(world, e);
    add_unique_mesh_components(world, e);
    add_ui_components(world, e);    // replace texture components with zigel ones
    zigel_prefab = e;
    return e;
}

ecs_entity_t spawn_zigel(ecs_world_t *world, ecs_entity_t zext, unsigned char index,
    int2 position, int2 size, float2 anchor)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, zigel_prefab);
    zoxel_set_component(world, e, ZigelIndex, { index });
    initialize_ui_components(world, e, zext, position, size, anchor);
    return e;
}