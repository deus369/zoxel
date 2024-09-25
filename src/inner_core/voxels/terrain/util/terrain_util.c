void generate_terrain(ChunkOctree* chunk_octree, unsigned char depth, float3 position, float scale) {
    const uint32_t seed = global_seed;
    double octree_noise = perlin_terrain(position.x + noise_positiver2, position.z + noise_positiver2, terrain_frequency, seed, terrain_octaves);
    if (octree_noise < octree_min_height) octree_noise = octree_min_height;
    // octree_noise += octree_height_addition * octree_perlin_noise(position.x, position.y, position.z, octree_persistence, octree_frequency);
    if (position.y <= octree_noise) chunk_octree->value = 1;
    else chunk_octree->value = 0;
    if (depth < max_octree_depth && chunk_octree->value) {
        depth++;
        scale = scale * 0.5f;
        open_ChunkOctree(chunk_octree);
        for (unsigned char i = 0; i < octree_length; i++) {
            float3 node_position = float3_add(position, float3_multiply_float(float3_from_int3(octree_positions[i]), scale));
            generate_terrain(&chunk_octree->nodes[i], depth, node_position, scale);
        }
        // check all children
#ifndef zoxel_disable_close_nodes
        unsigned char is_all_solid = 1;
        for (unsigned char i = 0; i < octree_length; i++) {
            if (chunk_octree->nodes[i].nodes != NULL || !chunk_octree->nodes[i].value) {
                is_all_solid = 0;
                break;
            }
        }
        if (is_all_solid) close_ChunkOctree(chunk_octree, max_octree_depth);
#endif
    }
}

void set_terrain_block(ecs_world_t *world, ChunkOctree *chunkOctree, const byte3 voxel_position, const int chunk_position_y, const unsigned char chunk_voxel_length, const byte2 set_voxel, const int global_place_y) {
    const int local_place_y = global_place_y - chunk_position_y;
    const unsigned char place_in_bounds = local_place_y >= 0 && local_place_y < chunk_voxel_length;
    if (place_in_bounds) {
        byte3 node_position = voxel_position;
        node_position.y = local_place_y;
        set_octree_voxel(chunkOctree, &node_position, &set_voxel, 0); // testing
    }
}
