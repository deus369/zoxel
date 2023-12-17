// #define zox_time_element_mesh_system

void Element2DMeshSystem(ecs_iter_t *it) {
#ifdef zox_time_element_mesh_system
    begin_timing()
#endif
    zox_iter_world()
    const PixelSize *pixelSizes = ecs_field(it, PixelSize, 2);
    const MeshAlignment *meshAlignments = ecs_field(it, MeshAlignment, 3);
    const CanvasLink *canvasLinks = ecs_field(it, CanvasLink, 4);
    InitializeEntityMesh *initializeEntityMeshs = ecs_field(it, InitializeEntityMesh, 5);
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 6);
    // GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 7);
    //  [out] GenerateTexture,
    MeshVertices2D *meshVertices2Ds = ecs_field(it, MeshVertices2D, 7);
    MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 8);
    TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 9);
    UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 10);
    for (int i = 0; i < it->count; i++) {
        InitializeEntityMesh *initializeEntityMesh = &initializeEntityMeshs[i];
        if (initializeEntityMesh->value != 1) continue;
        const CanvasLink *canvasLink = &canvasLinks[i];
        if (canvasLink->value == 0) continue;
        const ecs_entity_t e = it->entities[i];
        const PixelSize *pixelSize = &pixelSizes[i];
        const MeshAlignment *meshAlignment = &meshAlignments[i];
        MeshDirty *meshDirty = &meshDirtys[i];
        MeshVertices2D *meshVertices2D = &meshVertices2Ds[i];
        // rescale verts if scale changes, todo: make this in a new system?
        const PixelSize *canvasSize = ecs_get(world, canvasLink->value, PixelSize);
        float2 canvasSizef = { (float) canvasSize->value.x, (float) canvasSize->value.y };
        float2 scale2D = (float2) { pixelSize->value.x / canvasSizef.y, pixelSize->value.y / canvasSizef.y };
        set_mesh_vertices_scale2D(meshVertices2D, get_aligned_mesh2D(meshAlignment->value), 4, scale2D);
        // spawn gpu bufers
        if (!headless) {
            MeshGPULink *meshGPULink = &meshGPULinks[i];
            UvsGPULink *uvsGPULink = &uvsGPULinks[i];
            TextureGPULink *textureGPULink = &textureGPULinks[i];
            meshGPULink->value = spawn_gpu_mesh_buffers();
            textureGPULink->value = spawn_gpu_texture_buffers();
            uvsGPULink->value = spawn_gpu_generic_buffer();
        }
        initializeEntityMesh->value = 0;
        meshDirty->value = 1;
        if (zox_has(e, GenerateTexture)) zox_set(e, GenerateTexture, { 1 })
#ifdef zox_time_element_mesh_system
        did_do_timing()
#endif
        // zoxel_log(" > ui mesh 2D spawned on gpu [%lu]\n", it->entities[i]);
    }
#ifdef zox_time_element_mesh_system
    end_timing("    - element_mesh_system")
#endif
} zox_declare_system(Element2DMeshSystem)
