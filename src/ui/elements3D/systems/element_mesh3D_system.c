void Element3DMeshSystem(iter *it) {
    zox_sys_begin()
    zox_sys_out(InitializeElement)
    zox_sys_out(MeshDirty)
    zox_sys_out(MeshGPULink)
    zox_sys_out(UvsGPULink)
    zox_sys_out(ColorsGPULink)
    zox_sys_out(TextureGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(InitializeElement, initializeElement)
        zox_sys_o(MeshDirty, meshDirty)
        zox_sys_o(MeshGPULink, meshGPULink)
        zox_sys_o(TextureGPULink, textureGPULink)
        zox_sys_o(UvsGPULink, uvsGPULink)
        zox_sys_o(ColorsGPULink, colorsGPULink)
        if (!initializeElement->value || meshDirty->value) {
            continue;
        }
        if (!headless) {
            meshGPULink->value = spawn_gpu_mesh_buffers();
            textureGPULink->value = spawn_gpu_texture_buffer();
            uvsGPULink->value = spawn_gpu_generic_buffer();
            colorsGPULink->value = spawn_gpu_generic_buffer();
        }
        meshDirty->value = mesh_state_trigger;
        initializeElement->value = 0;
        zox_log_elements3D("+ updated mesh for element3D [%lu]", it->entities[i])
    }
} zoxd_system(Element3DMeshSystem)