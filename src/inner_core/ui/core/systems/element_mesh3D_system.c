void ElementMesh3DSystem(ecs_iter_t *it) {
    // const PixelSize *pixelSizes = ecs_field(it, PixelSize, 2);
    const CanvasLink *canvasLinks = ecs_field(it, CanvasLink, 3);
    InitializeEntityMesh *initializeEntityMeshs = ecs_field(it, InitializeEntityMesh, 4);
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 5);
    GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 6);
    for (int i = 0; i < it->count; i++) {
        InitializeEntityMesh *initializeEntityMesh = &initializeEntityMeshs[i];
        if (initializeEntityMesh->value != 1) continue;
        const CanvasLink *canvasLink = &canvasLinks[i];
        if (canvasLink->value == 0) continue;
        // const PixelSize *canvasSize = ecs_get(world, canvasLink->value, PixelSize);
        ecs_entity_t e = it->entities[i];
        // const PixelSize *pixelSize = &pixelSizes[i];
        MeshDirty *meshDirty = &meshDirtys[i];
        GenerateTexture *generateTexture = &generateTextures[i];
        // float2 canvasSizef = { (float) canvasSize->value.x, (float) canvasSize->value.y };
        // float2 scale2D = (float2) { pixelSize->value.x / canvasSizef.y, pixelSize->value.y / canvasSizef.y };
        // scale_mesh2D_vertices(world, e, scale2D);
        spawn_gpu_mesh(world, e);
        spawn_gpu_material(world, e, shader3D_textured);
        spawn_gpu_uvs(world, e);
        spawn_gpu_colors(world, e);
        spawn_gpu_texture(world, e);
        initializeEntityMesh->value = 0;
        meshDirty->value = 1;
        generateTexture->value = 1;
        // zoxel_log(" o> mesh_3D spawned [%lu]\n", it->entities[i]);
    }
} zox_declare_system(ElementMesh3DSystem)