void fill_new_octree(ChunkOctree* node, const byte voxel, byte depth) {
    node->value = voxel;
    if (depth > 0) {
        depth--;
        open_new_ChunkOctree(node);
        for (byte i = 0; i < octree_length; i++) fill_new_octree(&node->nodes[i], voxel, depth);
    } else node->nodes = NULL;
}

// max_octree_depth
void initialize_new_chunk_octree(ecs_world_t *world, ecs_entity_t e, byte depth) {
    ChunkOctree *chunkOctree = zox_get_mut(e, ChunkOctree)
    fill_new_octree(chunkOctree, 0, depth);
    zox_modified(e, ChunkOctree)
}

void add_chunk_octree(ecs_world_t *world, const ecs_entity_t e, const int3 size) {
    zox_add_tag(e, Chunk)
    zox_prefab_set(e, ChunkSize, { size })
    zox_prefab_set(e, ChunkDirty, { chunk_dirty_state_none })
    zox_prefab_set(e, ChunkMeshDirty, { chunk_dirty_state_none })
    zox_prefab_set(e, ChunkPosition, { int3_zero })
    zox_prefab_set(e, RenderLod, { 255 })
    zox_prefab_set(e, RenderDistance, { 255 })
    zox_prefab_set(e, ChunkLodDirty, { 0 }) // chunk_lod_state_spawning })
    zox_prefab_set(e, VoxLink, { 0 })
    zox_prefab_add(e, ChunkOctree)
    zox_prefab_add(e, ChunkNeighbors)
    zox_get_muter(e, ChunkNeighbors, chunkNeighbors)
    resize_memory_component(ChunkNeighbors, chunkNeighbors, ecs_entity_t, 6)
    for (byte i = 0; i < 6; i++) chunkNeighbors->value[i] = 0;
}

byte get_octree_voxel(const ChunkOctree *node, byte3 *position, const byte depth) {
    if (node == NULL) return 0;
    else if (node->nodes == NULL) return node->value;
    else if (depth == 0) return node->value;
    const byte dividor = powers_of_two_byte[depth - 1];
    const byte3 node_position = (byte3) { position->x / dividor, position->y / dividor, position->z / dividor };
    byte3_modulus_byte(position, dividor);
    return get_octree_voxel(&node->nodes[byte3_octree_array_index(node_position)], position, depth - 1);
}

// returns node, also sets voxel
ChunkOctree* get_octree_voxel_with_node(byte *value, ChunkOctree *node, byte3 *position, const byte depth) {
    if (node == NULL) return NULL;
    *value = node->value;
    // if child nodes closed or depth final, return current node
    if (node->nodes == NULL || depth == 0) return node;
    const byte dividor = powers_of_two_byte[depth - 1];
    const byte3 node_position = (byte3) { position->x / dividor, position->y / dividor, position->z / dividor };
    byte3_modulus_byte(position, dividor);
    return get_octree_voxel_with_node(value, &node->nodes[byte3_octree_array_index(node_position)], position, depth - 1);
}

//! Closes all solid nodes, as well as air nodes, after terrain system generates it.
void close_solid_nodes(ChunkOctree *node) {
    if (!node->nodes) return;
    // for all children nodes - only check higher nodes if closed children
    for (byte i = 0; i < octree_length; i++) close_solid_nodes(&node->nodes[i]);
    byte all_solid = 1;
    byte all_air = 1;
    for (byte i = 0; i < octree_length; i++) {
        // if child node is open still, don't close
        if (node->nodes[i].nodes) {
            all_solid = 0;
            all_air = 0;
            break;
        }
        // checks if all solid or all air
        if (!node->nodes[i].value) {
            all_solid = 0;
        } else if (node->nodes[i].value) {
            all_air = 0;
        }
        if (!all_solid && !all_air) {
            break;
        }
    }
    if (all_solid || all_air) {
        close_ChunkOctree(node, max_octree_depth);
    }
}

// todo: make sure we only close blocks that can be grouped together here (we shouldn't group grass etc)
void close_same_nodes(ChunkOctree *node, const byte max_depth, byte depth) {
    if (node->nodes == NULL) return;
    if (depth == max_depth) return; // make sure this doesn't try to close spawned nodes
    depth++;
    for (byte i = 0; i < octree_length; i++) close_same_nodes(&node->nodes[i], max_depth, depth);
    byte all_same = 1;
    byte all_same_voxel = 255;
    for (byte i = 0; i < octree_length; i++) {
        if (node->nodes[i].nodes != NULL) return; // if a child node is open, then don't close this node
        const byte node_value = node->nodes[i].value;
        if (all_same_voxel == 255) all_same_voxel = node_value;
        else if (all_same_voxel != node_value) {
            all_same = 0;
            break;
        }
    }
    // if (all_same && first_node_value != 0) zox_log("  > closing same node [%i]\n", first_node_value);
    if (all_same) {
        node->value = all_same_voxel;
        close_ChunkOctree(node, max_octree_depth);
    }
}

void optimize_solid_nodes(ChunkOctree *node) {
    if (node->nodes != NULL) {
        for (byte i = 0; i < octree_length; i++) optimize_solid_nodes(&node->nodes[i]);
        byte voxel_types = 0;
        // byte2 *voxel_counts = malloc(sizeof(byte2) * octree_length);
        byte2 voxel_counts[octree_length];
        for (byte i = 0; i < octree_length; i++) {
            byte node_value = node->nodes[i].value;
            if (node_value == 0) continue;
            byte has_counted = 0;
            for (byte j = 0; j < voxel_types; j++) {
                has_counted = voxel_counts[j].x == node_value;
                if (has_counted) {
                    voxel_counts[j].y++;
                    break;
                }
            }
            if (!has_counted) {
                voxel_counts[voxel_types].x = node_value;
                voxel_counts[voxel_types].y = 0;
                voxel_types++;
            }
        }
        byte2 biggest_count = byte2_zero;
        for (byte j = 0; j < voxel_types; j++) {
            if (voxel_counts[j].y > biggest_count.y) biggest_count = voxel_counts[j];
        }
        if (biggest_count.x != 0) node->value = biggest_count.x;
        // free(voxel_counts);
    }
}

byte get_adjacent_voxel(byte direction, const ChunkOctree *root_node, const ChunkOctree *neighbors[], int3 position, byte depth, const byte edge_voxel) {
    byte chunk_index = 0;
    const ChunkOctree *adjacent_node = find_root_adjacent_ChunkOctree(root_node, position, depth, direction, neighbors, &chunk_index);
    if (adjacent_node && adjacent_node->value) return adjacent_node->value;
    else if (!adjacent_node) return edge_voxel; // edge of map
    else return 0;
}

// single voxel check!
byte is_adjacent_solid(byte direction, const ChunkOctree *root_node, const ChunkOctree *neighbors[], int3 position, byte depth, const byte edge_voxel, const byte *voxel_solidity) {
    byte voxel_adjacent = get_adjacent_voxel(direction, root_node, neighbors, position, depth, edge_voxel);
    if (voxel_adjacent == 0) return 0;
    voxel_adjacent--; // remove air from index
    return voxel_solidity[voxel_adjacent];
    /*byte chunk_index = 0;
    const ChunkOctree *adjacent_node = find_root_adjacent_ChunkOctree(root_node, position, depth, direction, neighbors, &chunk_index);
    // if (adjacent_node == NULL) zox_log("  > adjacent node is null: %ix%ix%i - depth %i\n", position.x, position.y, position.z, depth);
    if (adjacent_node == NULL) return edge_voxel;
    //if (adjacent_node->value) zox_log("  > adjacent node is solid: %ix%ix%i - depth %i - direction %i\n", position.x, position.y, position.z, depth, direction);
    //if (!adjacent_node->value) zox_log("  > adjacent node is air: %ix%ix%i - depth %i - direction %i\n", position.x, position.y, position.z, depth, direction);
    if (adjacent_node->value) return 1;
    else return 0;*/
}

// Check all voxels on a side, instead of just one, a big voxel with 4 small voxels on its side should be face culled.
// max_depth is per chunk... refactor that
// Fix issues between chunks of different levels of division
// function to check all adjacent voxels are solid on the face
byte is_adjacent_all_solid(byte direction, const ChunkOctree *root_node, const ChunkOctree *parent_node, const ChunkOctree *neighbors[], int3 octree_position, byte node_index, byte3 node_position, byte depth, const byte max_depth, const byte neighbor_depths[], byte edge_voxel, const byte *voxel_solidity) {
    /*byte is_adjacent_solid(direction, root_node, neighbors[], node_position, depth, edge_voxel, voxel_solidity);*/
    byte chunk_index = 0;
    const ChunkOctree *adjacent_node = find_adjacent_ChunkOctree(root_node, parent_node, octree_position, node_index, node_position, depth, direction, neighbors, &chunk_index);
    if (adjacent_node == NULL) { // || depth == max_depth) {
        return edge_voxel;
    } else if (adjacent_node->value == 0 || (voxel_solidity != NULL && !voxel_solidity[adjacent_node->value - 1])) {
        return 0;
    } else if (adjacent_node->nodes != NULL && ((chunk_index == 0 && depth < max_depth) || (chunk_index != 0 && depth < neighbor_depths[chunk_index - 1]))) {
        depth++;
        int3_multiply_int_p(&octree_position, 2);
        for (byte i = 0; i < octree_length; i++) {
            const byte3 local_position = octree_positions_b[i];
            if (direction == direction_left) {
                if (local_position.x != 0) continue;
            } else if (direction == direction_right) {
                if (local_position.x != 1) continue;
            } else if (direction == direction_down) {
                if (local_position.y != 0) continue;
            } else if (direction == direction_up) {
                if (local_position.y != 1) continue;
            } else if (direction == direction_back) {
                if (local_position.z != 0) continue;
            } else if (direction == direction_front) {
                if (local_position.z != 1) continue;
            } else {
                continue;
            }
            // check underneath nodes
            if (is_adjacent_all_solid(direction, root_node, &adjacent_node->nodes[i], neighbors, int3_add(octree_position, octree_positions[i]), i, local_position, depth, max_depth, neighbor_depths, edge_voxel, voxel_solidity) == 0) return 0;
        }
    }
    return 1;
}

void random_fill_octree(ChunkOctree* node, byte voxel, byte depth) {
    node->value = voxel;
    if (depth > 0) {
        depth--;
        open_ChunkOctree(node);
        for (int i = 0; i < octree_length; i++) random_fill_octree(&node->nodes[i], voxel, depth);
    } else {
        if (rand() % 101 >= fill_octree_random_rate) node->value = 0;
        else if (rand() % 101 >= fill_octree_random_rate2) node->value = 2;
        else if (rand() % 101 >= fill_octree_random_rate3) node->value = 3;
    }
}

void fill_octree(ChunkOctree* node, const byte voxel, byte depth) {
    node->value = voxel;
    if (depth > 0) {
        depth--;
        open_ChunkOctree(node);
        for (byte i = 0; i < octree_length; i++) fill_octree(&node->nodes[i], voxel, depth);
    }
}
