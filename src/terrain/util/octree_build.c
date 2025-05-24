// #define zox_octree_chunk_build_limits
const byte zox_build_all_faces = 1;

// static data
typedef struct {
    // vox data
    const float scale; // overall scale
    byte edge_voxel;
    // voxels
    const TilemapUVs *tilemap_uvs;
    const byte *voxel_solidity;
    const int *voxel_uv_indexes;
    // neighbor data
    const ChunkOctree **neighbors;
    const byte *neighbor_depths;
    // chunk data
    const ChunkOctree *root;
    const byte is_max_depth_chunk;  // is chunk highest lod
    const byte render_depth;
    const byte max_depth;
    const mesh_uvs_build_data *mesh_data;
} terrain_build_data;

// changing data
typedef struct {
    // node data
    const ChunkOctree *parent;
    const ChunkOctree *node;
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
void zox_build_voxel_face(const mesh_uvs_build_data *mesh_data, const byte voxel, const int* voxel_face_indicies, const float3 voxel_face_vertices[], const float2 *voxel_face_uvs, const byte direction, const float3 offset, const float vert_scale) {
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
        float3_multiply_float_p(&vertex_position, vert_scale);
        mesh_data->vertices->data[mesh_data->vertices->size + i] = vertex_position;
    }
    mesh_data->vertices->size += voxel_face_vertices_length;
    // uvs
    expand_capacity_float2_array_d(mesh_data->uvs, voxel_face_vertices_length);
    for (byte i = 0; i < 4; i++) {
        const float2 vert_uv = voxel_face_uvs[i];
        mesh_data->uvs->data[mesh_data->uvs->size + i] = vert_uv;
        // mesh_data->uvs->data[mesh_data->uvs->size + i] = voxel_face_uvs[i];
    }
    mesh_data->uvs->size += voxel_face_vertices_length;
    // colors
    for (byte a = 0; a < voxel_face_vertices_length; a++) {
        color_rgb vertex_color = color_rgb_white;
#ifndef zox_disable_fake_voxel_lighting
        if (direction == direction_down) color_rgb_multiply_float(&vertex_color, 0.33f);
        else if (direction == direction_front) color_rgb_multiply_float(&vertex_color, 0.44f);
        else if (direction == direction_left) color_rgb_multiply_float(&vertex_color, 0.55f);
        else if (direction == direction_back) color_rgb_multiply_float(&vertex_color, 0.66f);
        else if (direction == direction_right) color_rgb_multiply_float(&vertex_color, 0.76f);
#endif
        add_to_color_rgb_array_d(mesh_data->color_rgbs, vertex_color);
    }
}

// this function accounts for size of drawing voxels
void build_voxel_mesh_final(const terrain_build_data data, octree_dig_data dig, octree_face_data face) {
    if (is_adjacent_all_solid(dig.direction, data.root, dig.parent, data.neighbors, dig.position, dig.index, dig.local_position, dig.depth, data.render_depth, data.neighbor_depths, data.edge_voxel, data.voxel_solidity)) {
        return;
    }
    byte is_regular_build = 1;
    if (zox_build_all_faces && data.is_max_depth_chunk) {
        // so far just increasing face draw resolution for up faces
        int depth_difference = data.max_depth - dig.depth;
        if (depth_difference != 0) {
            is_regular_build = 0;
            // this checks per voxel position if voxel is solid next to it
            int3 scaled_octree_position = dig.position;
            const int amplify_position = pow(2, depth_difference);
            if (amplify_position != 1) {
                int3_multiply_int_p(&scaled_octree_position, amplify_position);
            }
            int3 local_node_position = int3_zero;
            // place at top of current scale building
            if (dig.direction == direction_up) {
                local_node_position.y = (dig.scale - 1);
            } else if (dig.direction == direction_right) {
                local_node_position.x = (dig.scale - 1);
            } else if (dig.direction == direction_front) {
                local_node_position.z = (dig.scale - 1);
            }
            // three edge cases
            if (dig.direction == direction_up || dig.direction == direction_down) { // y
                for (local_node_position.x = 0; local_node_position.x < dig.scale; local_node_position.x++) {
                    for (local_node_position.z = 0; local_node_position.z < dig.scale; local_node_position.z++) {
                        int3 global_octree_position = scaled_octree_position;
                        int3_add_int3(&global_octree_position, local_node_position);
                        if (is_adjacent_solid(dig.direction, data.root, data.neighbors, global_octree_position, data.max_depth, data.edge_voxel, data.voxel_solidity)){
                            continue;
                        }
                        zox_build_voxel_face(data.mesh_data, dig.voxel, face.indicies, face.vertices, face.uvs, dig.direction, float3_from_int3(global_octree_position), data.scale);
                    }
                }
            } else if (dig.direction == direction_left || dig.direction == direction_right) { // x
                for (local_node_position.y = 0; local_node_position.y < dig.scale; local_node_position.y++) {
                    for (local_node_position.z = 0; local_node_position.z < dig.scale; local_node_position.z++) {
                        int3 global_octree_position = scaled_octree_position;
                        int3_add_int3(&global_octree_position, local_node_position);
                        if (is_adjacent_solid(dig.direction, data.root, data.neighbors, global_octree_position, data.max_depth, data.edge_voxel, data.voxel_solidity)) {
                            continue;
                        }
                        zox_build_voxel_face(data.mesh_data, dig.voxel, face.indicies, face.vertices, face.uvs, dig.direction, float3_from_int3(global_octree_position), data.scale);
                    }
                }
            } else { // z
                for (local_node_position.x = 0; local_node_position.x < dig.scale; local_node_position.x++) {
                    for (local_node_position.y = 0; local_node_position.y < dig.scale; local_node_position.y++) {
                        int3 global_octree_position = scaled_octree_position;
                        int3_add_int3(&global_octree_position, local_node_position);
                        if (is_adjacent_solid(dig.direction, data.root, data.neighbors, global_octree_position, data.max_depth, data.edge_voxel, data.voxel_solidity)) {
                            continue;
                        }
                        zox_build_voxel_face(data.mesh_data, dig.voxel, face.indicies, face.vertices, face.uvs, dig.direction, float3_from_int3(global_octree_position), data.scale);
                    }
                }
            }
        }
    }
    if (is_regular_build) {
        zox_build_voxel_face(data.mesh_data, dig.voxel, face.indicies, face.vertices, face.uvs, dig.direction, dig.offset, dig.scale * data.scale);
    }
}

// remember: vertex offset is just node position / voxel position

void zox_terrain_building_dig(const terrain_build_data data, octree_dig_data dig) {
    if (dig.depth >= data.render_depth || dig.node->nodes == NULL) {
        if (dig.node->value != 0 && data.voxel_solidity[dig.node->value - 1]) {
            dig.voxel = dig.node->value;
            dig.offset = float3_from_int3(dig.position);
            dig.scale =  real_chunk_scale * octree_scales3[dig.depth];
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
                    .indicies = get_voxel_indices(is_positive),
                    .vertices = voxel_face_vertices_n[i],
                    .uvs = &data.tilemap_uvs->value[uv_index],
                };
                build_voxel_mesh_final(data, dig, face);
            }
        }
    } else {
        int3 position = dig.position;
        int3_multiply_int_p(&position, 2);
        // only dig for solid child nodes
        for (byte i = 0; i < 8; i++) {
            if (dig.node->nodes[i].value) {
                octree_dig_data child = {
                    .parent = dig.node,
                    .depth = dig.depth + 1,
                    .scale = dig.scale * 0.5f,
                    // unique
                    .node = &dig.node->nodes[i],
                    .index = i,
                    .position = int3_add(position, octree_positions[i])
                };
                zox_terrain_building_dig(data, child);
            }
        }
    }
}