
void MeshGPURestoreSystem(ecs_iter_t *it) {
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 1);
    for (int i = 0; i < it->count; i++) {
        MeshDirty *meshDirty = &meshDirtys[i];
        meshDirty->value = 1;
    }
} zox_declare_system(MeshGPURestoreSystem)