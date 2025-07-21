// todo: remove macros, they're not useful here, debugging and maintainance bad

#define add_voxel_face_colors_indicies(index)\
    indicies->data[indicies->size + index] = vertices->size + voxel_face_indicies[index];

#define add_voxel_face_colors_vertices(index) {\
    float3 vertex_position = voxel_face_vertices[index];\
    float3_scale_p(&vertex_position, voxel_scale);\
    float3_add_float3_p(&vertex_position, vertex_position_offset);\
    vertices->data[vertices->size + index] = vertex_position;\
}

// this takes 14ms on a 24core cpu, 6ms though during streaming
// scales vertex, offsets vertex by voxel position in chunk, adds total mesh offset
void add_voxel_face_colors_d(
    int_array_d *indicies,
    float3_array_d* vertices,
    color_rgb_array_d* color_rgbs,
    float3 vertex_position_offset,
    color_rgb voxel_color,
    const float voxel_scale,
    const int* voxel_face_indicies,
    const float3 voxel_face_vertices[],
    const byte direction) {
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
        if (direction == direction_down) {
            color_rgb_multiply_float(&vertex_color, 0.33f);
        } else if (direction == direction_front) color_rgb_multiply_float(&vertex_color, 0.44f);
        else if (direction == direction_left) color_rgb_multiply_float(&vertex_color, 0.55f);
        else if (direction == direction_back) color_rgb_multiply_float(&vertex_color, 0.66f);
        else if (direction == direction_right) color_rgb_multiply_float(&vertex_color, 0.76f);
#endif
        add_to_color_rgb_array_d(color_rgbs, vertex_color);
    }
}

#define zoxel_octree_colors_build_face_d(direction_name, is_positive, face_verts)\
if (!is_adjacent_all_solid(direction##_##direction_name, root_node, parent_node, neighbors,\
    octree_position, node_index, node_position, depth, max_depth, neighbor_lods, color_edge_voxel, NULL)) {\
    add_voxel_face_colors_d(indicies, vertices, color_rgbs, vertex_position_offset, voxel_color, voxel_scale, get_voxel_indicies_##is_positive, face_verts, direction##_##direction_name);\
}

void build_octree_chunk_colors_d(
    const VoxelNode *root_node,
    const VoxelNode *parent_node,
    const VoxelNode *node,
    const VoxelNode *neighbors[],
    const byte neighbor_lods[],
    const ColorRGBs *colorRGBs,
    int_array_d *indicies,
    float3_array_d* vertices,
    color_rgb_array_d* color_rgbs,
    const byte max_depth,
    byte depth,
    int3 octree_position,
    const byte node_index,
    const float3 total_mesh_offset,
    const float vox_scale) {
    if (node == NULL) {
        return;
    }
    if (depth >= max_depth || is_closed_VoxelNode(node)) {
        const byte voxel = node->value;
        if (voxel) {
            const byte voxel_index = voxel - 1;
            if (voxel_index >= colorRGBs->length) {
                // warning here?
                return;
            }
            const color_rgb voxel_color = colorRGBs->value[voxel_index];
            const float voxel_scale = real_chunk_scale * octree_scales3[depth] * vox_scale;
            float3 vertex_position_offset = float3_from_int3(octree_position);
            float3_scale_p(&vertex_position_offset, voxel_scale);
            float3_add_float3_p(&vertex_position_offset, total_mesh_offset);
            byte3 node_position = octree_positions_b[node_index];
            zoxel_octree_colors_build_face_d(left, 0, voxel_face_vertices_n[0])
            zoxel_octree_colors_build_face_d(right, 1, voxel_face_vertices_n[1])
            zoxel_octree_colors_build_face_d(down, 1, voxel_face_vertices_n[2])
            zoxel_octree_colors_build_face_d(up, 0, voxel_face_vertices_n[3])
            zoxel_octree_colors_build_face_d(back, 0, voxel_face_vertices_n[4])
            zoxel_octree_colors_build_face_d(front, 1, voxel_face_vertices_n[5])
        }
    } else {
        depth++;
        int3_multiply_int_p(&octree_position, 2);
        VoxelNode* kids = get_children_VoxelNode(node);
        for (byte i = 0; i < octree_length; i++) {
            build_octree_chunk_colors_d(
                root_node,
                node,
                &kids[i],
                neighbors,
                neighbor_lods,
                colorRGBs,
                indicies,
                vertices,
                color_rgbs,
                max_depth,
                depth,
                int3_add(octree_position, octree_positions[i]),
                i,
                total_mesh_offset,
                vox_scale);
        }
    }
}

// basically it goes downwards even if upper value nodes are air
// so with our optimizing somewhere it messed up and set the upper ones to zero? idk
// or maybe it was optimized properly


void build_node_mesh_colors(
    const VoxelNode *node,
    const ColorRGBs *colorRGBs,
    MeshIndicies *meshIndicies,
    MeshVertices *meshVertices,
    MeshColorRGBs *meshColorRGBs,
    const byte chunk_depth,
    const VoxelNode *neighbors[],
    const byte neighbor_lods[],
    const float3 total_mesh_offset,
    const float vox_scale) {
    int_array_d* indicies = create_int_array_d(initial_dynamic_array_size);
    float3_array_d* vertices = create_float3_array_d(initial_dynamic_array_size);
    color_rgb_array_d* color_rgbs = create_color_rgb_array_d(initial_dynamic_array_size);
    build_octree_chunk_colors_d(node, NULL, node, neighbors, neighbor_lods, colorRGBs, indicies, vertices, color_rgbs, chunk_depth, 0, int3_zero, 0, total_mesh_offset, vox_scale);
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
