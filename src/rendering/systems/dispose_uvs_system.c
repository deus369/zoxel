void MeshUvsGPUDisposeSystem(ecs_iter_t *it) {
    zox_field_in(UvsGPULink, uvsGPULinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(UvsGPULink, uvsGPULinks, uvsGPULink)
        if (uvsGPULink->value != 0) glDeleteBuffers(1, &uvsGPULink->value);
    }
} zox_declare_system(MeshUvsGPUDisposeSystem)