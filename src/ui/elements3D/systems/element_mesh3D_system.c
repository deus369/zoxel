void Element3DMeshSystem(ecs_iter_t *it) {
    zox_field_out(InitializeElement, initializeElements, 4)
    zox_field_out(MeshDirty, meshDirtys, 5)
    zox_field_out(MeshGPULink, meshGPULinks, 7)
    zox_field_out(UvsGPULink, uvsGPULinks, 8)
    zox_field_out(ColorsGPULink, colorsGPULinks, 9)
    zox_field_out(TextureGPULink, textureGPULinks, 10)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(InitializeElement, initializeElements, initializeElement)
        if (!initializeElement->value) {
            continue;
        }
        zox_field_o(MeshDirty, meshDirtys, meshDirty)
        if (meshDirty->value) {
            continue;
        }
        initializeElement->value = 0;
        meshDirty->value = mesh_state_trigger;
        if (!headless) {
            zox_field_o(MeshGPULink, meshGPULinks, meshGPULink)
            zox_field_o(TextureGPULink, textureGPULinks, textureGPULink)
            zox_field_o(UvsGPULink, uvsGPULinks, uvsGPULink)
            zox_field_o(ColorsGPULink, colorsGPULinks, colorsGPULink)
            meshGPULink->value = spawn_gpu_mesh_buffers();
            textureGPULink->value = spawn_gpu_texture_buffer();
            uvsGPULink->value = spawn_gpu_generic_buffer();
            colorsGPULink->value = spawn_gpu_generic_buffer();
        }
        zox_log_elements3D("+ updated mesh for element3D [%lu]", it->entities[i])
    }
} zox_declare_system(Element3DMeshSystem)