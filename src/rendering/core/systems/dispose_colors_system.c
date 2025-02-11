void MeshColorsGPUDisposeSystem(ecs_iter_t *it) {
    zox_field_in(ColorsGPULink, colorsGPULinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ColorsGPULink, colorsGPULinks, colorsGPULink)
        if (colorsGPULink->value != 0) glDeleteBuffers(1, &colorsGPULink->value);
    }
} zox_declare_system(MeshColorsGPUDisposeSystem)
