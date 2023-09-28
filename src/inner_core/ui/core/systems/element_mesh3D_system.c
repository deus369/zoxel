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
        if (!initializeEntityMesh->value) continue;
        const CanvasLink *canvasLink = &canvasLinks[i];
        if (canvasLink->value == 0) continue;
        MeshDirty *meshDirty = &meshDirtys[i];
        if (meshDirty->value) continue;
        GenerateTexture *generateTexture = &generateTextures[i];
        if (generateTexture->value) continue;
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
        // zox_log("   > initialized mesh 3D [%lu]\n", it->entities[i])
    }
} zox_declare_system(Element3DMeshSystem)