void add_chunk(ecs_world_t *world, ecs_entity_t prefab, int3 size) {
    zoxel_add_tag(prefab, Chunk);
    zoxel_add(world, prefab, ChunkData);
    zoxel_set(world, prefab, ChunkSize, { size });
    zoxel_set(world, prefab, ChunkDirty, { 0 });
    zoxel_set(world, prefab, ChunkPosition, { int3_zero });
    zoxel_set(world, prefab, VoxLink, { 0 });
}

void add_chunk_octree(ecs_world_t *world, ecs_entity_t e, int3 size) {
    zoxel_add_tag(e, Chunk);
    zoxel_add(world, e, ChunkOctree);
    zoxel_set(world, e, ChunkSize, { size });
    zoxel_set(world, e, ChunkDirty, { 0 });
    zoxel_set(world, e, ChunkPosition, { int3_zero });
    zoxel_set(world, e, ChunkDivision, { 0 });
    zoxel_set(world, e, VoxLink, { 0 });
    // zoxel_set(world, e, ChunkNeighbors, { 0, NULL });
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

void add_chunk_colors(ecs_world_t *world, ecs_entity_t prefab) {
    zoxel_add(world, prefab, ColorRGBs);
    if (!headless) {
        zoxel_add(world, prefab, MeshColorRGBs);
    }
}

void add_generate_chunk(ecs_world_t *world, ecs_entity_t e) {
    zoxel_set(world, e, EntityDirty, { 0 });
    zoxel_set(world, e, GenerateChunk, { 1 });
}

void add_noise_chunk(ecs_world_t *world, ecs_entity_t e) {
    zoxel_add_tag(e, NoiseChunk);
    zoxel_set(world, e, EntityDirty, { 0 });
    zoxel_set(world, e, GenerateChunk, { 1 });
    // zoxel_set(world, e, AnimateTexture, { 0.0 });
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

// Check all voxels on a side, instead of just one, a big voxel with 4 small voxels on its side should be face culled.
// max_depth is per chunk... refactor that
// Fix issues between chunks of different levels of division
// function to check all adjacent voxels are solid on the face
unsigned char is_adjacent_all_solid(unsigned char direction, const ChunkOctree *root_node, const ChunkOctree *parent_node, const ChunkOctree *neighbors[],
    int3 octree_position, unsigned char node_index, byte3 node_position, unsigned char depth, const unsigned char max_depth, const unsigned char *neighbors_max_depths,
    unsigned char edge_voxel) {
    unsigned char chunk_index = 0;
    const ChunkOctree *adjacent_node = find_adjacent_ChunkOctree(root_node, parent_node, octree_position, node_index, node_position, depth, direction, neighbors, &chunk_index);
    if (adjacent_node == NULL || adjacent_node->value == 0) {
        if (adjacent_node == NULL && chunk_index != 0) return edge_voxel;
        return 0;
    } else if (adjacent_node->nodes && ((chunk_index == 0 && depth < max_depth) || 
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
            int3 new_octree_position = int3_add(octree_position, octree_positions[i]);
            unsigned char is_adjacent_solid = is_adjacent_all_solid(direction, root_node, &adjacent_node->nodes[i], neighbors, new_octree_position, i, local_position, depth, max_depth, neighbors_max_depths, edge_voxel);
            if (is_adjacent_solid == 0) return 0;
        }
    }
    return 1;
}