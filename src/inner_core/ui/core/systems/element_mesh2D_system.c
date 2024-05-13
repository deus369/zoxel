// #define zox_time_element_mesh_system
void Element2DMeshSystem(ecs_iter_t *it) {
#ifdef zox_time_element_mesh_system
    begin_timing()
#endif
    zox_iter_world()
    zox_field_in(PixelSize, pixelSizes, 2)
    zox_field_in(MeshAlignment, meshAlignments, 3)
    zox_field_in(CanvasLink, canvasLinks, 4)
    zox_field_out(InitializeEntityMesh, initializeEntityMeshs, 5)
    zox_field_out(MeshDirty, meshDirtys, 6)
    zox_field_out(MeshVertices2D, meshVertices2Ds, 7)
    zox_field_out(MeshGPULink, meshGPULinks, 8)
    zox_field_out(TextureGPULink, textureGPULinks, 9)
    zox_field_out(UvsGPULink, uvsGPULinks, 10)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(InitializeEntityMesh, initializeEntityMeshs, initializeEntityMesh)
        if (!initializeEntityMesh->value) continue;
        zox_field_i_in(CanvasLink, canvasLinks, canvasLink)
        if (!canvasLink->value) continue;
        zox_field_e()
        zox_field_i_in(PixelSize, pixelSizes, pixelSize)
        zox_field_i_in(MeshAlignment, meshAlignments, meshAlignment)
        zox_field_i_out(MeshDirty, meshDirtys, meshDirty)
        zox_field_i_out(MeshVertices2D, meshVertices2Ds, meshVertices2D)
        const int2 canvas_size = zox_get_value(canvasLink->value, PixelSize)
        const float2 canvasSizef = { (float) canvas_size.x, (float) canvas_size.y };
        const float2 scale2D = (float2) { pixelSize->value.x / canvasSizef.y, pixelSize->value.y / canvasSizef.y };
        set_mesh_vertices_scale2D(meshVertices2D, get_aligned_mesh2D(meshAlignment->value), 4, scale2D);
        // spawn gpu bufers
        if (!headless) {
            zox_field_i_out(MeshGPULink, meshGPULinks, meshGPULink)
            zox_field_i_out(UvsGPULink, uvsGPULinks, uvsGPULink)
            zox_field_i_out(TextureGPULink, textureGPULinks, textureGPULink)
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
    }
#ifdef zox_time_element_mesh_system
    end_timing("    - element_mesh_system")
#endif
} zox_declare_system(Element2DMeshSystem)
