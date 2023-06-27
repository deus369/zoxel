// #define zox_time_element_mesh_system

void ElementMeshSystem(ecs_iter_t *it) {
    #ifdef zox_time_element_mesh_system
        begin_timing()
    #endif
    unsigned char material_spawn_count = 0;
    const unsigned char max_material_spawn_count = 6;
    const PixelSize *pixelSizes = ecs_field(it, PixelSize, 2);
    const CanvasLink *canvasLinks = ecs_field(it, CanvasLink, 3);
    InitializeEntityMesh *initializeEntityMeshs = ecs_field(it, InitializeEntityMesh, 4);
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 5);
    GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 6);
    MeshVertices2D *meshVertices2Ds = ecs_field(it, MeshVertices2D, 7);
    MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 8);
    MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 9);
    TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 10);
    for (int i = 0; i < it->count; i++) {
        InitializeEntityMesh *initializeEntityMesh = &initializeEntityMeshs[i];
        if (initializeEntityMesh->value != 1) continue;
        const CanvasLink *canvasLink = &canvasLinks[i];
        if (canvasLink->value == 0) continue;
        const PixelSize *pixelSize = &pixelSizes[i];
        MeshDirty *meshDirty = &meshDirtys[i];
        GenerateTexture *generateTexture = &generateTextures[i];
        MeshVertices2D *meshVertices2D = &meshVertices2Ds[i];
        const PixelSize *canvasSize = ecs_get(world, canvasLink->value, PixelSize);
        float2 canvasSizef = { (float) canvasSize->value.x, (float) canvasSize->value.y };
        float2 scale2D = (float2) { pixelSize->value.x / canvasSizef.y, pixelSize->value.y / canvasSizef.y };
        scale_mesh2D_vertices_p(meshVertices2D, scale2D);
        if (!headless)  {
            MeshGPULink *meshGPULink = &meshGPULinks[i];
            MaterialGPULink *materialGPULink = &materialGPULinks[i];
            TextureGPULink *textureGPULink = &textureGPULinks[i];
            // materialGPULink->value = material2D_textured;
            materialGPULink->value = spawn_gpu_material_program(shader2D_textured);
            meshGPULink->value = spawn_gpu_mesh_buffers();
            textureGPULink->value = spawn_gpu_texture_buffers();
        }
        initializeEntityMesh->value = 0;
        meshDirty->value = 1;
        generateTexture->value = 1;
        // zoxel_log(" > [%lu] element_mesh_system: scale2D [%fx%f]\n", it->entities[i], scale2D.x, scale2D.y);
        material_spawn_count++;
        if (material_spawn_count >= max_material_spawn_count) break;
        #ifdef zox_time_element_mesh_system
            did_do_timing()
        #endif
        // zoxel_log(" > ui mesh 2D spawned on gpu [%lu]\n", it->entities[i]);
    }
    #ifdef zox_time_element_mesh_system
        end_timing("    - element_mesh_system")
    #endif
} zox_declare_system(ElementMeshSystem)