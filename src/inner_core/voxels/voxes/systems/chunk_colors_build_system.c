void add_voxel_face_colors(int_array_d *indicies, float3_array_d* vertices, color_rgb_array_d* color_rgbs,
    color_rgb voxel_color, float3 vertex_position_offset, float voxel_scale,
    const int voxel_face_indicies[], int voxel_face_indicies_length,
    const float3 voxel_face_vertices[], int voxel_face_vertices_length, unsigned char direction) {
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
        if (direction == direction_down) {
            color_rgb_multiply_float(&vertex_color, 0.33f);
        } else if (direction == direction_front) {
            color_rgb_multiply_float(&vertex_color, 0.44f);
        } else if (direction == direction_left) {
            color_rgb_multiply_float(&vertex_color, 0.55f);
        } else if (direction == direction_back) {
            color_rgb_multiply_float(&vertex_color, 0.66f);
        } else if (direction == direction_right) {
            color_rgb_multiply_float(&vertex_color, 0.76f);
        }
        add_to_color_rgb_array_d(color_rgbs, vertex_color);
    }
}

#define zoxel_get_adjacent_face(direction)\
    unsigned char voxel##_##direction = get_voxel##_##direction(local_position, chunk, chunk_size, NULL);

#define zoxel_add_faces_colors(direction_facing, is_positive)\
if (voxel##_##direction_facing == 0) {\
    add_voxel_face_colors(indicies, vertices, color_rgbs, voxel_color, vertex_position_offset, voxel_scale,\
        get_voxel_indices(is_positive), voxel_face_indicies_length, voxel_face_vertices##_##direction_facing,\
        voxel_face_vertices_length, direction##_##direction_facing);\
}

void build_chunk_mesh_colors(const ChunkData *chunk, const ChunkSize *chunkSize, const ColorRGBs *colorRGBs, MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshColorRGBs *meshColorRGBs, float3 total_mesh_offset, const float voxel_scale) {
    // go through and add a top face for each voxel position that is solid
    int_array_d* indicies = create_int_array_d(initial_dynamic_array_size);
    float3_array_d* vertices = create_float3_array_d(initial_dynamic_array_size);
    color_rgb_array_d* color_rgbs = create_color_rgb_array_d(initial_dynamic_array_size);
    // precount our face data for initialization
    const byte3 chunk_size = (byte3) { chunkSize->value.x, chunkSize->value.y, chunkSize->value.z };
    unsigned char voxel;
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
#ifdef zoxel_voxes_color_randomize
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
#ifndef disable_voxel_left
                    zoxel_add_faces_colors(left, 0)
#endif
#ifndef disable_voxel_right
                    zoxel_add_faces_colors(right, 1)
#endif
#ifndef disable_voxel_down
                    zoxel_add_faces_colors(down, 1)
#endif
#ifndef disable_voxel_up
                    zoxel_add_faces_colors(up, 0)
#endif
#ifndef disable_voxel_back
                    zoxel_add_faces_colors(back, 0)
#endif
#ifndef disable_voxel_front
                    zoxel_add_faces_colors(front, 1)
#endif
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
    if (!ecs_query_changed(it->ctx, NULL)) return;
#ifdef zoxel_time_chunk_colors_builds_system
    begin_timing()
#endif
    ChunkDirty *chunkDirtys = ecs_field(it, ChunkDirty, 1);
    const ChunkData *chunks = ecs_field(it, ChunkData, 2);
    const ChunkSize *chunkSizes = ecs_field(it, ChunkSize, 3);
    const ColorRGBs *colorRGBs = ecs_field(it, ColorRGBs, 4);
    zox_field_in(VoxScale, voxScales, 5)
    MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 6);
    MeshVertices *meshVertices = ecs_field(it, MeshVertices, 7);
    MeshColorRGBs *meshColorRGBs = ecs_field(it, MeshColorRGBs, 8);
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 9);
    for (int i = 0; i < it->count; i++) {
        ChunkDirty *chunkDirty = &chunkDirtys[i];
        if (chunkDirty->value == 0) continue;
        MeshDirty *meshDirty = &meshDirtys[i];
        if (meshDirty->value != 0) continue;
        const ChunkData *chunk = &chunks[i];
        const ChunkSize *chunkSize = &chunkSizes[i];
        const ColorRGBs *colors2 = &colorRGBs[i];
        zox_field_i_in(VoxScale, voxScales, voxScale)
        MeshIndicies *meshIndicies2 = &meshIndicies[i];
        MeshVertices *meshVertices2 = &meshVertices[i];
        MeshColorRGBs *meshColorRGBs2 = &meshColorRGBs[i];
        // maybe use bounds here directly
        float3 total_mesh_offset = calculate_vox_bounds(chunkSize->value, voxScale->value);
        float3_multiply_float_p(&total_mesh_offset, -1);
        build_chunk_mesh_colors(chunk, chunkSize, colors2, meshIndicies2, meshVertices2, meshColorRGBs2, total_mesh_offset, voxScale->value);
        chunkDirty->value = 0;
        meshDirty->value = 1;
#ifdef zoxel_time_chunk_colors_builds_system
        did_do_timing()
#endif
    }
#ifdef zoxel_time_chunk_colors_builds_system
    end_timing("    - chunk_colors_builds_system")
#endif
} zox_declare_system(ChunkColorsBuildSystem)
