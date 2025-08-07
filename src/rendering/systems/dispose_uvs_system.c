void MeshUvsGPUDisposeSystem(iter *it) {
    zox_sys_begin()
    zox_sys_in(UvsGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(UvsGPULink, uvsGPULink)
        if (uvsGPULink->value != 0) {
            glDeleteBuffers(1, &uvsGPULink->value);
        }
    }
} zox_declare_system(MeshUvsGPUDisposeSystem)