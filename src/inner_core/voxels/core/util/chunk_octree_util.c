void add_chunk_octree(ecs_world_t *world, ecs_entity_t e, int3 size) {
    zox_add_tag(e, Chunk)
    zox_add(e, ChunkOctree)
    zox_set(e, ChunkSize, { size })
    zox_set(e, ChunkDirty, { 0 })
    zox_set(e, ChunkPosition, { int3_zero })
    zox_set(e, RenderLod, { 0 })
    zox_set(e, VoxLink, { 0 })
    ChunkNeighbors chunkNeighbors = { };
    initialize_memory_component_non_pointer(chunkNeighbors, ecs_entity_t, 6);
    chunkNeighbors.value[0] = 0;
    chunkNeighbors.value[1] = 0;
    chunkNeighbors.value[2] = 0;
    chunkNeighbors.value[3] = 0;
    chunkNeighbors.value[4] = 0;
    chunkNeighbors.value[5] = 0;
    ecs_set(world, e, ChunkNeighbors, { chunkNeighbors.length, chunkNeighbors.value });
}

void set_octree_voxel(ChunkOctree *node, byte3 *position, const byte2 *set_octree_data, unsigned char depth) {
    node->value = set_octree_data->x;
    if (depth == set_octree_data->y || node->nodes == NULL) return;
    unsigned char dividor = powers_of_two_byte[set_octree_data->y - depth - 1];   // starts at default_chunk_length, ends at 1
    byte3 node_position = (byte3) { position->x / dividor, position->y / dividor, position->z / dividor };
    byte3_modulus_byte(position, dividor);
    set_octree_voxel(&node->nodes[byte3_octree_array_index(node_position)], position, set_octree_data, depth + 1);
}

void set_octree_voxel_final(ChunkOctree *node, byte3 *position, const byte2 *set_octree_data, unsigned char depth) {
    if (depth == set_octree_data->y || node->nodes == NULL) {
        node->value = set_octree_data->x;
        return;
    }
    unsigned char dividor = powers_of_two_byte[set_octree_data->y - depth - 1];   // starts at default_chunk_length, ends at 1
    byte3 node_position = (byte3) { position->x / dividor, position->y / dividor, position->z / dividor };
    byte3_modulus_byte(position, dividor);
    set_octree_voxel_final(&node->nodes[byte3_octree_array_index(node_position)], position, set_octree_data, depth + 1);
}

unsigned char get_octree_voxel(const ChunkOctree *node, byte3 *position, unsigned char depth) {
    if (node->nodes == NULL || depth == 0) return node->value;
    unsigned char dividor = powers_of_two_byte[depth - 1]; // target - depth - 1];   // starts at default_chunk_length, ends at 1
    byte3 node_position = (byte3) { position->x / dividor, position->y / dividor, position->z / dividor };
    byte3_modulus_byte(position, dividor);
    return get_octree_voxel(&node->nodes[byte3_octree_array_index(node_position)], position, depth - 1);
}

//! Closes all solid nodes, as well as air nodes, after terrain system generates it.
void close_solid_nodes(ChunkOctree *node) {
    // for all children nodes - only check higher nodes if closed children
    if (node->nodes != NULL) {
        for (unsigned char i = 0; i < octree_length; i++) {
            close_solid_nodes(&node->nodes[i]);
        }
    }
    if (node->nodes != NULL) {
        unsigned char all_solid = 1;
        for (unsigned char i = 0; i < octree_length; i++) {
            if (node->nodes[i].nodes != NULL || node->nodes[i].value == 0) {
                all_solid = 0;
                break;
            }
        }
        if (all_solid) {
            close_ChunkOctree(node);
        } else {
            unsigned char all_air = 1;
            for (unsigned char i = 0; i < octree_length; i++) {
                if (node->nodes[i].nodes != NULL || node->nodes[i].value != 0) {
                    all_air = 0;
                    break;
                }
            }
            if (all_air) {
                close_ChunkOctree(node);
            }
        }
    }
}

void close_same_nodes(ChunkOctree *node) {
    if (node->nodes != NULL) {
        for (unsigned char i = 0; i < octree_length; i++) {
            close_same_nodes(&node->nodes[i]);
        }
    }
    if (node->nodes != NULL) {
        unsigned char all_same = 1;
        unsigned char first_type = node->nodes[0].value;
        for (unsigned char i = 1; i < octree_length; i++) {
            if (node->nodes[i].nodes != NULL || first_type != node->nodes[i].value) {
                all_same = 0;
                break;
            }
        }
        if (all_same) {
            close_ChunkOctree(node);
        }
    }
}

void optimize_solid_nodes(ChunkOctree *node) {
    if (node->nodes != NULL) {
        for (unsigned char i = 0; i < octree_length; i++) {
            optimize_solid_nodes(&node->nodes[i]);
        }
        // zoxel_log(" > depth [%i]\n", depth);
        // unsigned char all_solid = 0;
        unsigned char voxel_types = 0;
        byte2 *voxel_counts = malloc(sizeof(byte2) * octree_length);
        for (unsigned char i = 0; i < octree_length; i++) {
            unsigned char node_value = node->nodes[i].value;
            if (node_value == 0) continue;
            unsigned char has_counted = 0;
            for (unsigned char j = 0; j < voxel_types; j++) {
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
        for (unsigned char j = 0; j < voxel_types; j++) {
            if (voxel_counts[j].y > biggest_count.y) {
                biggest_count = voxel_counts[j];
            }
        }
        if (biggest_count.x != 0)
            node->value = biggest_count.x;
        free(voxel_counts);
    }
}

// Check all voxels on a side, instead of just one, a big voxel with 4 small voxels on its side should be face culled.
// max_depth is per chunk... refactor that
// Fix issues between chunks of different levels of division
// function to check all adjacent voxels are solid on the face
unsigned char is_adjacent_all_solid(unsigned char direction, const ChunkOctree *root_node, const ChunkOctree *parent_node, const ChunkOctree *neighbors[],
    int3 octree_position, unsigned char node_index, byte3 node_position, unsigned char depth, const unsigned char max_depth, const unsigned char *neighbors_max_depths,
    unsigned char edge_voxel) {
    unsigned char chunk_index = 0;
    const ChunkOctree *adjacent_node = find_adjacent_ChunkOctree(root_node, parent_node, octree_position, node_index, node_position, depth, direction, neighbors, &chunk_index);
    if (adjacent_node == NULL) { // || depth == max_depth) {
        return edge_voxel;
    } else if (adjacent_node->value == 0) {
        return 0;
    } else if (adjacent_node->nodes &&
        ((chunk_index == 0 && depth < max_depth) || 
        (chunk_index != 0 && depth < neighbors_max_depths[chunk_index - 1]))) {
        depth++;
        int3_multiply_int_p(&octree_position, 2);
        for (unsigned char i = 0; i < octree_length; i++) {
            byte3 local_position = octree_positions_b[i];
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
            if (is_adjacent_all_solid(direction, root_node, &adjacent_node->nodes[i], neighbors,int3_add(octree_position, octree_positions[i]),
                i, local_position, depth, max_depth, neighbors_max_depths, edge_voxel) == 0) return 0;
        }
    }
    return 1;
} 

const int fill_octree_random_rate = 50;
const int fill_octree_random_rate2 = 40;
const int fill_octree_random_rate3 = 30;

void random_fill_octree(ChunkOctree* node, unsigned char voxel, unsigned char depth) {
    node->value = voxel;
    if (depth > 0) {
        depth--;
        open_ChunkOctree(node);
        for (int i = 0; i < octree_length; i++) {
            random_fill_octree(&node->nodes[i], voxel, depth);
        }
    } else {
        if (rand() % 101 >= fill_octree_random_rate) 
            node->value = 0;
        else if (rand() % 101 >= fill_octree_random_rate2) 
            node->value = 2;
        else if (rand() % 101 >= fill_octree_random_rate3) 
            node->value = 3;
    }
}

void fill_octree(ChunkOctree* node, unsigned char voxel, unsigned char depth) {
    node->value = voxel;
    if (depth > 0) {
        depth--;
        open_ChunkOctree(node);
        for (int i = 0; i < octree_length; i++) {
            fill_octree(&node->nodes[i], voxel, depth);
        }
    }
}