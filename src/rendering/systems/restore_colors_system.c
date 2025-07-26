void ColorsGPULinkRestoreSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_out(ColorsGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(ColorsGPULink, colorsGPULink)
        colorsGPULink->value = spawn_gpu_generic_buffer();
    }
} zox_declare_system(ColorsGPULinkRestoreSystem)
