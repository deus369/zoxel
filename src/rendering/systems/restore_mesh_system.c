void MeshGPURestoreSystem(ecs_iter_t *it) {
    zox_field_out(MeshGPULink, meshGPULinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(MeshGPULink, meshGPULinks, meshGPULink)
        meshGPULink->value.x = spawn_gpu_generic_buffer();
        meshGPULink->value.y = spawn_gpu_generic_buffer();
    }
} zox_declare_system(MeshGPURestoreSystem)