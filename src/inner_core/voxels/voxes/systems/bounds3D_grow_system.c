void Bounds3DGrowSystem(ecs_iter_t *it) {
    zox_field_in(MeshDirty, meshDirtys, 1)
    zox_field_in(ChunkSize, chunkSizes, 2)
    zox_field_in(VoxScale, voxScales, 3)
    zox_field_out(Bounds3D, bounds3Ds, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(MeshDirty, meshDirtys, meshDirty)
        if (meshDirty->value == mesh_state_none) continue;
        zox_field_i(ChunkSize, chunkSizes, chunkSize)
        zox_field_i(VoxScale, voxScales, voxScale)
        zox_field_o(Bounds3D, bounds3Ds, bounds3D)
        bounds3D->value = calculate_vox_bounds(chunkSize->value, voxScale->value);
    }
} zox_declare_system(Bounds3DGrowSystem)
