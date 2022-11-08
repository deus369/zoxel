ecs_entity_t element_prefab;

void spawn_element_prefab(ecs_world_t *world, int2 size)
{
    ecs_entity_t e = ecs_new_prefab(world, "ui_element_prefab");
    // generic
    add_seed(world, e, 444);
    add_dirty(world, e);
    // UI components
    zoxel_add_tag(world, e, Element);
    zoxel_add_component(world, e, PixelPosition);
    zoxel_add_component(world, e, PixelSize);
    #ifdef zoxel_transforms2D
    add_transform2Ds(world, e);
    #endif
    // Rendering2D
    add_texture(world, e, size);
    add_texture_frame(world, e);
    // gpu
    add_gpu_material(world, e);
    add_gpu_texture(world, e);
    // add render properties, brightness? color? etc
    zoxel_add_component(world, e, Brightness);
    // printf("Spawned test_custom_mesh [%lu].\n", (long int) (e));
    element_prefab = e;
}

ecs_entity_t spawn_element(ecs_world_t *world, int2 position, int2 size)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, element_prefab);
    // ui transform?
    ecs_set(world, e, PixelPosition, { size });
    ecs_set(world, e, PixelSize, { size });
    ecs_set(world, e, Position2D, { { position.x, position.y } });
    ecs_set(world, e, Scale1D, { 1.0f });
    ecs_set(world, e, Brightness, { 1.4f });
    spawn_gpu_material(world, e, textured2DShader);
    spawn_gpu_texture(world, e);
    // printf("Spawned Character2D [%lu]\n", (long unsigned int) e);
    return e;
}