// Doing: Keeping in one place, making iteration easier

// todo: keep this in hashmap for processed Voxes - atm its gonna check 10k chunks * voxels length which is bad
// todo: support for multiple terrains using hashmap

byte zox_disable_node_face_subdivision = 1;
define_fun_stopwatch(time_chunk3_build, 0);

// remember: vertex offset is just node position / voxel position

// #define zox_octree_chunk_build_limits

// static data
typedef struct {
    // vox data
    // const float scale; // overall scale
    byte edge_voxel;
    // voxels
    const TilemapUVs *tilemap_uvs;
    const byte *voxel_solidity;
    const int *voxel_uv_indexes;
    // neighbor data
    const VoxelNode **neighbors;
    const byte *ndepths;
    // chunk data
    const VoxelNode *root;
    // const byte is_max_depth_chunk;  // is chunk highest lod
    const byte render_depth;
    const byte node_depth;
    const mesh_uvs_build_data *mesh_data;
} terrain_build_data;

// changing data
typedef struct {
    // node data
    const VoxelNode *parent;
    const VoxelNode *node;
    byte depth;
    int3 position;
    float scale;
    byte index;
    byte voxel;
    // face data
    byte direction;
    float3 offset;
    byte3 local_position;
} octree_dig_data;

typedef struct {
    const int* indicies;
    const float3 *vertices;
    const float2 *uvs;
} octree_face_data;

// this takes 14ms on a 24core cpu, 6ms though during streaming
// scales vertex, offsets vertex by voxel position in chunk, adds total mesh offset
void zox_build_voxel_face(
    const mesh_uvs_build_data *mesh_data,
    const byte voxel,
    const int* voxel_face_indicies,
    const float3* voxel_face_vertices,
    const float2* voxel_face_uvs,
    const byte direction,
    const float3 offset,
    const float scale
) {
    // indicies
    expand_capacity_int_array_d(mesh_data->indicies, voxel_face_indicies_length);
    for (byte i = 0; i < 6; i++) {
        mesh_data->indicies->data[mesh_data->indicies->size + i] = mesh_data->vertices->size + voxel_face_indicies[i];
    }
    mesh_data->indicies->size += voxel_face_indicies_length;
    // verts
    expand_capacity_float3_array_d(mesh_data->vertices, voxel_face_vertices_length);
    for (byte i = 0; i < 4; i++) {
        float3 vertex_position = voxel_face_vertices[i];
        float3_add_float3_p(&vertex_position, offset);
        float3_scale_p(&vertex_position, scale);
        mesh_data->vertices->data[mesh_data->vertices->size + i] = vertex_position;
    }
    mesh_data->vertices->size += voxel_face_vertices_length;
    // uvs
    expand_capacity_float2_array_d(mesh_data->uvs, voxel_face_vertices_length);
    for (byte i = 0; i < 4; i++) {
        const float2 vert_uv = voxel_face_uvs[i];
        mesh_data->uvs->data[mesh_data->uvs->size + i] = vert_uv;
    }
    mesh_data->uvs->size += voxel_face_vertices_length;
    // colors
    for (byte a = 0; a < voxel_face_vertices_length; a++) {
        color_rgb vertex_color = color_rgb_white;
#ifndef zox_disable_fake_voxel_lighting
        if (direction == direction_down) {
            color_rgb_multiply_float(&vertex_color, 0.33f);
        } else if (direction == direction_front) {
            color_rgb_multiply_float(&vertex_color, 0.44f);
        } else if (direction == direction_left) {
            color_rgb_multiply_float(&vertex_color, 0.55f);
        } else if (direction == direction_back) {
            color_rgb_multiply_float(&vertex_color, 0.66f);
        } else if (direction == direction_right) {
            color_rgb_multiply_float(&vertex_color, 0.76f);
        }
#endif
        add_to_color_rgb_array_d(mesh_data->color_rgbs, vertex_color);
    }
}

// this function accounts for size of drawing voxels
void build_voxel_mesh_final(
    const terrain_build_data data,
    octree_dig_data dig,
    octree_face_data face
) {
    /*byte adepth = get_adjacent_depth_VoxelNode(
        data.ndepths,
        dig.position,
        dig.depth,      // data.render_depth,
        dig.direction);*/
    // Node finished at: dig.depth
    // Rendering at: data.render_depth
    /*byte adjacent_air = !is_adjacent_all_solid(
        data.voxel_solidity,
        data.edge_voxel,
        data.neighbors,
        data.ndepths,
        data.root,
        dig.position,
        dig.direction,
        dig.depth   // dig.depth adepth data.render_depth
    );
    if (!adjacent_air) {
        return;
    }*/
    byte is_regular_build = 1;
    // Splits Node Quad up!
    /*byte is_maxxed = data.render_depth == dig.depth;
    if (!zox_disable_node_face_subdivision && !is_maxxed) {
        // so far just increasing face draw resolution for up faces
        int depth_difference = data.render_depth - dig.depth;
        if (depth_difference != 0) {
            is_regular_build = 0;
            // this checks per voxel position if voxel is solid next to it
            int3 scaled_octree_position = dig.position;
            const int amplify_position = pow(2, depth_difference);
            if (amplify_position != 1) {
                int3_multiply_int_p(&scaled_octree_position, amplify_position);
            }
            int3 position = int3_zero;
            // place at top of current scale building
            if (dig.direction == direction_up) {
                position.y = (dig.scale - 1);
            } else if (dig.direction == direction_right) {
                position.x = (dig.scale - 1);
            } else if (dig.direction == direction_front) {
                position.z = (dig.scale - 1);
            }
            // three edge cases
            if (dig.direction == direction_up || dig.direction == direction_down) { // y
                for (position.x = 0; position.x < dig.scale; position.x++) {
                    for (position.z = 0; position.z < dig.scale; position.z++) {
                        int3 global_octree_position = scaled_octree_position;
                        int3_add_int3(&global_octree_position, position);
                        if (is_adjacent_solid(
                            dig.direction,
                            data.root,
                            data.neighbors,
                            global_octree_position,
                            data.render_depth,
                            data.edge_voxel,
                            data.voxel_solidity)
                        ) {
                            continue;
                        }
                        zox_build_voxel_face(
                            data.mesh_data,
                            dig.voxel,
                            face.indicies,
                            face.vertices,
                            face.uvs,
                            dig.direction,
                            float3_from_int3(global_octree_position),
                            data.scale);
                    }
                }
            } else if (dig.direction == direction_left || dig.direction == direction_right) { // x
                for (position.y = 0; position.y < dig.scale; position.y++) {
                    for (position.z = 0; position.z < dig.scale; position.z++) {
                        int3 global_octree_position = scaled_octree_position;
                        int3_add_int3(&global_octree_position, position);
                        if (is_adjacent_solid(
                            dig.direction,
                            data.root,
                            data.neighbors,
                            global_octree_position,
                            data.render_depth,
                            data.edge_voxel,
                            data.voxel_solidity)
                        ) {
                            continue;
                        }
                        zox_build_voxel_face(
                            data.mesh_data,
                            dig.voxel,
                            face.indicies,
                            face.vertices,
                            face.uvs,
                            dig.direction,
                            float3_from_int3(global_octree_position),
                            data.scale);
                    }
                }
            } else { // z
                for (position.x = 0; position.x < dig.scale; position.x++) {
                    for (position.y = 0; position.y < dig.scale; position.y++) {
                        int3 global_octree_position = scaled_octree_position;
                        int3_add_int3(&global_octree_position, position);
                        if (is_adjacent_solid(
                            dig.direction,
                            data.root,
                            data.neighbors,
                            global_octree_position,
                            data.render_depth,
                            data.edge_voxel,
                            data.voxel_solidity)
                        ) {
                            continue;
                        }
                        zox_build_voxel_face(
                            data.mesh_data,
                            dig.voxel,
                            face.indicies,
                            face.vertices,
                            face.uvs,
                            dig.direction,
                            float3_from_int3(global_octree_position),
                            data.scale);
                    }
                }
            }
        }
    }*/

    if (is_regular_build) {
        // data.render_depth | dig.depth | adepth
        const byte adepth = get_adjacent_depth_VoxelNode(
            data.neighbors,
            data.ndepths,
            dig.position,
            data.render_depth,
            dig.direction);
        // get anode at the current dig depth
        const VoxelNode* anode = get_adjacentn_VoxelNode(
            data.neighbors,
            data.ndepths,
            data.root,
            dig.position,
            dig.depth,
            dig.direction
        );
        byte rdir = reverse_direction(dig.direction);
        // but this assume the adjacent node is rendering at max level!
        //  it checks for all sub nodes..!
        byte ddepth = adepth - dig.depth < 0 ? 0 : adepth - dig.depth;
        // byte ddepth = data.render_depth - dig.depth < 0 ? 0 : data.render_depth - dig.depth;
        // Handle Chunk Seems
        /*if (data.render_depth != adepth) {
            if (adepth > data.render_depth) {
                ddepth += 1;
            } else if (ddepth) {
                ddepth -= 1;
            }
        }*/

        // we need to know how far to check, using anodes depth
        byte adjacent_solid = get_node_sides_all_solid(
            data.voxel_solidity,
            anode,
            rdir,
            ddepth + 1);
        adjacent_solid = anode ? adjacent_solid : data.edge_voxel;

        if (!adjacent_solid) {
            zox_build_voxel_face(
                data.mesh_data,
                dig.voxel,
                face.indicies,
                face.vertices,
                face.uvs,
                dig.direction,
                dig.offset,
                dig.scale);
        }
    }
}

void zox_terrain_building_dig(
    const terrain_build_data data,
    octree_dig_data dig
) {
    if (dig.depth >= data.render_depth || is_closed_VoxelNode(dig.node)) {
        // we dig until depth is at render level or the node is closed
        if (dig.node->value && data.voxel_solidity[dig.node->value - 1]) {
            dig.voxel = dig.node->value;
            dig.offset = float3_from_int3(dig.position);
            // dig.scale = octree_scales3[dig.depth];
            dig.local_position = octree_positions_b[dig.index];
            const int voxel_uvs_index = (dig.voxel - 1) * 6;
            for (byte i = 0; i < 6; i++) {
                byte is_positive = (i + 1) % 2 == 0;
                if (i == block_side_down || i == block_side_up) {
                    is_positive = !is_positive;
                }
                dig.direction = i;
                int uv_index = data.voxel_uv_indexes[voxel_uvs_index + i];
                octree_face_data face = {
                    //.indicies = get_voxel_indices(is_positive),
                    //.vertices = voxel_face_vertices_n[i],
                    .indicies = voxel_face_indicies_n + i * voxel_face_indicies_length,
                    .vertices = voxel_face_vertices_n[i],
                    .uvs = &data.tilemap_uvs->value[uv_index],
                };

                build_voxel_mesh_final(data, dig, face);
            }
        }
    } else {
        // keep digging
        byte child_depth = dig.depth + 1;
        float child_scale = dig.scale * 0.5f;
        // zox_log_error("At [%i] Halved scale: %f", child_depth, child_scale);
        int3 position = dig.position;
        int3_multiply_int_p(&position, 2);
        // only dig for solid child nodes
        VoxelNode* kids = get_children_VoxelNode(dig.node);
        for (byte i = 0; i < 8; i++) {
            if (!kids[i].value) {
                continue;
            }
            int3 child_position = int3_add(position, octree_positions[i]);
            octree_dig_data child = {
                .parent = dig.node,
                .depth = child_depth,
                .scale = child_scale,
                // unique
                .node = &kids[i],
                .index = i,
                .position = child_position
            };
            zox_terrain_building_dig(data, child);
        }
    }
}

void build_chunk_terrain_mesh(
    const VoxelNode *node,
    const TilemapUVs *tilemap_uvs,
    MeshIndicies *meshIndicies,
    MeshVertices *meshVertices,
    MeshUVs *meshUVs,
    MeshColorRGBs *meshColorRGBs,
    // const byte is_max_depth_chunk,
    const byte render_depth,
    const VoxelNode **neighbors,
    const byte* ndepths,
    const byte *voxel_solidity,
    const int *voxel_uv_indexes,
    const float scale
) {
    const mesh_uvs_build_data mesh_data = {
        .indicies = create_int_array_d(initial_dynamic_array_size),
        .vertices = create_float3_array_d(initial_dynamic_array_size),
        .uvs = create_float2_array_d(initial_dynamic_array_size),
        .color_rgbs = create_color_rgb_array_d(initial_dynamic_array_size)
    };
    // build out mesh data
    const terrain_build_data data = {
        // vox data
        .tilemap_uvs = tilemap_uvs,
        .voxel_solidity = voxel_solidity,
        .voxel_uv_indexes = voxel_uv_indexes,
        .mesh_data = &mesh_data,
        // neighbor data
        .neighbors = neighbors,
        .ndepths = ndepths,
        // chunk data
        .root = node,
        // .is_max_depth_chunk = is_max_depth_chunk,
        .render_depth = render_depth,
#ifndef zox_disable_hidden_terrain_edge
        .edge_voxel = 1,
#endif
    };
    octree_dig_data dig = {
        .parent = NULL,
        .node = node,
        .scale = scale,
    };
    zox_terrain_building_dig(data, dig);
    // sizes
    meshIndicies->length = mesh_data.indicies->size;
    meshVertices->length = mesh_data.vertices->size;
    meshUVs->length = mesh_data.uvs->size;
    meshColorRGBs->length = mesh_data.color_rgbs->size;
    // data
    meshIndicies->value = zinalize_int_array_d(mesh_data.indicies);
    meshVertices->value = zinalize_float3_array_d(mesh_data.vertices);
    meshColorRGBs->value = zinalize_color_rgb_array_d(mesh_data.color_rgbs);
    meshUVs->value = zinalize_float2_array_d(mesh_data.uvs);
}

void fetch_neightbor_chunk_data(
    ecs_world_t* world,
    const ChunkNeighbors* chunkNeighbors,
    byte node_depth,
    const VoxelNode** neighbors,
    byte* ndepths
) {
    for (int i = 0; i < 6; i++) {
        const ecs_entity_t e = chunkNeighbors->value[i];
        if (!zox_valid(e) || !zox_has(e, RenderLod) || !zox_has(e, VoxelNode)) {
            ndepths[i] = 0;
            neighbors[i] = 0;
            continue;
        }
        neighbors[i] = zox_get(e, VoxelNode);
        zox_geter_value(e, RenderLod, byte, neighbor_lod);
        if (neighbor_lod == render_lod_invisible || neighbor_lod == render_lod_uninitialized) {
            ndepths[i] = 0;
        } else {
            ndepths[i] = terrain_lod_to_node_depth(neighbor_lod, node_depth);
        }
    }
}

void Chunk3BuildSystem(ecs_iter_t *it) {
    zox_ts_begin(chunk3_builder);
    uint updated_count = 0;
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(ChunkMeshDirty)
    zox_sys_in(VoxLink)
    zox_sys_in(VoxelNode)
    zox_sys_in(NodeDepth)
    zox_sys_in(RenderLod)
    zox_sys_in(ChunkNeighbors)
    zox_sys_in(VoxScale)
    zox_sys_out(MeshIndicies)
    zox_sys_out(MeshVertices)
    zox_sys_out(MeshUVs)
    zox_sys_out(MeshColorRGBs)
    zox_sys_out(MeshDirty)
    byte any_dirty = 0;
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ChunkMeshDirty, chunkMeshDirty)
        if (chunkMeshDirty->value == chunk_dirty_state_update) {
            any_dirty = 1;
            break;
        }
    }
    if (!any_dirty) {
        zox_ts_end(chunk3_builder, 3, zox_profile_system_chunk3_builder);
        return;
    }
    startwatch(time_chunk3_build);

    // cache terrain data
    int voxels_length = 0;
    ecs_entity_t terrain = 0;
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(VoxLink, voxLink)
        if (!voxLink->value) {
            continue;
        }
        terrain = voxLink->value;
        break;
    }
    if (!zox_valid(terrain) || !zox_has(terrain, RealmLink) || !zox_has(terrain, TilemapLink)) {
        zox_ts_end(chunk3_builder, 3, zox_profile_system_chunk3_builder);
        return;
    } // if failed to find terrain parents
    const ecs_entity_t realm = zox_get_value(terrain, RealmLink)
    if (!zox_valid(realm) || !zox_has(realm, VoxelLinks)) {
        zox_ts_end(chunk3_builder, 3, zox_profile_system_chunk3_builder);
        return;
    }
    zox_geter(realm, VoxelLinks, voxelLinks)
    voxels_length = voxelLinks->length;
    if (voxels_length == 0) {
        zox_ts_end(chunk3_builder, 3, zox_profile_system_chunk3_builder);
        return; // if failed to find terrain parents
    }
    const ecs_entity_t tilemap = zox_get_value(terrain, TilemapLink)
    if (!zox_valid(tilemap) || !zox_has(tilemap, TilemapUVs)) {
        zox_ts_end(chunk3_builder, 3, zox_profile_system_chunk3_builder);
        return;
    }
    zox_geter(tilemap, TilemapUVs, tilemap_uvs)
    if (tilemap_uvs->value == NULL || tilemap_uvs->length == 0) {
        // zox_log(" ! tilemap troubles in chunk building: %lu %i\n", tilemap, tilemap_uvs->length)
        zox_ts_end(chunk3_builder, 3, zox_profile_system_chunk3_builder);
        return; // if tilemap generating still
    }
    ChunkTexturedBuildData build_data;
    byte solidity[voxels_length];
    build_data.solidity = solidity;
    int uvs[voxels_length * 6]; //  * sizeof(int)];
    build_data.uvs = uvs;
    // calculate tileuv indexes - voxel and face to index  in tilemap_uvs
    int uvs_index = 0;
    for (int j = 0; j < voxels_length; j++) {
        const ecs_entity_t block = voxelLinks->value[j];
        if (!zox_valid(block)) {
            build_data.solidity[j] = 1;
            continue;
        }
        // solidity
        if (!zox_has(block, BlockModel)) {
            build_data.solidity[j] = 1;
        } else {
            build_data.solidity[j] = zox_gett_value(block, BlockModel) == zox_block_solid;
        }
        // uvs
        if (!zox_has(block, TextureLinks)) {
            continue;    // no textures...!
        }
        const byte block_textures_length = zox_gett(block, TextureLinks)->length;
        int voxel_uv_indexes_index = j * 6;
        if (block_textures_length == 1) {
            // per voxel, 24 uvs
            for (byte k = 0; k < 6; k++) {
                build_data.uvs[voxel_uv_indexes_index + k] = uvs_index;
                // uvs_index += 4;
            }
            uvs_index += 4;
        } else {
            // for 6 sides textured voxes
            for (byte k = 0; k < 6; k++) {
                build_data.uvs[voxel_uv_indexes_index + k] = uvs_index;
                uvs_index += 4;
            }
        }
    }


    for (int i = 0; i < it->count; i++) {
        zox_sys_i(VoxLink, voxLink)
        zox_sys_i(ChunkMeshDirty, chunkMeshDirty)
        zox_sys_i(ChunkNeighbors, chunkNeighbors)
        zox_sys_i(NodeDepth, nodeDepth)
        zox_sys_i(RenderLod, renderLod)
        zox_sys_i(VoxScale, voxScale)
        zox_sys_i(VoxelNode, voxelNode)
        zox_sys_o(MeshIndicies, meshIndicies)
        zox_sys_o(MeshVertices, meshVertices)
        zox_sys_o(MeshColorRGBs, meshColorRGBs)
        zox_sys_o(MeshUVs, meshUVs)
        zox_sys_o(MeshDirty, meshDirty)
        if (chunkMeshDirty->value != chunk_dirty_state_update) {
            continue;
        }
        if (renderLod->value == render_lod_uninitialized)  {
            zox_log_error("render_depth_uninitialized")
            continue;
        }
        clear_mesh_uvs(meshIndicies, meshVertices, meshColorRGBs, meshUVs);
        if (renderLod->value == render_lod_invisible) {
            meshDirty->value = mesh_state_trigger_slow;
            continue;
        }

        // zox_geter_value(voxLink->value, VoxScale, float, scale);
        zox_geter_value(voxLink->value, NodeDepth, byte, terrain_depth);
        const byte render_depth = terrain_lod_to_node_depth(
            renderLod->value,
            terrain_depth);
        byte node_depth = nodeDepth->value;
        byte terrain_length = powers_of_two[terrain_depth];
        // TODO: grab voxScale from terrain instead
        const float chunk_scale = ((float) terrain_length) * voxScale->value;
        // zox_log_error("At Len [%i] Start scale: %f", terrain_length, voxScale->value);
        // const float start_scale =  voxScale->value / ((float) length);
        // zox_log("building: chunk_scale [%f] voxscale [%f] terrain_length [%i]", chunk_scale, voxScale->value, terrain_length);

        const VoxelNode *neighbors[6];
        byte ndepths[6];
        fetch_neightbor_chunk_data(
            world,
            chunkNeighbors,
            node_depth,
            neighbors,
            ndepths);

        // const float scale = 2 * get_terrain_voxel_scale(node_depth);
        read_lock_VoxelNode(voxelNode);
        build_chunk_terrain_mesh(
            voxelNode,
            tilemap_uvs,
            meshIndicies,
            meshVertices,
            meshUVs,
            meshColorRGBs,
            render_depth,
            neighbors,
            ndepths,
            build_data.solidity,
            build_data.uvs,
            chunk_scale
        );
        read_unlock_VoxelNode(voxelNode);
        meshDirty->value = mesh_state_trigger_slow;
        tapwatch(time_chunk3_build, "built mesh");
        updated_count++;
    }

    if (updated_count > 0) {
        zox_log_streaming(" - [%i] updated [%i]", ecs_run_count, updated_count)
    }
    endwatch(time_chunk3_build, "ending");
    zox_ts_end(chunk3_builder, 3, zox_profile_system_chunk3_builder);
} zox_declare_system(Chunk3BuildSystem)