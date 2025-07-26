const float fudge_frustum_extents = 2.0f;
/*extern int zox_statistics_chunks_visible;
extern int zox_statistics_chunks_total;
extern int zox_statistics_characters_visible;
extern int zox_statistics_characters_total;*/

// Note: uses zox_set here for children setting

// note: I may need to thread lock/unlock EntityLinks when reading

// block spawn delve function
void set_chunk_block_spawns_render_disabled(ecs_world_t *world, const VoxelNode *node, const byte state) {
    if (is_closed_VoxelNode(node)) {
        return;
    } else if (is_linked_VoxelNode(node)) {
        const ecs_entity_t e = get_entity_VoxelNode(node);
        if (zox_valid(e)) {
            zox_set(e, RenderDisabled, { state })
        }
    } else if (has_children_VoxelNode(node)) {
        VoxelNode* kids = get_children_VoxelNode(node);
        for (int i = 0; i < octree_length; i++) {
            set_chunk_block_spawns_render_disabled(world, &kids[i], state);
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
    zox_sys_in(VoxelNode)
    // zox_sys_in(NodeDepth)
    zox_sys_out(RenderDisabled)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(Position3D, position3D)
        zox_sys_i(ChunkSize, chunkSize)
        zox_sys_i(VoxScale, voxScale)
        zox_sys_i(EntityLinks, entityLinks)
        zox_sys_i(VoxelNode, voxelNode)
        // zox_sys_i(NodeDepth, nodeDepth)
        zox_sys_o(RenderDisabled, renderDisabled)
        // const float terrain_mesh_scale = get_terrain_voxel_scale(nodeDepth->value);
        bounds chunk_bounds = calculate_chunk_bounds(
            position3D->value,
            chunkSize->value,
            voxScale->value * 0.5f);
        float3_scale_p(&chunk_bounds.extents, fudge_frustum_extents);
        zox_sys_query_begin()
        byte is_viewed = 0;
        while (zox_sys_query_loop()) {
            if (is_viewed) {
                continue;
            }
            zox_sys_begin_2()
            zox_sys_in_2(Position3DBounds)
            zox_sys_in_2(CameraPlanes)
            for (int j = 0; j < it2.count; j++) {
                zox_sys_i_2(Position3DBounds, position3DBounds)
                zox_sys_i_2(CameraPlanes, cameraPlanes)
                is_viewed = is_bounds_in_position_bounds(position3DBounds->value, chunk_bounds);
                if (is_viewed) {
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
            // -=- Block Spawns -=-
            if (zox_gett_value(e, BlocksSpawned)) {
                set_chunk_block_spawns_render_disabled(world, voxelNode, renderDisabled->value);
            }
            // -=- -=- -=- -=- -=- -=-
            for (int j = 0; j < entityLinks->length; j++) {
                const ecs_entity_t e2 = entityLinks->value[j];
                zox_set(e2, RenderDisabled, { renderDisabled->value })
                if (!zox_valid(e2) || !zox_has(e2, ElementLinks)) {
                    continue;
                }
                zox_geter(e2, ElementLinks, entity_elements)
                for (int k = 0; k < entity_elements->length; k++) {
                    const ecs_entity_t e3 = entity_elements->value[k];
                    if (!zox_valid(e3)) {
                        continue;
                    }
                    zox_set(e3, RenderDisabled, { renderDisabled->value })
                    if (!zox_has(e3, Children)) {
                        continue;
                    }
                    zox_geter(e3, Children, element_children)
                    for (int l = 0; l < element_children->length; l++) {
                        const ecs_entity_t e4 = element_children->value[l];
                        zox_set(e4, RenderDisabled, { renderDisabled->value })
                    }
                }
            }
        }
    }
} zox_declare_system(ChunkFrustumSystem)