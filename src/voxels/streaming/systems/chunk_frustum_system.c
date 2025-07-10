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
        if (!is_linked_ChunkOctree(node)) {
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
    zox_sys_query()
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(Position3D)
    zox_sys_in(ChunkSize)
    zox_sys_in(VoxScale)
    zox_sys_in(EntityLinks)
    zox_sys_in(ChunkOctree)
    zox_sys_in(NodeDepth)
    zox_sys_out(RenderDisabled)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Position3D, position3D)
        zox_sys_i(ChunkSize, chunkSize)
        zox_sys_i(VoxScale, voxScale)
        zox_sys_i(EntityLinks, entityLinks)
        zox_sys_i(ChunkOctree, chunkOctree)
        zox_sys_i(NodeDepth, nodeDepth)
        zox_sys_o(RenderDisabled, renderDisabled)
        bounds chunk_bounds = calculate_chunk_bounds(position3D->value, chunkSize->value, voxScale->value);
        float3_multiply_float_p(&chunk_bounds.extents, fudge_frustum_extents);
        byte is_viewed = 0; // 1;
        zox_sys_query_begin()
        while (zox_sys_query_loop()) {
            if (is_viewed) {
                continue;
            }
            const Position3DBounds *position3DBoundss = ecs_field(&it2, Position3DBounds, 1);
            const CameraPlanes *cameraPlaness = ecs_field(&it2, CameraPlanes, 2);
            for (int j = 0; j < it2.count; j++) {
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
        zox_sys_query_end()
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
                set_chunk_block_spawns_render_disabled(world, chunkOctree, nodeDepth->value, 0, renderDisabled->value);
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