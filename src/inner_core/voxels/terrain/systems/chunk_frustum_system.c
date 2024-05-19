void ChunkFrustumSystem(ecs_iter_t *it) {
    zox_statistics_chunks_total += it->count;
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
        const bounds chunk_bounds = calculate_chunk_bounds(position3D->value, chunkSize->value, voxScale->value);
        unsigned char is_viewed = 1;
        ecs_iter_t it2 = ecs_query_iter(world, it->ctx);
        while(ecs_query_next(&it2)) {
            const Position3DBounds *position3DBoundss = ecs_field(&it2, Position3DBounds, 1);
            const CameraPlanes *cameraPlaness = ecs_field(&it2, CameraPlanes, 2);
            for (int j = 0; j < it2.count; j++) {
                const Position3DBounds *position3DBounds = &position3DBoundss[j];
                is_viewed = is_bounds_in_position_bounds(position3DBounds->value, chunk_bounds);
                //const CameraPlanes *cameraPlanes = &cameraPlaness[j];
                //is_viewed = is_in_frustum(cameraPlanes->value, chunk_bounds);
#ifdef zox_disable_frustum_checks
                is_viewed = 1;
#endif
                if (is_viewed) break;
            }
            if (is_viewed) break;
        }
        renderDisabled->value = !is_viewed;
        if (is_viewed) zox_statistics_chunks_visible++;
    }
    // zox_log(" > rendering  [%i] out of [%i]\n", zox_statistics_chunks_visible, zox_statistics_chunks_total)
} zox_declare_system(ChunkFrustumSystem)
