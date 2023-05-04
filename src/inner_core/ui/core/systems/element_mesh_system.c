void ElementMeshSystem(ecs_iter_t *it) {
    const PixelSize *pixelSizes = ecs_field(it, PixelSize, 2);
    const CanvasLink *canvasLinks = ecs_field(it, CanvasLink, 3);
    InitializeEntityMesh *initializeEntityMeshs = ecs_field(it, InitializeEntityMesh, 4);
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 5);
    GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 6);
    for (int i = 0; i < it->count; i++) {
        InitializeEntityMesh *initializeEntityMesh = &initializeEntityMeshs[i];
        if (initializeEntityMesh->value != 1) {
            continue;
        }
        ecs_entity_t e = it->entities[i];
        const PixelSize *pixelSize = &pixelSizes[i];
        const CanvasLink *canvasLink = &canvasLinks[i];
        MeshDirty *meshDirty = &meshDirtys[i];
        GenerateTexture *generateTexture = &generateTextures[i];
        const PixelSize *canvasSize = ecs_get(world, canvasLink->value, PixelSize);
        // new ui size
        float2 canvasSizef = { (float) canvasSize->value.x, (float) canvasSize->value.y };
        float2 scale2D = (float2) { pixelSize->value.x / canvasSizef.y, pixelSize->value.y / canvasSizef.y };
        initializeEntityMesh->value = 0;
        meshDirty->value = 1;
        generateTexture->value = 1;
        scale_mesh2D_vertices(world, e, scale2D);
        spawn_gpu_mesh(world, e);
        spawn_gpu_material(world, e, shader2D_textured);
        spawn_gpu_texture(world, e);
    }
}
zoxel_declare_system(ElementMeshSystem)

// set_mesh_indicies_world(world, e, square_indicies, 6);
// set_mesh_vertices_world_scale2D(world, e, square_vertices, 4, scaledSize2D);  // scale the mesh
// zoxel_log(" > initialized ui mesh\n");