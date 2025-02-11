void ColorsGPULinkRestoreSystem(ecs_iter_t *it) {
    zox_field_out(ColorsGPULink, colorsGPULinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(ColorsGPULink, colorsGPULinks, colorsGPULink)
        colorsGPULink->value = spawn_gpu_generic_buffer();
    }
} zox_declare_system(ColorsGPULinkRestoreSystem)
