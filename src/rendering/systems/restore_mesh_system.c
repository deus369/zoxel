void MeshGPURestoreSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_out(MeshGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(MeshGPULink, meshGPULink)
        meshGPULink->value.x = spawn_gpu_generic_buffer();
        meshGPULink->value.y = spawn_gpu_generic_buffer();
    }
} zox_declare_system(MeshGPURestoreSystem)