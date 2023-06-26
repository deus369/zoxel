// used for resource management
void MeshGPUDisposeSystem(ecs_iter_t *it) {
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 1);
    const ColorsGPULink *colorsGPULinks = ecs_field(it, ColorsGPULink, 2);
    for (int i = 0; i < it->count; i++) {
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        const ColorsGPULink *colorsGPULink = &colorsGPULinks[i];
        if (meshGPULink->value.x != 0) glDeleteBuffers(1, &meshGPULink->value.x);
        if (meshGPULink->value.y != 0) glDeleteBuffers(1, &meshGPULink->value.y);
        if (colorsGPULink->value != 0) glDeleteBuffers(1, &colorsGPULink->value);
    }
} zox_declare_system(MeshGPUDisposeSystem)

void MeshGPURestoreSystem(ecs_iter_t *it) {
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 1);
    for (int i = 0; i < it->count; i++) {
        MeshDirty *meshDirty = &meshDirtys[i];
        meshDirty->value = 1;
    }
} zox_declare_system(MeshGPURestoreSystem)