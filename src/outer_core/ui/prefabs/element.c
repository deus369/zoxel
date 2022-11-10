ecs_entity_t element_prefab;

ecs_entity_t spawn_element_prefab(ecs_world_t *world, int2 size)
{
    ecs_entity_t e = ecs_new_prefab(world, "ui_element_prefab");
    // generic
    add_seed(world, e, 444);
    add_dirty(world, e);
    // ui
    zoxel_add_tag(world, e, Element);
    zoxel_add_tag(world, e, ElementRender);
    zoxel_add_component(world, e, PixelPosition);
    zoxel_add_component(world, e, PixelSize);
    zoxel_add_component(world, e, Anchor);
    zoxel_add_component(world, e, CanvasLink);
    #ifdef zoxel_transforms2D
    add_transform2Ds(world, e);
    #endif
    // rendering
    zoxel_add_component(world, e, Brightness);
    add_texture(world, e, size);
    add_texture_frame(world, e);
    add_gpu_mesh(world, e);
    add_gpu_material(world, e);
    add_gpu_texture(world, e);
    zoxel_add_component(world, e, MeshIndicies);
    //! \todo Fix: Causes a Flecs memory leak?!?! Temporarily commented out.
    // zoxel_add_component(world, e, MeshVertices);
    // printf("Spawned test_custom_mesh [%lu].\n", (long int) (e));
    // zoxel_add_tag(world, e, SaveTexture);
    element_prefab = e;
    return e;
}

// a quick & dirty lookup for uis
ecs_entity_t ui_entities[128];
int ui_entities_count = 0;

ecs_entity_t spawn_element(ecs_world_t *world, int2 position, int2 size, float2 anchor)
{
    const PixelSize *canvasSize = ecs_get(world, canvas, PixelSize);
    float2 canvasSizef2 = { (float) canvasSize->value.x, (float) canvasSize->value.y };
    float aspectRatio = canvasSizef2.x / canvasSizef2.y;
    float2 scaledSize2D = (float2) { size.x / canvasSizef2.y, size.y / canvasSizef2.y };
    float2 position2D = { ((position.x  / canvasSizef2.x) - 0.5f + anchor.x) * aspectRatio, ((position.y  / canvasSizef2.y) - 0.5f + anchor.y) };
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, element_prefab);
    ecs_set(world, e, Anchor, { anchor });
    ecs_set(world, e, PixelPosition, { position });
    ecs_set(world, e, PixelSize, { size });
    ecs_set(world, e, TextureSize, { size });
    // ecs_set(world, e, TextureSize, { int2_multiply_float(size, 0.25f) });
    ecs_set(world, e, Brightness, { 1.0f });
    ecs_set(world, e, CanvasLink, { canvas });
    ecs_set(world, e, Scale1D, { 1 });
    ecs_set(world, e, Position2D, { position2D });
    spawn_gpu_mesh(world, e);
    spawn_gpu_material(world, e, textured2DShader);
    spawn_gpu_texture(world, e);
    set_mesh_indicies_world(world, e, square_indicies, 6);
    set_mesh_vertices_world_scale2D(world, e, squareTexturedVerts2, 16, scaledSize2D);  // scale the mesh
    // printf("Texture ratio: %f - ScaleRatio: %f\n", (size.x / (float) size.y), (scaledSize2D.x / scaledSize2D.y));
    //printf("UI Element Spawned - Position [%ix%i] - Size [%ix%i] - Position(Real) [%fx%f] - ScaledSize [%fx%f]\n",
    //    position.x, position.y, size.x, size.y, position2D.x, position2D.y, scaledSize2D.x, scaledSize2D.y);
    ui_entities[ui_entities_count] = e;
    ui_entities_count++;
    return e;
}