/*
void add_voxel_face_colors(int_array_d *indicies, float3_array_d* vertices, color_rgb_array_d* color_rgbs,
    color_rgb voxel_color, float3 vertex_position_offset, float voxel_scale,
    const int voxel_face_indicies[], int voxel_face_indicies_length,
    const float3 voxel_face_vertices[], int voxel_face_vertices_length, byte direction) {
    int vertex_index_start = vertices->size;
    for (int a = 0; a < voxel_face_indicies_length; a++) {
        int vertex_index = vertex_index_start + voxel_face_indicies[a];
        add_to_int_array_d(indicies, vertex_index);
    }
    for (int a = 0; a < voxel_face_vertices_length; a++) {
        float3 vertex_position = voxel_face_vertices[a];
        float3_multiply_float_p(&vertex_position, voxel_scale);
        float3_add_float3_p(&vertex_position, vertex_position_offset);
        add_to_float3_array_d(vertices, vertex_position);
        color_rgb vertex_color = voxel_color;
        if (direction == direction_down) color_rgb_multiply_float(&vertex_color, 0.33f);
        else if (direction == direction_front) color_rgb_multiply_float(&vertex_color, 0.44f);
        else if (direction == direction_left) color_rgb_multiply_float(&vertex_color, 0.55f);
        else if (direction == direction_back) color_rgb_multiply_float(&vertex_color, 0.66f);
        else if (direction == direction_right) color_rgb_multiply_float(&vertex_color, 0.76f);
        add_to_color_rgb_array_d(color_rgbs, vertex_color);
    }
}

#define zoxel_get_adjacent_face(direction)\
    byte voxel##_##direction = get_voxel##_##direction(local_position, chunk, chunk_size, NULL);

#define zoxel_add_faces_colors(direction_facing, is_positive)\
if (voxel##_##direction_facing == 0) {\
    add_voxel_face_colors(indicies, vertices, color_rgbs, voxel_color, vertex_position_offset, voxel_scale,\
        get_voxel_indicies_##is_positive, voxel_face_indicies_length, voxel_face_vertices##_##direction_facing,\
        voxel_face_vertices_length, direction##_##direction_facing);\
}

void build_chunk_mesh_colors(const ChunkData *chunk, const ChunkSize *chunkSize, const ColorRGBs *colorRGBs, MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshColorRGBs *meshColorRGBs, float3 total_mesh_offset, const float voxel_scale) {
    // go through and add a top face for each voxel position that is solid
    int_array_d* indicies = create_int_array_d(initial_dynamic_array_size);
    float3_array_d* vertices = create_float3_array_d(initial_dynamic_array_size);
    color_rgb_array_d* color_rgbs = create_color_rgb_array_d(initial_dynamic_array_size);
    // precount our face data for initialization
    const byte3 chunk_size = (byte3) { chunkSize->value.x, chunkSize->value.y, chunkSize->value.z };
    byte voxel;
    color_rgb voxel_color;
    int array_index;
    byte3 local_position;
    for (local_position.x = 0; local_position.x < chunk_size.x; local_position.x++) {
        for (local_position.y = 0; local_position.y < chunk_size.y; local_position.y++) {
            for (local_position.z = 0; local_position.z < chunk_size.z; local_position.z++) {
                array_index = byte3_array_index(local_position, chunk_size);
                voxel = chunk->value[array_index];
                if (voxel != 0) {
                    voxel_color = colorRGBs->value[voxel - 1];
                    // randomize color
#ifdef zox_vox_noise
                    voxel_color.r -= voxel_color_rand + rand() % voxel_color_rand2;
                    voxel_color.g -= voxel_color_rand + rand() % voxel_color_rand2;
                    voxel_color.b -= voxel_color_rand + rand() % voxel_color_rand2;
#endif
                    // get color based on pallete voxel_color
                    float3 vertex_position_offset = float3_from_byte3(local_position);
                    float3_multiply_float_p(&vertex_position_offset, voxel_scale);
                    float3_add_float3_p(&vertex_position_offset, total_mesh_offset);

                    zoxel_get_adjacent_face(left)
                    zoxel_get_adjacent_face(right)
                    zoxel_get_adjacent_face(down)
                    zoxel_get_adjacent_face(up)
                    zoxel_get_adjacent_face(back)
                    zoxel_get_adjacent_face(front)

                    zoxel_add_faces_colors(left, 0)
                    zoxel_add_faces_colors(right, 1)
                    zoxel_add_faces_colors(down, 1)
                    zoxel_add_faces_colors(up, 0)
                    zoxel_add_faces_colors(back, 0)
                    zoxel_add_faces_colors(front, 1)
                }
            }
        }
    }
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

void ChunkColorsBuildSystem(ecs_iter_t *it) {
    zox_change_check()
    zox_field_in(ChunkData, chunkDatas, 2)
    zox_field_in(ChunkSize, chunkSizes, 3)
    zox_field_in(ColorRGBs, colorRGBs, 4)
    zox_field_in(VoxScale, voxScales, 5)
    zox_field_out(ChunkDirty, chunkDirtys, 1)
    zox_field_out(MeshIndicies, meshIndicies, 6)
    zox_field_out(MeshVertices, meshVertices, 7)
    zox_field_out(MeshColorRGBs, meshColorRGBs, 8)
    zox_field_out(MeshDirty, meshDirtys, 9)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(ChunkDirty, chunkDirtys, chunkDirty)
        if (chunkDirty->value == chunk_dirty_state_none) continue;
        zox_field_o(MeshDirty, meshDirtys, meshDirty)
        // if (meshDirty->value) continue;
        zox_field_i(ChunkData, chunkDatas, chunkData)
        zox_field_i(ChunkSize, chunkSizes, chunkSize)
        zox_field_i(ColorRGBs, colorRGBs, colors2)
        zox_field_i(VoxScale, voxScales, voxScale)
        zox_field_o(MeshIndicies, meshIndicies, meshIndicies2)
        zox_field_o(MeshVertices, meshVertices, meshVertices2)
        zox_field_o(MeshColorRGBs, meshColorRGBs, meshColorRGBs2)
        // maybe use bounds here directly
        const float3 total_mesh_offset = float3_multiply_float(calculate_vox_bounds(chunkSize->value, voxScale->value), -1);
        build_chunk_mesh_colors(chunkData, chunkSize, colors2, meshIndicies2, meshVertices2, meshColorRGBs2, total_mesh_offset, voxScale->value);
        chunkDirty->value = chunk_dirty_state_none;
        meshDirty->value = mesh_state_trigger;
    }
} zox_declare_system(ChunkColorsBuildSystem)
*/
