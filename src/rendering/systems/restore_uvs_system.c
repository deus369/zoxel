void UvsGPULinkRestoreSystem(iter *it) {
    zox_sys_begin()
    zox_sys_out(UvsGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(UvsGPULink, uvsGPULink)
        uvsGPULink->value = spawn_gpu_generic_buffer();
    }
} zoxd_system(UvsGPULinkRestoreSystem)