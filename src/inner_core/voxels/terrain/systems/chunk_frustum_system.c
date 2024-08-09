const float fudge_frustum_extents = 2.0f;
// this sets RenderDisabled for chunks and their children
void ChunkFrustumSystem(ecs_iter_t *it) {
#ifdef zox_disable_frustum_culling
    return;
#endif
    zox_iter_world()
    zox_field_in(Position3D, position3Ds, 1)
    zox_field_in(ChunkSize, chunkSizes, 2)
    zox_field_in(VoxScale, voxScales, 3)
    zox_field_in(EntityLinks, entityLinkss, 4)
    // zox_field_in(BlockSpawns, blockSpawnss, 5)
    zox_field_out(RenderDisabled, renderDisableds, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Position3D, position3Ds, position3D)
        zox_field_i(ChunkSize, chunkSizes, chunkSize)
        zox_field_i(VoxScale, voxScales, voxScale)
        zox_field_i(EntityLinks, entityLinkss, entityLinks)
        // zox_field_i(BlockSpawns, blockSpawnss, blockSpawns)
        zox_field_o(RenderDisabled, renderDisableds, renderDisabled)
        // const unsigned char block_spawns_initialized = blockSpawns->value && blockSpawns->value->data;
        bounds chunk_bounds = calculate_chunk_bounds(position3D->value, chunkSize->value, voxScale->value);
        float3_multiply_float_p(&chunk_bounds.extents, fudge_frustum_extents);
        unsigned char is_viewed = 1;
        ecs_iter_t it2 = ecs_query_iter(world, it->ctx);
        while(ecs_query_next(&it2)) {
            const Position3DBounds *position3DBoundss = ecs_field(&it2, Position3DBounds, 1);
#ifndef zox_disable_frustum_planes
            const CameraPlanes *cameraPlaness = ecs_field(&it2, CameraPlanes, 2);
#endif
            for (int j = 0; j < it2.count; j++) {
                const Position3DBounds *position3DBounds = &position3DBoundss[j];
                is_viewed = is_bounds_in_position_bounds(position3DBounds->value, chunk_bounds);
#ifndef zox_disable_frustum_planes
                if (is_viewed) {
                    const CameraPlanes *cameraPlanes = &cameraPlaness[j];
                    is_viewed = is_in_frustum(cameraPlanes->value, chunk_bounds);
                }
#endif
#ifdef zox_disable_frustum_checks
                is_viewed = 1;
#endif
                if (is_viewed) break;
            }
            if (is_viewed) break;
        }
        ecs_iter_fini(&it2);
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
// -=- Block Spawns -=-
            /* if (block_spawns_initialized) {
                for (int j = 0; j < blockSpawns->value->size; j++) {
                    const byte3_hashmap_pair* pair = blockSpawns->value->data[j];
                    uint checks = 0;
                    while (pair != NULL && checks < max_safety_checks_hashmap) {
                        const ecs_entity_t e2 = pair->value;
                        if (e2 && zox_valid(e2)) zox_set(e2, RenderDisabled, { renderDisabled->value })
                        pair = pair->next;
                        checks++;
                    }
                }
            }*/
// -=- -=- -=- -=- -=- -=-
        }
        // int block_spawns_count = block_spawns_initialized ? count_byte3_hashmap(blockSpawns->value) : 0;
        if (is_viewed) {
            zox_statistics_chunks_visible++;
            zox_statistics_characters_visible += entityLinks->length;
            // if (block_spawns_initialized) zox_statistics_block_voxes_visible += block_spawns_count;
        }
        zox_statistics_characters_total += entityLinks->length;
        // zox_statistics_block_voxes_total += block_spawns_count;
    }
    zox_statistics_chunks_total += it->count;
} zox_declare_system(ChunkFrustumSystem)
