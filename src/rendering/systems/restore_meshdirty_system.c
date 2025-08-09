void MeshDirtyRestoreSystem(iter *it) {
    zox_sys_begin()
    zox_sys_out(MeshDirty)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(MeshDirty, meshDirty)
        meshDirty->value = mesh_state_trigger;
    }
} zoxd_system(MeshDirtyRestoreSystem)
