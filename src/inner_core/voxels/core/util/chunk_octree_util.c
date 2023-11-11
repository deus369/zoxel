const int fill_octree_random_rate = 50;
const int fill_octree_random_rate2 = 40;
const int fill_octree_random_rate3 = 30;

void fill_new_octree(ChunkOctree* node, const unsigned char voxel, unsigned char depth) {
    node->value = voxel;
    if (depth > 0) {
        depth--;
        open_new_ChunkOctree(node);
        for (unsigned char i = 0; i < octree_length; i++) fill_new_octree(&node->nodes[i], voxel, depth);
    } else node->nodes = NULL;
}

// max_octree_depth
void initialize_new_chunk_octree(ecs_world_t *world, ecs_entity_t e, unsigned char depth) {
    ChunkOctree *chunkOctree = zox_get_mut(e, ChunkOctree)
    fill_new_octree(chunkOctree, 0, depth);
    zox_modified(e, ChunkOctree)
}

void add_chunk_octree(ecs_world_t *world, ecs_entity_t e, int3 size) {
    zox_add_tag(e, Chunk)
    zox_prefab_set(e, ChunkOctree, { 0, NULL })
    zox_prefab_set(e, ChunkSize, { size })
    zox_prefab_set(e, ChunkDirty, { 0 })
    zox_prefab_set(e, ChunkPosition, { int3_zero })
    zox_prefab_set(e, RenderLod, { 0 })
    zox_prefab_set(e, VoxLink, { 0 })
    zox_prefab_set(e, ChunkNeighbors, { 0, NULL })
    ChunkNeighbors *chunkNeighbors = zox_get_mut(e, ChunkNeighbors)
    resize_memory_component(ChunkNeighbors, chunkNeighbors, ecs_entity_t, 6)
    for (unsigned char i = 0; i < 6; i++) chunkNeighbors->value[i] = 0;
    zox_modified(e, ChunkNeighbors)
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
    if (depth == set_octree_data->y || !node->nodes) {
        node->value = set_octree_data->x;
        return;
    }
    unsigned char dividor = powers_of_two_byte[set_octree_data->y - depth - 1];   // starts at default_chunk_length, ends at 1
    byte3 node_position = (byte3) { position->x / dividor, position->y / dividor, position->z / dividor };
    byte3_modulus_byte(position, dividor);
    set_octree_voxel_final(&node->nodes[byte3_octree_array_index(node_position)], position, set_octree_data, depth + 1);
}

unsigned char get_octree_voxel(const ChunkOctree *node, byte3 *position, unsigned char depth) {
    if (!node->nodes || !depth) return node->value;
    unsigned char dividor = powers_of_two_byte[depth - 1]; // target - depth - 1];   // starts at default_chunk_length, ends at 1
    byte3 node_position = (byte3) { position->x / dividor, position->y / dividor, position->z / dividor };
    byte3_modulus_byte(position, dividor);
    return get_octree_voxel(&node->nodes[byte3_octree_array_index(node_position)], position, depth - 1);
}

//! Closes all solid nodes, as well as air nodes, after terrain system generates it.
void close_solid_nodes(ChunkOctree *node) {
    if (!node->nodes) return;
    // for all children nodes - only check higher nodes if closed children
    for (unsigned char i = 0; i < octree_length; i++) close_solid_nodes(&node->nodes[i]);
    unsigned char all_solid = 1;
    for (unsigned char i = 0; i < octree_length; i++) {
        if (node->nodes[i].nodes != NULL || !node->nodes[i].value) {
            all_solid = 0;
            break;
        }
    }
    if (all_solid) close_ChunkOctree(node);
    else {
        unsigned char all_air = 1;
        for (unsigned char i = 0; i < octree_length; i++) {
            if (node->nodes[i].nodes != NULL || node->nodes[i].value) {
                all_air = 0;
                break;
            }
        }
        if (all_air) close_ChunkOctree(node);
    }
}

void close_same_nodes(ChunkOctree *node) {
    if (node->nodes == NULL) return;
    for (unsigned char i = 0; i < octree_length; i++) close_same_nodes(&node->nodes[i]);
    unsigned char all_same = 1;
    unsigned char first_node_value = 255;
    for (unsigned char i = 0; i < octree_length; i++) {
        if (node->nodes[i].nodes != NULL) return; // if a child node is open, then don't close this node
        const unsigned char node_value = node->nodes[i].value;
        if (first_node_value == 255) first_node_value = node_value;
        else if (first_node_value != node_value) {
            all_same = 0;
            break;
        }
    }
    // if (all_same && first_node_value != 0) zoxel_log("  > closing same node [%i]\n", first_node_value);
    if (all_same) close_ChunkOctree(node);
}

void optimize_solid_nodes(ChunkOctree *node) {
    if (node->nodes != NULL) {
        for (unsigned char i = 0; i < octree_length; i++) optimize_solid_nodes(&node->nodes[i]);
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
            if (voxel_counts[j].y > biggest_count.y) biggest_count = voxel_counts[j];
        }
        if (biggest_count.x != 0) node->value = biggest_count.x;
        free(voxel_counts);
    }
}

// Check all voxels on a side, instead of just one, a big voxel with 4 small voxels on its side should be face culled.
// max_depth is per chunk... refactor that
// Fix issues between chunks of different levels of division
// function to check all adjacent voxels are solid on the face
unsigned char is_adjacent_all_solid(unsigned char direction, const ChunkOctree *root_node, const ChunkOctree *parent_node, const ChunkOctree *neighbors[], int3 octree_position, unsigned char node_index, byte3 node_position, unsigned char depth, const unsigned char max_depth, const unsigned char *neighbor_lods, unsigned char edge_voxel) {
    unsigned char chunk_index = 0;
    const ChunkOctree *adjacent_node = find_adjacent_ChunkOctree(root_node, parent_node, octree_position, node_index, node_position, depth, direction, neighbors, &chunk_index);
    if (adjacent_node == NULL) { // || depth == max_depth) {
        return edge_voxel;
    } else if (adjacent_node->value == 0) {
        return 0;
    } else if (adjacent_node->nodes != NULL && ((chunk_index == 0 && depth < max_depth) || (chunk_index != 0 && depth < neighbor_lods[chunk_index - 1]))) {
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
            if (is_adjacent_all_solid(direction, root_node, &adjacent_node->nodes[i], neighbors, int3_add(octree_position, octree_positions[i]), i, local_position, depth, max_depth, neighbor_lods, edge_voxel) == 0) return 0;
        }
    }
    return 1;
}

// single voxel check!
unsigned char is_adjacent_solid(unsigned char direction, const ChunkOctree *root_node, const ChunkOctree *neighbors[], int3 position, unsigned char depth, const unsigned char edge_voxel) {
    unsigned char chunk_index = 0;
    const ChunkOctree *adjacent_node = find_root_adjacent_ChunkOctree(root_node, position, depth, direction, neighbors, &chunk_index);
    // if (adjacent_node == NULL) zoxel_log("  > adjacent node is null: %ix%ix%i - depth %i\n", position.x, position.y, position.z, depth);
    if (adjacent_node == NULL) return edge_voxel;
    //if (adjacent_node->value) zoxel_log("  > adjacent node is solid: %ix%ix%i - depth %i - direction %i\n", position.x, position.y, position.z, depth, direction);
    //if (!adjacent_node->value) zoxel_log("  > adjacent node is air: %ix%ix%i - depth %i - direction %i\n", position.x, position.y, position.z, depth, direction);
    if (adjacent_node->value) return 1;
    else return 0;
}

void random_fill_octree(ChunkOctree* node, unsigned char voxel, unsigned char depth) {
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

void fill_octree(ChunkOctree* node, const unsigned char voxel, unsigned char depth) {
    node->value = voxel;
    if (depth > 0) {
        depth--;
        open_ChunkOctree(node);
        for (unsigned char i = 0; i < octree_length; i++) fill_octree(&node->nodes[i], voxel, depth);
    }
}
