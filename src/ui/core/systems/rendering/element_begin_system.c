void ElementBeginSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(InitializeElement)
    zox_sys_in(PixelSize)
    zox_sys_in(MeshAlignment)
    zox_sys_in(CanvasLink)
    zox_sys_out(MeshDirty)
    zox_sys_out(MeshVertices2D)
    zox_sys_out(MeshGPULink)
    zox_sys_out(TextureGPULink)
    zox_sys_out(UvsGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(InitializeElement, initializeElement)
        zox_sys_i(CanvasLink, canvasLink)
        zox_sys_i(PixelSize, pixelSize)
        zox_sys_i(MeshAlignment, meshAlignment)
        zox_sys_o(MeshDirty, meshDirty)
        zox_sys_o(MeshVertices2D, meshVertices2D)
        zox_sys_o(MeshGPULink, meshGPULink)
        zox_sys_o(UvsGPULink, uvsGPULink)
        zox_sys_o(TextureGPULink, textureGPULink)
        if (initializeElement->value != zox_dirty_active || !canvasLink->value) {
            continue;
        }
        // we also set mesh verts here
        zox_geter_value(canvasLink->value, PixelSize, int2, canvas_size)
        const float2 canvas_sizef = int2_to_float2(canvas_size);
        const float2 size2D = (float2) { pixelSize->value.x / canvas_sizef.y, pixelSize->value.y / canvas_sizef.y };
        set_mesh_vertices_scale2D(meshVertices2D, get_aligned_mesh2D(meshAlignment->value), 4, size2D);
        // spawn gpu bufers
        if (!headless) {
            // spawn mesh buffers needs to be done on main thread
            meshGPULink->value = spawn_gpu_mesh_buffers();
            textureGPULink->value = spawn_gpu_texture_buffer();
            uvsGPULink->value = spawn_gpu_generic_buffer();
        }
        meshDirty->value = mesh_state_trigger; // mesh_state_upload;
    }
} zox_declare_system(ElementBeginSystem)