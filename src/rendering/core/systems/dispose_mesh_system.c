void MeshGPUDisposeSystem(ecs_iter_t *it) {
    zox_field_in(MeshGPULink, meshGPULinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(MeshGPULink, meshGPULinks, meshGPULink)
        if (meshGPULink->value.x != 0) glDeleteBuffers(1, &meshGPULink->value.x);
        if (meshGPULink->value.y != 0) glDeleteBuffers(1, &meshGPULink->value.y);
    }
} zox_declare_system(MeshGPUDisposeSystem)
