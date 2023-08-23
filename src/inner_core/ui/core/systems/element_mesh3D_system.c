void Element3DMeshSystem(ecs_iter_t *it) {
    const CanvasLink *canvasLinks = ecs_field(it, CanvasLink, 3);
    InitializeEntityMesh *initializeEntityMeshs = ecs_field(it, InitializeEntityMesh, 4);
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 5);
    GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 6);
    MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 7);
    UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 8);
    ColorsGPULink *colorsGPULinks = ecs_field(it, ColorsGPULink, 9);
    TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 10);
    for (int i = 0; i < it->count; i++) {
        InitializeEntityMesh *initializeEntityMesh = &initializeEntityMeshs[i];
        if (initializeEntityMesh->value != 1) continue;
        const CanvasLink *canvasLink = &canvasLinks[i];
        if (canvasLink->value == 0) continue;
        ecs_entity_t e = it->entities[i];
        MeshDirty *meshDirty = &meshDirtys[i];
        GenerateTexture *generateTexture = &generateTextures[i];
        if (!headless) {
            MeshGPULink *meshGPULink = &meshGPULinks[i];
            UvsGPULink *uvsGPULink = &uvsGPULinks[i];
            ColorsGPULink *colorsGPULink = &colorsGPULinks[i];
            TextureGPULink *textureGPULink = &textureGPULinks[i];
            meshGPULink->value = spawn_gpu_mesh_buffers();
            textureGPULink->value = spawn_gpu_texture_buffers();
            uvsGPULink->value = spawn_gpu_generic_buffer();
            colorsGPULink->value = spawn_gpu_generic_buffer();
            // zoxel_log(" > entity [%lu] ui 3D spawned [%i, %i, %i]\n", it->entities[i], meshGPULink->value.x, meshGPULink->value.y, uvsGPULink->value);
        }
        initializeEntityMesh->value = 0;
        meshDirty->value = 1;
        generateTexture->value = 1;
        // zoxel_log(" o> mesh_3D spawned [%lu]\n", it->entities[i]);
    }
} zox_declare_system(Element3DMeshSystem)

// const PixelSize *pixelSizes = ecs_field(it, PixelSize, 2);
// const PixelSize *canvasSize = ecs_get(world, canvasLink->value, PixelSize);
// const PixelSize *pixelSize = &pixelSizes[i];
// float2 canvasSizef = { (float) canvasSize->value.x, (float) canvasSize->value.y };
// float2 scale2D = (float2) { pixelSize->value.x / canvasSizef.y, pixelSize->value.y / canvasSizef.y };
// scale_mesh2D_vertices(world, e, scale2D);
// spawn_gpu_material(world, e, shader3D_textured);
// spawn_gpu_mesh(world, e);
// spawn_gpu_uvs(world, e);
// spawn_gpu_colors(world, e);
// spawn_gpu_texture(world, e);