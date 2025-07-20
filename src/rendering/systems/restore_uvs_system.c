void UvsGPULinkRestoreSystem(ecs_iter_t *it) {
    zox_field_out(UvsGPULink, uvsGPULinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(UvsGPULink, uvsGPULinks, uvsGPULink)
        uvsGPULink->value = spawn_gpu_generic_buffer();
    }
} zox_declare_system(UvsGPULinkRestoreSystem)