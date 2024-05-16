// pass in camera datas
void ChunkFrustumSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(Position3D, position3Ds, 1)
    zox_field_in(ChunkSize, chunkSizes, 2)
    zox_field_in(VoxScale, voxScales, 3)
    zox_field_out(RenderDisabled, renderDisableds, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Position3D, position3Ds, position3D)
        zox_field_i_in(ChunkSize, chunkSizes, chunkSize)
        zox_field_i_in(VoxScale, voxScales, voxScale)
        zox_field_i_out(RenderDisabled, renderDisableds, renderDisabled)
        float3 extents = float3_from_int3(chunkSize->value);
        float3_multiply_float_p(&extents, voxScale->value); //  * 0.5f);
        const float3 bounds_position = float3_add(extents, position3D->value);
        const bounds chunk_bounds = (bounds) { bounds_position, extents };
        ecs_iter_t it2 = ecs_query_iter(world, it->ctx);
        unsigned char is_viewed = 0;
        while(ecs_query_next(&it2)) {
            const CameraPlanes *cameraPlaness = ecs_field(&it2, CameraPlanes, 1);
            for (int j = 0; j < it2.count; j++) {
                const CameraPlanes *cameraPlanes = &cameraPlaness[j];
                is_viewed = is_in_frustum(cameraPlanes->value, chunk_bounds);
                if (is_viewed) break;
            }
            if (is_viewed) break;
        }
        renderDisabled->value = !is_viewed;
    }
} zox_declare_system(ChunkFrustumSystem)
