void MeshDirtyRestoreSystem(ecs_iter_t *it) {
    zox_field_out(MeshDirty, meshDirtys, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(MeshDirty, meshDirtys, meshDirty)
        meshDirty->value = 1;
    }
} zox_declare_system(MeshDirtyRestoreSystem)
