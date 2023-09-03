// #define zox_time_element_mesh_system

void ElementMeshSystem(ecs_iter_t *it) {
    #ifdef zox_time_element_mesh_system
        begin_timing()
    #endif
    ecs_world_t *world = it->world;
    const PixelSize *pixelSizes = ecs_field(it, PixelSize, 2);
    const CanvasLink *canvasLinks = ecs_field(it, CanvasLink, 3);
    InitializeEntityMesh *initializeEntityMeshs = ecs_field(it, InitializeEntityMesh, 4);
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 5);
    GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 6);
    MeshVertices2D *meshVertices2Ds = ecs_field(it, MeshVertices2D, 7);
    MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 8);
    TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 9);
    UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 10);
    for (int i = 0; i < it->count; i++) {
        InitializeEntityMesh *initializeEntityMesh = &initializeEntityMeshs[i];
        if (initializeEntityMesh->value != 1) continue;
        const CanvasLink *canvasLink = &canvasLinks[i];
        if (canvasLink->value == 0) continue;
        const PixelSize *pixelSize = &pixelSizes[i];
        MeshDirty *meshDirty = &meshDirtys[i];
        GenerateTexture *generateTexture = &generateTextures[i];
        MeshVertices2D *meshVertices2D = &meshVertices2Ds[i];
        // rescale verts if scale changes, todo: make this in a new system?
        const PixelSize *canvasSize = ecs_get(world, canvasLink->value, PixelSize);
        float2 canvasSizef = { (float) canvasSize->value.x, (float) canvasSize->value.y };
        float2 scale2D = (float2) { pixelSize->value.x / canvasSizef.y, pixelSize->value.y / canvasSizef.y };
        set_mesh_vertices_scale2D(meshVertices2D, square_vertices, 4, scale2D);  // scale the mesh
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
        generateTexture->value = 1;
        #ifdef zox_time_element_mesh_system
            did_do_timing()
        #endif
        // zoxel_log(" > ui mesh 2D spawned on gpu [%lu]\n", it->entities[i]);
    }
    #ifdef zox_time_element_mesh_system
        end_timing("    - element_mesh_system")
    #endif
} zox_declare_system(ElementMeshSystem)

// MaterialInstancedGPULink *materialInstancedGPULinks = ecs_field(it, MaterialInstancedGPULink, 9);
// MaterialInstancedGPULink *materialInstancedGPULink = &materialInstancedGPULinks[i];
// materialInstancedGPULink->value = textured2D_material;
// zoxel_log(" > [%lu] scale2D [%fx%f]\n", it->entities[i], scale2D.x, scale2D.y);
// zoxel_log(" > [%lu] element_mesh_system: scale2D [%fx%f]\n", it->entities[i], scale2D.x, scale2D.y);
// material_spawn_count++;
// if (material_spawn_count >= max_material_spawn_count) break;
// materialGPULink->value = spawn_gpu_material_program(shader2D_textured);
// zoxel_log(" > entity [%lu] ui spawned [%i, %i, %i]\n", it->entities[i], meshGPULink->value.x, meshGPULink->value.y, uvsGPULink->value);
        