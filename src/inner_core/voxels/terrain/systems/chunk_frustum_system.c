void ChunkFrustumSystem(ecs_iter_t *it) {
    zox_statistics_chunks_total += it->count;
    zox_iter_world()
    zox_field_in(Position3D, position3Ds, 1)
    zox_field_in(ChunkSize, chunkSizes, 2)
    zox_field_in(VoxScale, voxScales, 3)
    zox_field_in(EntityLinks, entityLinkss, 4)
    zox_field_out(RenderDisabled, renderDisableds, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Position3D, position3Ds, position3D)
        zox_field_i_in(ChunkSize, chunkSizes, chunkSize)
        zox_field_i_in(VoxScale, voxScales, voxScale)
        zox_field_i_in(EntityLinks, entityLinkss, entityLinks)
        zox_field_i_out(RenderDisabled, renderDisableds, renderDisabled)
        const bounds chunk_bounds = calculate_chunk_bounds(position3D->value, chunkSize->value, voxScale->value);
        unsigned char is_viewed = 1;
        ecs_iter_t it2 = ecs_query_iter(world, it->ctx);
        while(ecs_query_next(&it2)) {
            const Position3DBounds *position3DBoundss = ecs_field(&it2, Position3DBounds, 1);
            // const CameraPlanes *cameraPlaness = ecs_field(&it2, CameraPlanes, 2);
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
        if (renderDisabled->value != !is_viewed) {
            renderDisabled->value = !is_viewed;
            for (int j = 0; j < entityLinks->length; j++) {
                const ecs_entity_t e2 = entityLinks->value[j];
                zox_set(e2, RenderDisabled, { renderDisabled->value })
                if (!zox_has(e2, ElementLinks)) continue;
                const ElementLinks *entity_elements = zox_get(e2, ElementLinks)
                for (int k = 0; k < entity_elements->length; k++) {
                    const ecs_entity_t e3 = entity_elements->value[k];
                    zox_set(e3, RenderDisabled, { renderDisabled->value })
                    if (!zox_has(e3, Children)) continue;
                    const Children *element_children = zox_get(e3, Children)
                    for (int l = 0; l < element_children->length; l++) {
                        const ecs_entity_t e4 = element_children->value[l];
                        zox_set(e4, RenderDisabled, { renderDisabled->value })
                    }
                }
            }
        }
        if (is_viewed) {
            zox_statistics_chunks_visible++;
            zox_statistics_characters_visible += entityLinks->length;
        }
        zox_statistics_characters_total += entityLinks->length;
    }
} zox_declare_system(ChunkFrustumSystem)
