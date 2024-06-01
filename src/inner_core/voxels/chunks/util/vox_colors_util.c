unsigned char colors_get_max_depth_from_division(const unsigned char chunk_division) {
    return max_octree_depth - chunk_division;
}

#define add_voxel_face_colors_indicies(index) indicies->data[indicies->size + index] = vertices->size + voxel_face_indicies[index];

#define add_voxel_face_colors_vertices(index) {\
    float3 vertex_position = voxel_face_vertices[index];\
    float3_multiply_float_p(&vertex_position, voxel_scale);\
    float3_add_float3_p(&vertex_position, vertex_position_offset);\
    vertices->data[vertices->size + index] = vertex_position;\
}

float3 calculate_vox_bounds(const int3 chunk_size, const float vox_scale) {
    float3 vox_bounds = float3_from_int3(chunk_size);
    float3_multiply_float_p(&vox_bounds, 0.5f * vox_scale);
    return vox_bounds;
}

// this takes 14ms on a 24core cpu, 6ms though during streaming
// scales vertex, offsets vertex by voxel position in chunk, adds total mesh offset
void add_voxel_face_colors_d(int_array_d *indicies, float3_array_d* vertices, color_rgb_array_d* color_rgbs, float3 vertex_position_offset, color_rgb voxel_color, const float voxel_scale, const int* voxel_face_indicies, const float3 voxel_face_vertices[], const unsigned char direction) {
    expand_capacity_int_array_d(indicies, voxel_face_indicies_length);
        add_voxel_face_colors_indicies(0)
        add_voxel_face_colors_indicies(1)
        add_voxel_face_colors_indicies(2)
        add_voxel_face_colors_indicies(3)
        add_voxel_face_colors_indicies(4)
        add_voxel_face_colors_indicies(5)
    indicies->size += voxel_face_indicies_length;
    expand_capacity_float3_array_d(vertices, voxel_face_vertices_length);
        add_voxel_face_colors_vertices(0)
        add_voxel_face_colors_vertices(1)
        add_voxel_face_colors_vertices(2)
        add_voxel_face_colors_vertices(3)
    vertices->size += voxel_face_vertices_length;
    for (int a = 0; a < voxel_face_vertices_length; a++) {
        color_rgb vertex_color = voxel_color;
#ifndef zox_disable_fake_voxel_lighting
        if (direction == direction_down) color_rgb_multiply_float(&vertex_color, 0.33f);
        else if (direction == direction_front) color_rgb_multiply_float(&vertex_color, 0.44f);
        else if (direction == direction_left) color_rgb_multiply_float(&vertex_color, 0.55f);
        else if (direction == direction_back) color_rgb_multiply_float(&vertex_color, 0.66f);
        else if (direction == direction_right) color_rgb_multiply_float(&vertex_color, 0.76f);
#endif
        add_to_color_rgb_array_d(color_rgbs, vertex_color);
    }
}

#define zoxel_octree_colors_build_face_d(direction_name, is_positive)\
if (!is_adjacent_all_solid(direction##_##direction_name, root_node, parent_node, neighbors,\
    octree_position, node_index, node_position, depth, max_depth, neighbor_lods, color_edge_voxel, NULL)) {\
    add_voxel_face_colors_d(indicies, vertices, color_rgbs, vertex_position_offset, voxel_color,\
        voxel_scale, get_voxel_indices(is_positive), voxel_face_vertices##_##direction_name,\
        direction##_##direction_name);\
}

// basically it goes downwards even if upper value nodes are air
// so with our optimizing somewhere it messed up and set the upper ones to zero? idk
// or maybe it was optimized properly
#define build_octree_chunk_colors_child_node(i)\
if (!(chunk_octree->nodes[i].nodes == NULL && chunk_octree->nodes[i].value == 0)) {\
    build_octree_chunk_colors_d(root_node, chunk_octree, &chunk_octree->nodes[i], neighbors, neighbor_lods, colorRGBs, indicies, vertices, color_rgbs, max_depth, depth, int3_add(octree_position, octree_positions[i]), i, total_mesh_offset, vox_scale);\
}

void build_octree_chunk_colors_d(const ChunkOctree *root_node, const ChunkOctree *parent_node, const ChunkOctree *chunk_octree, const ChunkOctree *neighbors[], const unsigned char neighbor_lods[], const ColorRGBs *colorRGBs, int_array_d *indicies, float3_array_d* vertices, color_rgb_array_d* color_rgbs, const unsigned char max_depth, unsigned char depth, int3 octree_position, const unsigned char node_index, const float3 total_mesh_offset, const float vox_scale) {
    if (depth >= max_depth || chunk_octree->nodes == NULL) {
        if (chunk_octree->value != 0) {
            const float voxel_scale = octree_scales3[depth] * vox_scale;
            float3 vertex_position_offset = float3_from_int3(octree_position);
            float3_multiply_float_p(&vertex_position_offset, voxel_scale);
            float3_add_float3_p(&vertex_position_offset, total_mesh_offset);
            byte3 node_position = octree_positions_b[node_index];
            const unsigned char voxel = chunk_octree->value;
            const color_rgb voxel_color = colorRGBs->value[voxel - 1];
            zoxel_octree_colors_build_face_d(left, 0)
            zoxel_octree_colors_build_face_d(right, 1)
            zoxel_octree_colors_build_face_d(down, 1)
            zoxel_octree_colors_build_face_d(up, 0)
            zoxel_octree_colors_build_face_d(back, 0)
            zoxel_octree_colors_build_face_d(front, 1)
        }
    } else {
        depth++;
        int3_multiply_int_p(&octree_position, 2);
        build_octree_chunk_colors_child_node(0)
        build_octree_chunk_colors_child_node(1)
        build_octree_chunk_colors_child_node(2)
        build_octree_chunk_colors_child_node(3)
        build_octree_chunk_colors_child_node(4)
        build_octree_chunk_colors_child_node(5)
        build_octree_chunk_colors_child_node(6)
        build_octree_chunk_colors_child_node(7)
    }
}

void build_chunk_octree_mesh_colors(const ChunkOctree *chunk_octree, const ColorRGBs *colorRGBs, MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshColorRGBs *meshColorRGBs, const unsigned char chunk_depth, const ChunkOctree *neighbors[], unsigned char neighbor_lods[], const float3 total_mesh_offset, const float vox_scale) {
    int_array_d* indicies = create_int_array_d(initial_dynamic_array_size);
    float3_array_d* vertices = create_float3_array_d(initial_dynamic_array_size);
    color_rgb_array_d* color_rgbs = create_color_rgb_array_d(initial_dynamic_array_size);
    build_octree_chunk_colors_d(chunk_octree, NULL, chunk_octree, neighbors, neighbor_lods, colorRGBs, indicies, vertices, color_rgbs, chunk_depth, 0, int3_zero, 0, total_mesh_offset, vox_scale);
    clear_mesh(meshIndicies, meshVertices, meshColorRGBs);
    meshIndicies->length = indicies->size;
    meshVertices->length = vertices->size;
    meshColorRGBs->length = color_rgbs->size;
    meshIndicies->value = finalize_int_array_d(indicies);
    meshVertices->value = finalize_float3_array_d(vertices);
    meshColorRGBs->value = finalize_color_rgb_array_d(color_rgbs);
    on_memory_component_created(meshIndicies, MeshIndicies)
    on_memory_component_created(meshVertices, MeshVertices)
    on_memory_component_created(meshColorRGBs, MeshColorRGBs)
}
