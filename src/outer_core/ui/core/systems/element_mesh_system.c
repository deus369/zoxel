//! Closes a window when button is clicked
void ElementMeshSystem(ecs_iter_t *it)
{
    // printf("ElementMeshSystem [%i] - canvas [%lu]\n", it->count, (long int) main_canvas);
    const EntityInitialize *entityInitializes = ecs_field(it, EntityInitialize, 2);
    const PixelSize *pixelSizes = ecs_field(it, PixelSize, 3);
    const CanvasLink *canvasLinks = ecs_field(it, CanvasLink, 4);
    for (int i = 0; i < it->count; i++)
    {
        const EntityInitialize *entityInitialize = &entityInitializes[i];
        if (entityInitialize->value == 1)
        {
            ecs_entity_t e = it->entities[i];
            const PixelSize *pixelSize = &pixelSizes[i];
            const CanvasLink *canvasLink = &canvasLinks[i];
            const PixelSize *canvasSize = ecs_get(world, canvasLink->value, PixelSize);
            float2 canvasSizef = { (float) canvasSize->value.x, (float) canvasSize->value.y };
            spawn_gpu_mesh(world, e);
            spawn_gpu_material(world, e, shader2D_textured);
            spawn_gpu_texture(world, e);
            set_mesh_indicies_world(world, e, square_indicies, 6);
            float2 scaledSize2D = (float2) {
                pixelSize->value.x / canvasSizef.y,
                pixelSize->value.y / canvasSizef.y };
            set_mesh_vertices_world_scale2D(world, e, squareTexturedVerts2, 16, scaledSize2D);  // scale the mesh
            // printf("ElementMeshSystem [%lu]\n", (long int) e);
        }
    }
}
ECS_SYSTEM_DECLARE(ElementMeshSystem);