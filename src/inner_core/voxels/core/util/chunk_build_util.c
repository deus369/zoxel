// face data for voxels
const int voxel_face_indicies_length = 6;
const int voxel_face_vertices_length = 4;
const int voxel_face_indicies_normal[] = { 0, 1, 2,    2, 3, 0 };
// reversed if positive
const int voxel_face_indicies_reversed[] = { 2, 1, 0,    0, 3, 2 };

const int voxel_face_indicies_p[] = {
    2, 1, 0, 0, 3, 2,   // reversed
    0, 1, 2, 2, 3, 0    // normal
};

const int* get_voxel_indices(unsigned char is_positive) {
    if (is_positive) {
        return &voxel_face_indicies_p[0];
    } else {
        return &voxel_face_indicies_p[6];
    }
}

const float2 voxel_face_uvs[] = { { 0, 0 }, { 0, 1 }, { 1, 1 }, { 1, 0 } };

// left
const float3 voxel_face_vertices_left[] = {
    { 0, 0, 0 },    //4
    { 0, 0, 1 },    //0
    { 0, 1, 1 },    //2
    { 0, 1, 0 },    //6
};
// right
const float3 voxel_face_vertices_right[] = {
    { 1, 0, 0 },   //5
    { 1, 0, 1 },   //1
    { 1, 1, 1 },   //3
    { 1, 1, 0 }    //7
};
// down
const float3 voxel_face_vertices_down[] = {
    { 0, 0, 0 },   //4
    { 0, 0, 1 },   //0
    { 1, 0, 1 },   //1
    { 1, 0, 0 },   //5
};
// up
const float3 voxel_face_vertices_up[] = {
    { 0, 1, 0 },   //2
    { 0, 1, 1 },   //0
    { 1, 1, 1 },   //1
    { 1, 1, 0}     //3
};
// back
const float3 voxel_face_vertices_back[] = {
    { 0, 0, 0 },
    { 0, 1, 0 },
    { 1, 1, 0 },
    { 1, 0, 0 }
};
// front
const float3 voxel_face_vertices_front[] = {
    { 0, 0, 1 },
    { 0, 1, 1 },
    { 1, 1, 1 },
    { 1, 0, 1 }
};

//! Add vertices and uvs to the chunk one.
void add_voxel_face_uvs(MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshUVs *meshUVs,
    float3 vertex_position_offset, float3 center_mesh_offset, float voxel_scale, int2 *mesh_start,
    const int voxel_face_indicies[], int voxel_face_indicies_length, const float3 voxel_face_vertices[],
    int voxel_face_vertices_length, const float2 voxel_face_uvs[]) {
    for (int a = 0, b = mesh_start->x; a < voxel_face_indicies_length; a++, b++) {
        // printf("b [%i]\n", b);
        meshIndicies->value[b] = mesh_start->y + voxel_face_indicies[a];
    }
    // add verts
    for (int a = 0, b = mesh_start->y, c = mesh_start->y; a < voxel_face_vertices_length; a++, b++, c++) {
        float3 vertex_position = voxel_face_vertices[a];
        vertex_position = float3_multiply_float(vertex_position, voxel_scale);          // scale vertex
        vertex_position = float3_add(vertex_position, vertex_position_offset);   // offset vertex by voxel position in chunk
        // vertex_position = float3_add(vertex_position, center_mesh_offset);       // add total mesh offset
        meshVertices->value[b] = vertex_position;
        meshUVs->value[c] = voxel_face_uvs[a];
    }
    mesh_start->x += voxel_face_indicies_length;
    mesh_start->y += voxel_face_vertices_length;
}

//! Create functions with macros to get voxels.
/**
*   \todo chunk_other should never be non null and have value == null as all chunks should be built at once..
*/
// printf("Error in get_voxel_direction (chunk_other->value == NULL) [%ix%ix%i]\n", local_position.x, local_position.y, local_position.z);
// printf("Error in get_voxel_direction (chunk_other->length == 0) [%ix%ix%i]\n", local_position.x, local_position.y, local_position.z);

#define zoxel_get_voxel_direction(direction, dimension, is_positive)\
unsigned char get_voxel##_##direction(byte3 local_position, const ChunkData *chunk, byte3 chunk_size, const ChunkData *chunk_other) {\
    if ((is_positive && local_position.dimension == chunk_size.dimension - 1) || (!is_positive && local_position.dimension == 0)) {\
        if (chunk_other == NULL || chunk_other->value == NULL || chunk_other->length == 0) {\
            return 0;\
        }\
        return chunk_other->value[byte3_array_index(byte3_reverse##_##direction(local_position, chunk_size), chunk_size)];\
    } else {\
        return chunk->value[byte3_array_index(byte3##_##direction(local_position), chunk_size)];\
    }\
}

zoxel_get_voxel_direction(left, x, 0)       // creates get_voxel_left
zoxel_get_voxel_direction(right, x, 1)      // creates get_voxel_right
zoxel_get_voxel_direction(down, y, 0)       // creates get_voxel_down
zoxel_get_voxel_direction(up, y, 1)         // creates get_voxel_up
zoxel_get_voxel_direction(back, z, 0)       // creates get_voxel_back
zoxel_get_voxel_direction(front, z, 1)      // creates get_voxel_front

#define zoxel_add_voxel_face_counts()\
    mesh_count->x += voxel_face_indicies_length;\
    mesh_count->y += voxel_face_vertices_length;

#define zoxel_check_faces_with_uvs(direction) {\
    unsigned char that_voxel = get_voxel##_##direction(local_position, chunk, chunk_size, chunk##_##direction);\
    if (that_voxel == 0) {\
        zoxel_add_voxel_face_counts()\
    }\
}

#define zoxel_check_faces_no_chunk(direction) {\
    unsigned char that_voxel = get_voxel##_##direction(local_position, chunk, chunk_size, NULL);\
    if (that_voxel == 0) {\
        zoxel_add_voxel_face_counts()\
    }\
}

#define zoxel_add_voxel_face_uvs(direction, is_positive)\
    if (is_positive) {\
        add_voxel_face_uvs(meshIndicies, meshVertices, meshUVs,\
            vertex_position_offset, center_mesh_offset, voxel_scale,\
            start, voxel_face_indicies_reversed, voxel_face_indicies_length,\
            voxel_face_vertices##_##direction, voxel_face_vertices_length, voxel_face_uvs);\
    } else {\
        add_voxel_face_uvs(meshIndicies, meshVertices, meshUVs,\
            vertex_position_offset, center_mesh_offset, voxel_scale,\
            start, voxel_face_indicies_normal, voxel_face_indicies_length,\
            voxel_face_vertices##_##direction, voxel_face_vertices_length, voxel_face_uvs);\
    }

#define zoxel_add_faces_with_uvs(direction, is_positive) {\
    unsigned char that_voxel = get_voxel##_##direction(local_position, chunk, chunk_size, chunk##_##direction);\
    if (that_voxel == 0) {\
        zoxel_add_voxel_face_uvs(direction, is_positive)\
    }\
}

#define zoxel_add_faces_no_chunk(direction, is_positive) {\
    unsigned char that_voxel = get_voxel##_##direction(local_position, chunk, chunk_size, NULL);\
    if (that_voxel == 0) {\
        if (is_positive) {\
            add_voxel_face_uvs(meshIndicies, meshVertices, meshUVs,\
                vertex_position_offset, center_mesh_offset, voxel_scale,\
                start, voxel_face_indicies_reversed, voxel_face_indicies_length,\
                voxel_face_vertices##_##direction, voxel_face_vertices_length, voxel_face_uvs);\
        } else {\
            add_voxel_face_uvs(meshIndicies, meshVertices, meshUVs,\
                vertex_position_offset, center_mesh_offset, voxel_scale,\
                start, voxel_face_indicies_normal, voxel_face_indicies_length,\
                voxel_face_vertices##_##direction, voxel_face_vertices_length, voxel_face_uvs);\
        }\
    }\
}

#define zoxel_check_faces(direction) {\
    unsigned char that_voxel = get_voxel##_##direction(local_position, chunk, chunk_size, NULL);\
    if (that_voxel == 0) {\
        indicies_count += voxel_face_indicies_length;\
        verticies_count += voxel_face_vertices_length * 1;\
    }\
}

#define zoxel_add_faces(direction, is_positive) {\
    unsigned char that_voxel = get_voxel##_##direction(local_position, chunk, chunk_size, NULL);\
    if (that_voxel == 0) {\
        if (is_positive) {\
            add_voxel_face(meshIndicies, meshVertices, vertex_position_offset, center_mesh_offset, voxel_scale,\
                &start, start, voxel_face_indicies_reversed, voxel_face_indicies_length,\
                voxel_face_vertices##_##direction, voxel_face_vertices_length);\
        } else {\
            add_voxel_face(meshIndicies, meshVertices, vertex_position_offset, center_mesh_offset, voxel_scale,\
                &start, start, voxel_face_indicies_normal, voxel_face_indicies_length,\
                voxel_face_vertices##_##direction, voxel_face_vertices_length);\
        }\
    }\
}

/*
#define voxel_face_uvs_create(index, offset_x, offset_y, size_x, size_y)\
const float2 voxel_uvs##_##index[] = { { offset_x, offset_y }, { offset_x, offset_y + size_y },\
    { offset_x + size_x, offset_y + size_y }, { offset_x + size_x, offset_y } };

voxel_face_uvs_create(0, 0, 0, 0.5f, 0.5f)
voxel_face_uvs_create(1, 0.5f, 0, 0.5f, 0.5f)
voxel_face_uvs_create(2, 0, 0.5f, 0.5f, 0.5f)
voxel_face_uvs_create(3, 0.5f, 0.5f, 0.5f, 0.5f)*/