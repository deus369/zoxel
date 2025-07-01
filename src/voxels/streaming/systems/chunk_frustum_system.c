const float fudge_frustum_extents = 2.0f;
/*extern int zox_statistics_chunks_visible;
extern int zox_statistics_chunks_total;
extern int zox_statistics_characters_visible;
extern int zox_statistics_characters_total;*/

// Note: uses zox_set here for children setting

// block spawn delve function
void set_chunk_block_spawns_render_disabled(ecs_world_t *world, const ChunkOctree *node, const byte max_depth, byte depth, const byte state) {
    if (!node->nodes) {
        return;
    }
    if (depth == max_depth) {
        if (!is_linking_ChunkOctree(node)) {
            return;
        }
        NodeEntityLink *node_entity_link = (NodeEntityLink*) node->nodes;
        if (!node_entity_link) {
            return;
        }
        // get block_vox from nodes
        const ecs_entity_t block_vox = node_entity_link->value;
        if (zox_valid(block_vox)) {
            zox_set(block_vox, RenderDisabled, { state })
        }
    } else {
        depth++;
        for (int i = 0; i < 8; i++) {
            set_chunk_block_spawns_render_disabled(world, &node->nodes[i], max_depth, depth, state);
        }
    }
}

// this sets RenderDisabled for chunks and their children
void ChunkFrustumSystem(ecs_iter_t *it) {
    ecs_query_t *query = it->ctx;
    if (!query) {
        return;
    }
    zox_field_world()
    zox_field_in(Position3D, position3Ds, 1)
    zox_field_in(ChunkSize, chunkSizes, 2)
    zox_field_in(VoxScale, voxScales, 3)
    zox_field_in(EntityLinks, entityLinkss, 4)
    zox_field_in(ChunkOctree, chunkOctrees, 5)
    zox_field_out(RenderDisabled, renderDisableds, 6)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Position3D, position3Ds, position3D)
        zox_field_i(ChunkSize, chunkSizes, chunkSize)
        zox_field_i(VoxScale, voxScales, voxScale)
        zox_field_i(EntityLinks, entityLinkss, entityLinks)
        zox_field_o(RenderDisabled, renderDisableds, renderDisabled)
        bounds chunk_bounds = calculate_chunk_bounds(position3D->value, chunkSize->value, voxScale->value);
        float3_multiply_float_p(&chunk_bounds.extents, fudge_frustum_extents);
        byte is_viewed = 0; // 1;
        ecs_iter_t streamers_iter = ecs_query_iter(world, query);
        while (ecs_query_next(&streamers_iter)) {
            if (is_viewed) {
                continue;
            }
            const Position3DBounds *position3DBoundss = ecs_field(&streamers_iter, Position3DBounds, 1);
            const CameraPlanes *cameraPlaness = ecs_field(&streamers_iter, CameraPlanes, 2);
            for (int j = 0; j < streamers_iter.count; j++) {
                const Position3DBounds *position3DBounds = &position3DBoundss[j];
                is_viewed = is_bounds_in_position_bounds(position3DBounds->value, chunk_bounds);
                if (is_viewed) {
                    const CameraPlanes *cameraPlanes = &cameraPlaness[j];
                    is_viewed = is_in_frustum(cameraPlanes->value, chunk_bounds);
                }
                if (is_viewed) {
                    break;
                }
            }
        }
        ecs_iter_fini(&streamers_iter);
        if (renderDisabled->value != !is_viewed) {
            renderDisabled->value = !is_viewed;
            for (int j = 0; j < entityLinks->length; j++) {
                const ecs_entity_t e2 = entityLinks->value[j];
                zox_set(e2, RenderDisabled, { renderDisabled->value })
                if (!zox_has(e2, ElementLinks)) {
                    continue;
                }
                const ElementLinks *entity_elements = zox_get(e2, ElementLinks)
                for (int k = 0; k < entity_elements->length; k++) {
                    const ecs_entity_t e3 = entity_elements->value[k];
                    zox_set(e3, RenderDisabled, { renderDisabled->value })
                    if (!zox_has(e3, Children)) {
                        continue;
                    }
                    const Children *element_children = zox_get(e3, Children)
                    for (int l = 0; l < element_children->length; l++) {
                        const ecs_entity_t e4 = element_children->value[l];
                        zox_set(e4, RenderDisabled, { renderDisabled->value })
                    }
                }
            }
// -=- Block Spawns -=-
            if (zox_gett_value(it->entities[i], BlocksSpawned)) {
                zox_field_i(ChunkOctree, chunkOctrees, chunkOctree)
                set_chunk_block_spawns_render_disabled(world, chunkOctree, chunkOctree->max_depth, 0, renderDisabled->value);
            }
// -=- -=- -=- -=- -=- -=-
        }
        //if (is_viewed) {
            //zox_statistics_chunks_visible++;
            //zox_statistics_characters_visible += entityLinks->length;
        //}
        //zox_statistics_characters_total += entityLinks->length;
    }
    //zox_statistics_chunks_total += it->count;
} zox_declare_system(ChunkFrustumSystem)