void MeshGPUDisposeSystem(iter *it) {
    zox_sys_begin()
    zox_sys_in(MeshGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(MeshGPULink, meshGPULink)
        if (meshGPULink->value.x != 0) {
            glDeleteBuffers(1, &meshGPULink->value.x);
        }
        if (meshGPULink->value.y != 0) {
            glDeleteBuffers(1, &meshGPULink->value.y);
        }
    }
} zoxd_system(MeshGPUDisposeSystem)
