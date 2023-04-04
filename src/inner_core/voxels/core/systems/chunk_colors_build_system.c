// colors version

#define zoxel_add_faces_colors(direction, is_positive)\
{\
    unsigned char that_voxel = get_voxel##_##direction(local_position, chunk, chunkSize, NULL);\
    if (that_voxel == 0)\
    {\
        if (is_positive)\
        {\
            add_voxel_face_colors(meshIndicies, meshVertices,\
                meshColors, voxel_color, \
                vertex_position_offset, center_mesh_offset, voxel_scale,\
                &start, start,\
                voxel_face_indicies_reversed,\
                voxel_face_indicies_length,\
                voxel_face_vertices##_##direction, voxel_face_vertices_length);\
        }\
        else\
        {\
            add_voxel_face_colors(meshIndicies, meshVertices,\
                meshColors, voxel_color, \
                vertex_position_offset, center_mesh_offset, voxel_scale,\
                &start, start,\
                voxel_face_indicies_normal,\
                voxel_face_indicies_length,\
                voxel_face_vertices##_##direction, voxel_face_vertices_length);\
        }\
    }\
}


void add_voxel_face_colors(MeshIndicies *meshIndicies, MeshVertices *meshVertices,
    MeshColors *meshColors, color voxel_color,
    float3 vertex_position_offset, float3 center_mesh_offset, float voxel_scale,
    int2 *start, int2 start2,
    const int voxel_face_indicies[], int voxel_face_indicies_length,
    const float3 voxel_face_vertices[], int voxel_face_vertices_length) {
    int indicies_offset = start2.y;
    for (int a = 0, b = start2.x; a < voxel_face_indicies_length; a++, b++)
    {
        meshIndicies->value[b] = indicies_offset + voxel_face_indicies[a];
    }
    // add verts
    for (int a = 0, b = start2.y; a < voxel_face_vertices_length; a++, b = b + 1)
    {
        float3 vertex_position = voxel_face_vertices[a]; // (float3) { cubeVertices[a + 0], cubeVertices[a + 1], cubeVertices[a + 2] };
        vertex_position = float3_multiply_float(vertex_position, voxel_scale);          // scale vertex
        vertex_position = float3_add(vertex_position, vertex_position_offset);   // offset vertex by voxel position in chunk
        vertex_position = float3_add(vertex_position, center_mesh_offset);       // add total mesh offset
        meshVertices->value[b] = vertex_position;
        meshColors->value[b] = voxel_color;
    }
    start->x += voxel_face_indicies_length;
    start->y += voxel_face_vertices_length * 1;
}

void build_chunk_mesh_colors(const ChunkData *chunk, const ChunkSize *chunkSize, const Colors *colors,
    MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshColors *meshColors) {
    // go through and add a top face for each voxel position that is solid
    int array_index = 0;
    int indicies_count = 0;
    int verticies_count = 0;
    int3 local_position;
    int2 start = { };
    float voxel_scale = overall_voxel_scale / ((float) chunkSize->value.x); // 16.0f;
    // float3 center_mesh_offset = (float3) { - overall_voxel_scale / 2.0f,
    //    - overall_voxel_scale / 2.0f, - overall_voxel_scale / 2.0f };
    // precount our face data for initialization
    for (local_position.x = 0; local_position.x < chunkSize->value.x; local_position.x++)
    {
        for (local_position.y = 0; local_position.y < chunkSize->value.y; local_position.y++)
        {
            for (local_position.z = 0; local_position.z < chunkSize->value.z; local_position.z++)
            {
                array_index = int3_array_index(local_position, chunkSize->value);
                if (chunk->value[array_index] != 0)
                {
                    #ifndef disable_voxel_left
                    zoxel_check_faces(left)
                    #endif
                    #ifndef disable_voxel_right
                    zoxel_check_faces(right)
                    #endif
                    #ifndef disable_voxel_down
                    zoxel_check_faces(down)
                    #endif
                    #ifndef disable_voxel_up
                    zoxel_check_faces(up)
                    #endif
                    #ifndef disable_voxel_back
                    zoxel_check_faces(back)
                    #endif
                    #ifndef disable_voxel_front
                    zoxel_check_faces(front)
                    #endif
                }
            }
        }
    }
    re_initialize_memory_component(meshIndicies, int, indicies_count);
    re_initialize_memory_component(meshVertices, float3, verticies_count);
    re_initialize_memory_component(meshColors, color, verticies_count);
    array_index = 0;
    unsigned char voxel = 0;
    color voxel_color = (color) { 255, 255, 255, 255 };
    for (local_position.x = 0; local_position.x < chunkSize->value.x; local_position.x++)
    {
        for (local_position.y = 0; local_position.y < chunkSize->value.y; local_position.y++)
        {
            for (local_position.z = 0; local_position.z < chunkSize->value.z; local_position.z++)
            {
                array_index = int3_array_index(local_position, chunkSize->value);
                voxel = chunk->value[array_index];
                if (voxel != 0)
                {
                    voxel_color = colors->value[voxel - 1];
                    // get color based on pallete voxel_color
                    float3 vertex_position_offset = float3_multiply_float(float3_from_int3(local_position), voxel_scale);
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
}

//! Builds a mesh data from the chunk!
void ChunkColorsBuildSystem(ecs_iter_t *it) {
    if (disable_chunk_systems) return;
    if (!ecs_query_changed(it->ctx, NULL))
    {
        return;
    }
    // printf("[ChunkBuildSystem] GenerateChunk was changed.\n");
    ChunkDirty *chunkDirtys = ecs_field(it, ChunkDirty, 1);
    const ChunkData *chunks = ecs_field(it, ChunkData, 2);
    const ChunkSize *chunkSizes = ecs_field(it, ChunkSize, 3);
    const Colors *colors = ecs_field(it, Colors, 4);
    MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 5);
    MeshVertices *meshVertices = ecs_field(it, MeshVertices, 6);
    MeshColors *meshColors = ecs_field(it, MeshColors, 7);
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 8);
    for (int i = 0; i < it->count; i++)
    {
        ChunkDirty *chunkDirty = &chunkDirtys[i];
        if (chunkDirty->value == 0)
        {
            continue;
        }
        MeshDirty *meshDirty = &meshDirtys[i];
        if (meshDirty->value != 0)
        {
            continue;
        }
        chunkDirty->value = 0;
        meshDirty->value = 1;
        const ChunkData *chunk = &chunks[i];
        const ChunkSize *chunkSize = &chunkSizes[i];
        const Colors *colors2 = &colors[i];
        MeshIndicies *meshIndicies2 = &meshIndicies[i];
        MeshVertices *meshVertices2 = &meshVertices[i];
        MeshColors *meshColors2 = &meshColors[i];
        build_chunk_mesh_colors(chunk, chunkSize, colors2, meshIndicies2, meshVertices2, meshColors2);
        //printf("Building ChunkData Colors Mesh [%lu] - [%i] [%i]\n",
        //    (long int) it->entities[i], meshIndicies2->length, meshVertices2->length);
    }
}
zoxel_declare_system(ChunkColorsBuildSystem)