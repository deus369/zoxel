float3 calculate_vox_bounds(const int3 chunk_size) {
    float3 vox_bounds = float3_from_int3(chunk_size);
    float3_multiply_float_p(&vox_bounds, 0.5f * model_scale);
    return vox_bounds;
}

void Bounds3DGrowSystem(ecs_iter_t *it) {
    zox_field_in(MeshDirty, meshDirtys, 1)
    zox_field_in(ChunkSize, chunkSizes, 2)
    zox_field_out(Bounds3D, bounds3Ds, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(MeshDirty, meshDirtys, meshDirty)
        if (!meshDirty->value) continue;
        zox_field_i_in(ChunkSize, chunkSizes, chunkSize)
        zox_field_i_out(Bounds3D, bounds3Ds, bounds3D)
        bounds3D->value = calculate_vox_bounds(chunkSize->value);
    }
} zox_declare_system(Bounds3DGrowSystem)
