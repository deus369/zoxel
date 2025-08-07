void MeshColorsGPUDisposeSystem(iter *it) {
    zox_sys_begin()
    zox_sys_in(ColorsGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ColorsGPULink, colorsGPULink)
        if (colorsGPULink->value != 0) {
            glDeleteBuffers(1, &colorsGPULink->value);
        }
    }
} zox_declare_system(MeshColorsGPUDisposeSystem)
