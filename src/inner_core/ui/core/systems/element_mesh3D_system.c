void Element3DMeshSystem(ecs_iter_t *it) {
    zox_field_in(CanvasLink, canvasLinks, 3)
    zox_field_out(InitializeEntityMesh, initializeEntityMeshs, 4)
    zox_field_out(MeshDirty, meshDirtys, 5)
    zox_field_out(GenerateTexture, generateTextures, 6)
    zox_field_out(MeshGPULink, meshGPULinks, 7)
    zox_field_out(UvsGPULink, uvsGPULinks, 8)
    zox_field_out(ColorsGPULink, colorsGPULinks, 9)
    zox_field_out(TextureGPULink, textureGPULinks, 10)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(InitializeEntityMesh, initializeEntityMeshs, initializeEntityMesh)
        if (!initializeEntityMesh->value) continue;
        zox_field_i_in(CanvasLink, canvasLinks, canvasLink)
        if (!canvasLink->value) continue;
        zox_field_i_out(MeshDirty, meshDirtys, meshDirty)
        if (meshDirty->value) continue;
        zox_field_i_out(GenerateTexture, generateTextures, generateTexture)
        if (generateTexture->value) continue;
        if (!headless) {
            zox_field_i_out(MeshGPULink, meshGPULinks, meshGPULink)
            zox_field_i_out(UvsGPULink, uvsGPULinks, uvsGPULink)
            zox_field_i_out(TextureGPULink, textureGPULinks, textureGPULink)
            zox_field_i_out(ColorsGPULink, colorsGPULinks, colorsGPULink)
            meshGPULink->value = spawn_gpu_mesh_buffers();
            textureGPULink->value = spawn_gpu_texture_buffers();
            uvsGPULink->value = spawn_gpu_generic_buffer();
            colorsGPULink->value = spawn_gpu_generic_buffer();
        }
        initializeEntityMesh->value = 0;
        meshDirty->value = 1;
        generateTexture->value = 1;
    }
} zox_declare_system(Element3DMeshSystem)
