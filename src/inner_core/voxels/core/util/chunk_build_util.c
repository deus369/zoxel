// face data for voxels
const int voxel_face_indicies_length = 6;
const int voxel_face_vertices_length = 4;
const int voxel_face_indicies_normal[] =
{
    0, 1, 2,    2, 3, 0
};
// reversed if positive
const int voxel_face_indicies_reversed[] =
{
    2, 1, 0,    0, 3, 2
};
const float2 voxel_face_uvs[] =
{
    { 0, 0.0f },
    { 0.0f, 1.0f },
    { 1.0f, 1.0f },
    { 1.0f, 0 }
};
// left
const float3 voxel_face_vertices_left[] =
{
    { 0, 0, 0 },            //4
    { 0, 0, 1.0f },         //0
    { 0, 1.0f, 1.0f },      //2
    { 0, 1.0f, 0 },         //6
};
// right
const float3 voxel_face_vertices_right[] =
{
    { 1.0f, 0, 0 },         //5
    { 1.0f, 0, 1.0f},       //1
    { 1.0f, 1.0f, 1.0f },   //3
    { 1.0f, 1.0f, 0}        //7
};
// down
const float3 voxel_face_vertices_down[] =
{
    { 0, 0, 0 },            //4
    { 0, 0, 1.0f },         //0
    { 1.0f, 0, 1.0f},       //1
    { 1.0f, 0, 0 },         //5
};
// up
const float3 voxel_face_vertices_up[] =
{
    { 0, 1.0f, 0 },         //2
    { 0, 1.0f, 1.0f },      //0
    { 1.0f, 1.0f, 1.0f },   //1
    { 1.0f, 1.0f, 0}        //3
};
// back
const float3 voxel_face_vertices_back[] =
{
    { 0, 0, 0.0f },
    { 0.0f, 1.0f, 0.0f},
    { 1.0f, 1.0f, 0.0f },
    { 1.0f, 0.0f, 0.0f }
};
// front
const float3 voxel_face_vertices_front[] =
{
    { 0, 0, 1.0f },
    { 0.0f, 1.0f, 1.0f},
    { 1.0f, 1.0f, 1.0f },
    { 1.0f, 0.0f, 1.0f }
};

// printf("Error in get_voxel_direction (chunk_other->value == NULL) [%ix%ix%i]\n", local_position.x, local_position.y, local_position.z);
// printf("Error in get_voxel_direction (chunk_other->length == 0) [%ix%ix%i]\n", local_position.x, local_position.y, local_position.z);

//! Create functions with macros to get voxels.
/**
*   \todo chunk_other should never be non null and have value == null as all chunks should be built at once..
*/
#define zoxel_get_voxel_direction(direction, dimension, is_positive)\
unsigned char get_voxel##_##direction(\
    int3 local_position,\
    const ChunkData *chunk,\
    const ChunkSize *chunkSize,\
    const ChunkData *chunk_other)\
{\
    if ((is_positive && local_position.dimension == chunkSize->value.dimension - 1)\
        || (!is_positive && local_position.dimension == 0))\
    {\
        if (chunk_other == NULL || chunk_other->value == NULL || chunk_other->length == 0)\
        {\
            return 0;\
        }\
        return chunk_other->value[int3_array_index(\
            int3_reverse##_##direction(local_position, chunkSize->value),\
            chunkSize->value)];\
    }\
    else\
    {\
        return chunk->value[int3_array_index(int3##_##direction(local_position), chunkSize->value)];\
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

//uvs_count += voxel_face_vertices_length;

#define zoxel_check_faces_with_uvs(direction)\
{\
    unsigned char that_voxel = get_voxel##_##direction(local_position, chunk, chunkSize, chunk##_##direction);\
    if (that_voxel == 0)\
    {\
        zoxel_add_voxel_face_counts()\
    }\
}

#define zoxel_check_faces_no_chunk(direction)\
{\
    unsigned char that_voxel = get_voxel##_##direction(local_position, chunk, chunkSize, NULL);\
    if (that_voxel == 0)\
    {\
        zoxel_add_voxel_face_counts()\
    }\
}

#define zoxel_add_voxel_face_uvs(direction, is_positive)\
    if (is_positive)\
    {\
        add_voxel_face_uvs(meshIndicies, meshVertices, meshUVs,\
            vertex_position_offset, center_mesh_offset, voxel_scale,\
            start,\
            voxel_face_indicies_reversed,\
            voxel_face_indicies_length,\
            voxel_face_vertices##_##direction, voxel_face_vertices_length,\
            voxel_face_uvs);\
    }\
    else\
    {\
        add_voxel_face_uvs(meshIndicies, meshVertices, meshUVs,\
            vertex_position_offset, center_mesh_offset, voxel_scale,\
            start,\
            voxel_face_indicies_normal,\
            voxel_face_indicies_length,\
            voxel_face_vertices##_##direction, voxel_face_vertices_length,\
            voxel_face_uvs);\
    }

#define zoxel_add_faces_with_uvs(direction, is_positive)\
{\
    unsigned char that_voxel = get_voxel##_##direction(local_position, chunk, chunkSize, chunk##_##direction);\
    if (that_voxel == 0)\
    {\
        zoxel_add_voxel_face_uvs(direction, is_positive)\
    }\
}
// start,

#define zoxel_add_faces_no_chunk(direction, is_positive)\
{\
    unsigned char that_voxel = get_voxel##_##direction(local_position, chunk, chunkSize, NULL);\
    if (that_voxel == 0)\
    {\
        if (is_positive)\
        {\
            add_voxel_face_uvs(meshIndicies, meshVertices, meshUVs,\
                vertex_position_offset, center_mesh_offset, voxel_scale,\
                start,\
                voxel_face_indicies_reversed,\
                voxel_face_indicies_length,\
                voxel_face_vertices##_##direction, voxel_face_vertices_length,\
                voxel_face_uvs);\
        }\
        else\
        {\
            add_voxel_face_uvs(meshIndicies, meshVertices, meshUVs,\
                vertex_position_offset, center_mesh_offset, voxel_scale,\
                start,\
                voxel_face_indicies_normal,\
                voxel_face_indicies_length,\
                voxel_face_vertices##_##direction, voxel_face_vertices_length,\
                voxel_face_uvs);\
        }\
    }\
}

#define zoxel_check_faces(direction)\
{\
    unsigned char that_voxel = get_voxel##_##direction(local_position, chunk, chunkSize, NULL);\
    if (that_voxel == 0)\
    {\
        indicies_count += voxel_face_indicies_length;\
        verticies_count += voxel_face_vertices_length * 1;\
    }\
}

#define zoxel_add_faces(direction, is_positive)\
{\
    unsigned char that_voxel = get_voxel##_##direction(local_position, chunk, chunkSize, NULL);\
    if (that_voxel == 0)\
    {\
        if (is_positive)\
        {\
            add_voxel_face(meshIndicies, meshVertices,\
                vertex_position_offset, center_mesh_offset, voxel_scale,\
                &start, start,\
                voxel_face_indicies_reversed,\
                voxel_face_indicies_length,\
                voxel_face_vertices##_##direction, voxel_face_vertices_length);\
        }\
        else\
        {\
            add_voxel_face(meshIndicies, meshVertices,\
                vertex_position_offset, center_mesh_offset, voxel_scale,\
                &start, start,\
                voxel_face_indicies_normal,\
                voxel_face_indicies_length,\
                voxel_face_vertices##_##direction, voxel_face_vertices_length);\
        }\
    }\
}
