void Element2DMeshSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(PixelSize, pixelSizes, 2)
    zox_field_in(MeshAlignment, meshAlignments, 3)
    zox_field_in(CanvasLink, canvasLinks, 4)
    zox_field_out(InitializeElement, initializeElements, 5)
    zox_field_out(MeshDirty, meshDirtys, 6)
    zox_field_out(MeshVertices2D, meshVertices2Ds, 7)
    zox_field_out(MeshGPULink, meshGPULinks, 8)
    zox_field_out(TextureGPULink, textureGPULinks, 9)
    zox_field_out(UvsGPULink, uvsGPULinks, 10)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(InitializeElement, initializeElements, initializeElement)
        if (!initializeElement->value) {
            continue;
        }
        zox_field_i(CanvasLink, canvasLinks, canvasLink)
        if (!canvasLink->value) {
            continue;
        }
        zox_field_i(PixelSize, pixelSizes, pixelSize)
        zox_field_i(MeshAlignment, meshAlignments, meshAlignment)
        zox_field_o(MeshDirty, meshDirtys, meshDirty)
        zox_field_o(MeshVertices2D, meshVertices2Ds, meshVertices2D)
        const int2 canvas_size = zox_get_value(canvasLink->value, PixelSize)
        const float2 canvasSizef = { (float) canvas_size.x, (float) canvas_size.y };
        const float2 size2D = (float2) { pixelSize->value.x / canvasSizef.y, pixelSize->value.y / canvasSizef.y };
        set_mesh_vertices_scale2D(meshVertices2D, get_aligned_mesh2D(meshAlignment->value), 4, size2D);
        // spawn gpu bufers
        if (!headless) {
            // spawn mesh buffers needs to be done on main thread
            zox_field_o(MeshGPULink, meshGPULinks, meshGPULink)
            zox_field_o(UvsGPULink, uvsGPULinks, uvsGPULink)
            zox_field_o(TextureGPULink, textureGPULinks, textureGPULink)
            meshGPULink->value = spawn_gpu_mesh_buffers();
            textureGPULink->value = spawn_gpu_texture_buffer();
            uvsGPULink->value = spawn_gpu_generic_buffer();
            // zox_log("> [%s] activated mesh2D: size [%ix%i]\n", zox_get_name(it->entities[i]), pixelSize->value.x, pixelSize->value.y)
            // doing this again?
            zox_field_e()
            if (zox_has(e, RenderTexture)) {
                set_render_texture_gpu(textureGPULink->value, canvas_size);
                const ecs_entity_t camera = zox_get_value(e, CameraLink)
                if (zox_has(camera, FrameBufferLink)) {
                    const uint fbo = zox_get_value(camera, FrameBufferLink)
                    connect_render_texture_to_fbo(fbo, textureGPULink->value);
                } else {
                    zox_log(" ! render_texture connected to invalid render camera [%s]\n", zox_get_name(camera))
                }
            }
        }
        initializeElement->value = 0;
        meshDirty->value = mesh_state_trigger2; // mesh_state_upload;
    }
} zox_declare_system(Element2DMeshSystem)
