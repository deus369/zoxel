void Bounds3GrowSystem(iter *it) {
    zox_sys_begin()
    zox_sys_in(MeshDirty)
    zox_sys_in(ChunkSize)
    zox_sys_in(VoxScale)
    zox_sys_out(Bounds3D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(MeshDirty, meshDirty)
        zox_sys_i(ChunkSize, chunkSize)
        zox_sys_i(VoxScale, voxScale)
        zox_sys_o(Bounds3D, bounds3D)
        if (meshDirty->value == mesh_state_generate) {
            bounds3D->value = calculate_vox_bounds(chunkSize->value, voxScale->value);
        }
    }
} zoxd_system(Bounds3GrowSystem)