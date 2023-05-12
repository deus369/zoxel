#define zoxel_octree_check(direction_name)\
    if (!is_adjacent_all_solid(direction##_##direction_name, root_node, parent_node, neighbors,\
        octree_position, node_index, node_position, depth, max_depth, neighbors_max_depths, 0))

#define zoxel_octree_add_face_counts(direction_name) {\
    zoxel_octree_check(direction_name) {\
        zoxel_add_voxel_face_counts()\
    }\
}

#define zoxel_octree_build_face(direction_name, is_positive) {\
    zoxel_octree_check(direction_name) {\
        zoxel_add_voxel_face_uvs(direction_name, is_positive)\
    }\
}

void count_octree_chunk(const ChunkOctree *root_node, const ChunkOctree *parent_node, const ChunkOctree *chunk_octree, const ChunkOctree *neighbors[],
    unsigned char *neighbors_max_depths, MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshUVs *meshUVs, int2 *mesh_count,
    unsigned char depth, unsigned char max_depth, int3 octree_position, unsigned char node_index, byte3 node_position) {
    if (depth >= max_depth || chunk_octree->nodes == NULL) {
        if (chunk_octree->value) {
            zoxel_octree_add_face_counts(left)
            zoxel_octree_add_face_counts(right)
            zoxel_octree_add_face_counts(down)
            zoxel_octree_add_face_counts(up)
            zoxel_octree_add_face_counts(back)
            zoxel_octree_add_face_counts(front)
        }
    } else {
        depth++;
        // also check for sub nodes!
        if (chunk_octree->nodes != NULL) {
            int3_multiply_int_p(&octree_position, 2);
            for (unsigned char i = 0; i < octree_length; i++) {
                int3 child_octree_position = int3_add(octree_position, octree_positions[i]);
                count_octree_chunk(root_node, chunk_octree, &chunk_octree->nodes[i],
                    neighbors, neighbors_max_depths, meshIndicies, meshVertices, meshUVs, mesh_count,
                    depth, max_depth, child_octree_position, i, octree_positions_b[i]);
            }
        }
    }
}

void build_octree_chunk(const ChunkOctree *root_node, const ChunkOctree *parent_node, const ChunkOctree *chunk_octree, const ChunkOctree *neighbors[],
    unsigned char *neighbors_max_depths, MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshUVs *meshUVs,
    int2 *start, unsigned char depth, unsigned char max_depth, int3 octree_position, unsigned char node_index, byte3 node_position) {
    if (depth >= max_depth || chunk_octree->nodes == NULL) {
        if (chunk_octree->value) {
            // float3 center_mesh_offset = (float3) { - overall_voxel_scale / 2.0f, - overall_voxel_scale / 2.0f, - overall_voxel_scale / 2.0f };
            float3 vertex_position_offset = float3_from_int3(octree_position);
            float voxel_scale = octree_scales2[depth] * (overall_voxel_scale / ((float) octree_node_size));
            vertex_position_offset = float3_multiply_float(vertex_position_offset, voxel_scale);
            zoxel_octree_build_face(left, 0)
            zoxel_octree_build_face(right, 1)
            zoxel_octree_build_face(down, 1)
            zoxel_octree_build_face(up, 0)
            zoxel_octree_build_face(back, 0)
            zoxel_octree_build_face(front, 1)
        }
    } else {
        depth++;
        int3_multiply_int_p(&octree_position, 2);
        for (unsigned char i = 0; i < octree_length; i++) {
            if (chunk_octree->nodes[i].value != 0) {
                int3 child_octree_position = int3_add(octree_position, octree_positions[i]);
                build_octree_chunk(root_node, chunk_octree, &chunk_octree->nodes[i],
                    neighbors, neighbors_max_depths, meshIndicies, meshVertices, meshUVs,
                    start, depth, max_depth, child_octree_position, i, octree_positions_b[i]);
            }
        }
    }
}

/*int3 local_position;
for (local_position.x = 0; local_position.x < octree_node_size; local_position.x++) {
    for (local_position.y = 0; local_position.y < octree_node_size; local_position.y++) {
        for (local_position.z = 0; local_position.z < octree_node_size; local_position.z++) {
            int array_index = int3_array_index(local_position, octree_node_size3);
            ChunkOctree node = chunk_octree->nodes[array_index];*/