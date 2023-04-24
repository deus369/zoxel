float3 calculate_vox_bounds(int3 chunk_size) {
    return (float3) { 0.5f * chunk_size.x * model_scale,
        0.5f * chunk_size.y * model_scale, 0.5f * chunk_size.z * model_scale };
}

void Bounds3DGrowSystem(ecs_iter_t *it) {
    const MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 1);
    const ChunkSize *chunkSizes = ecs_field(it, ChunkSize, 2);
    Bounds3D *bounds3Ds = ecs_field(it, Bounds3D, 3);
    for (int i = 0; i < it->count; i++) {
        const MeshDirty *meshDirty = &meshDirtys[i];
        if (meshDirty->value) {
            const ChunkSize *chunkSize = &chunkSizes[i];
            Bounds3D *bounds3D = &bounds3Ds[i];
            bounds3D->value = calculate_vox_bounds(chunkSize->value);
            // zoxel_log(" > bounds3D->value.y %f\n", bounds3D->value.y);
        }
    }
}
zoxel_declare_system(Bounds3DGrowSystem)