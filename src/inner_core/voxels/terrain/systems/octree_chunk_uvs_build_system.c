#define zoxel_set_octree_adjacent(direction_name)\
    const ChunkOctree *octree_node = find_adjacent_ChunkOctree(root_node, parent_node, octree_position, node_position, depth, direction##_##direction_name);

    //const ChunkOctree *octree_node = NULL;
    
#define zoxel_octree_add_face_counts(direction_name)\
{\
    zoxel_set_octree_adjacent(direction_name)\
    if (octree_node == NULL || octree_node->value == 0)\
    {\
        zoxel_add_voxel_face_counts()\
    }\
}

//  find_adjacent_ChunkOctree(root_node, parent_node, octree_position, node_position, depth, direction##_##name);

#define zoxel_octree_build_face(direction_name, is_positive)\
{\
    zoxel_set_octree_adjacent(direction_name)\
    if (octree_node == NULL || octree_node->value == 0)\
    {\
        zoxel_add_voxel_face_uvs(direction_name, is_positive)\
    }\
}

// 


void count_octree_chunk(const ChunkOctree *root_node, const ChunkOctree *parent_node, const ChunkOctree *chunk_octree,
    MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshUVs *meshUVs,
    int2 *mesh_count, unsigned char depth, unsigned char max_depth,
    int3 octree_position, int3 node_position)
{
    if (depth >= max_depth || chunk_octree->nodes == NULL)
    {
        if (chunk_octree->value)
        {
            zoxel_octree_add_face_counts(left)
            zoxel_octree_add_face_counts(right)
            zoxel_octree_add_face_counts(down)
            zoxel_octree_add_face_counts(up)
            zoxel_octree_add_face_counts(back)
            zoxel_octree_add_face_counts(front)
        }
        return;
    }
    depth++;
    // also check for sub nodes!
    if (chunk_octree->nodes != NULL)
    {
        octree_position.x *= 2;
        octree_position.y *= 2;
        octree_position.z *= 2;
        for (unsigned char i = 0; i < octree_length; i++)
        {
            int3 local_position = octree_positions[i];
            int3 child_octree_position = int3_add(octree_position, local_position);
            count_octree_chunk(root_node, chunk_octree, &chunk_octree->nodes[i], meshIndicies, meshVertices, meshUVs, mesh_count,
                depth, max_depth,
                child_octree_position, local_position);
        }
    }
}

void build_octree_chunk(const ChunkOctree *root_node, const ChunkOctree *parent_node, const ChunkOctree *chunk_octree,
    MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshUVs *meshUVs,
    int2 *start,
    unsigned char depth, unsigned char max_depth,
    int3 octree_position, int3 node_position, float scale)
{
    if (depth >= max_depth || chunk_octree->nodes == NULL)
    {
        if (chunk_octree->value)
        {
            float voxel_scale = scale * (overall_voxel_scale / ((float) octree_node_size));
            float3 center_mesh_offset = (float3) { - overall_voxel_scale / 2.0f,
                - overall_voxel_scale / 2.0f, - overall_voxel_scale / 2.0f };
            float3 vertex_position_offset = float3_from_int3(octree_position);
            vertex_position_offset = float3_multiply_float(vertex_position_offset, voxel_scale);
            zoxel_octree_build_face(left, 0)
            zoxel_octree_build_face(right, 1)
            zoxel_octree_build_face(down, 1)
            zoxel_octree_build_face(up, 0)
            zoxel_octree_build_face(back, 0)
            zoxel_octree_build_face(front, 1)
        }
        return;
    }
    depth++;
    // build for nodes
    scale *= 0.5f;
    // float3 center_mesh_offset = (float3) { - overall_voxel_scale / 2.0f,
    //    - overall_voxel_scale / 2.0f, - overall_voxel_scale / 2.0f };
    octree_position.x *= 2;
    octree_position.y *= 2;
    octree_position.z *= 2;
    int3 local_position;
    for (local_position.x = 0; local_position.x < octree_node_size; local_position.x++)
    {
        for (local_position.y = 0; local_position.y < octree_node_size; local_position.y++)
        {
            for (local_position.z = 0; local_position.z < octree_node_size; local_position.z++)
            {
                int array_index = int3_array_index(local_position, octree_node_size3);
                ChunkOctree node = chunk_octree->nodes[array_index];
                if (node.value == 0)
                {
                    continue;
                }
                int3 child_octree_position = int3_add(octree_position, local_position);
                build_octree_chunk(root_node, chunk_octree, &chunk_octree->nodes[array_index],
                    meshIndicies, meshVertices, meshUVs,
                    start,
                    depth, max_depth,
                    child_octree_position, local_position, scale);
            }
        }
    }
}

// float3 vertex_position_offset = float3_add(parent_vertex_position_offset,
//  float3_multiply_float(float3_from_int3(local_position), voxel_scale * 0.5f));

/*int3 get_octree_position(float3 real_position, unsigned char depth)
{
    int3 octree_position = (int3) { 0, 0, 0 };
    for (unsigned char i = 0; i < depth; i++)
    {

    }
}*/

void build_octree_chunk_mesh_uvs(const ChunkOctree *chunk_octree,
    MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshUVs *meshUVs,
    const ChunkOctree *chunk_left, const ChunkOctree *chunk_right,
    const ChunkOctree *chunk_back, const ChunkOctree *chunk_front,
    unsigned char chunk_division)
{
    int2 mesh_count = { 0, 0 };
    int2 *start = &((int2) { 0, 0 });
    #ifdef zoxel_voxel_disable_distance_division
        unsigned char max_depth = max_octree_depth;
    #else
        unsigned char max_depth = 0;
        if (chunk_division >= max_octree_depth)
        {
            max_depth = 0;
        }
        else
        {
            max_depth = max_octree_depth - chunk_division;
        }
    #endif
    count_octree_chunk(chunk_octree, NULL, chunk_octree, meshIndicies, meshVertices, meshUVs, &mesh_count, 0, max_depth,
        int3_zero, int3_zero);
    re_initialize_memory_component(meshIndicies, int, mesh_count.x);
    re_initialize_memory_component(meshVertices, float3, mesh_count.y);
    re_initialize_memory_component(meshUVs, float2, mesh_count.y);
    build_octree_chunk(chunk_octree, NULL, chunk_octree, meshIndicies, meshVertices, meshUVs, start, 0, max_depth,
        int3_zero, int3_zero, 2.0f);
}

//! Builds a mesh data from the chunk!
void OctreeChunkUVsBuildSystem(ecs_iter_t *it)
{
    ecs_query_t *changeQuery = it->ctx;
    if (!changeQuery || !ecs_query_changed(changeQuery, NULL))
    {
        return;
    }
    const ChunkDirty *entityDirtys = ecs_field(it, ChunkDirty, 1);
    const ChunkOctree *chunkOctrees = ecs_field(it, ChunkOctree, 2);
    const ChunkDivision *chunkDivisions = ecs_field(it, ChunkDivision, 3);
    const ChunkNeighbors *chunkNeighbors = ecs_field(it, ChunkNeighbors, 4);
    MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 5);
    MeshVertices *meshVertices = ecs_field(it, MeshVertices, 6);
    MeshUVs *meshUVs = ecs_field(it, MeshUVs, 7);
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 8);
    for (int i = 0; i < it->count; i++)
    {
        const ChunkDirty *chunkDirty = &entityDirtys[i];
        if (chunkDirty->value == 0)
        {
            continue;
        }
        MeshDirty *meshDirty = &meshDirtys[i];
        if (meshDirty->value != 0)
        {
            continue;
        }
        meshDirty->value = 1;
        const ChunkOctree *chunkOctree = &chunkOctrees[i];
        const ChunkDivision *chunkDivision = &chunkDivisions[i];
        const ChunkNeighbors *chunkNeighbors2 = &chunkNeighbors[i];
        MeshIndicies *meshIndicies2 = &meshIndicies[i];
        MeshVertices *meshVertices2 = &meshVertices[i];
        MeshUVs *meshUVs2 = &meshUVs[i];
        const ChunkOctree *chunk_left = chunkNeighbors2->value[0] == 0 ?
            NULL : ecs_get(it->world, chunkNeighbors2->value[0], ChunkOctree);
        const ChunkOctree *chunk_right = chunkNeighbors2->value[1] == 0 ?
            NULL : ecs_get(it->world, chunkNeighbors2->value[1], ChunkOctree);
        const ChunkOctree *chunk_back = chunkNeighbors2->value[2] == 0 ?
            NULL : ecs_get(it->world, chunkNeighbors2->value[2], ChunkOctree);
        const ChunkOctree *chunk_front = chunkNeighbors2->value[3] == 0 ?
            NULL : ecs_get(it->world, chunkNeighbors2->value[3], ChunkOctree);
        build_octree_chunk_mesh_uvs(chunkOctree, meshIndicies2, meshVertices2, meshUVs2,
            chunk_left, chunk_right, chunk_back, chunk_front, chunkDivision->value);
    }
}
zoxel_declare_system(OctreeChunkUVsBuildSystem)

                /*#ifndef disable_voxel_left
                zoxel_check_faces_with_uvs(left)
                #endif
                #ifndef disable_voxel_right
                zoxel_check_faces_with_uvs(right)
                #endif
                #ifndef disable_voxel_down
                zoxel_check_faces_no_chunk(down)
                #endif
                #ifndef disable_voxel_up
                zoxel_check_faces_no_chunk(up)
                #endif
                #ifndef disable_voxel_back
                zoxel_check_faces_with_uvs(back)
                #endif
                #ifndef disable_voxel_front
                zoxel_check_faces_with_uvs(front)
                #endif*/

                /*#ifndef disable_voxel_left
                zoxel_add_faces_with_uvs(left, 0)
                #endif
                #ifndef disable_voxel_right
                zoxel_add_faces_with_uvs(right, 1)
                #endif
                #ifndef disable_voxel_down
                zoxel_add_faces_no_chunk(down, 1)
                #endif
                #ifndef disable_voxel_up
                zoxel_add_faces_no_chunk(up, 0)
                #endif
                #ifndef disable_voxel_back
                zoxel_add_faces_with_uvs(back, 0)
                #endif
                #ifndef disable_voxel_front
                zoxel_add_faces_with_uvs(front, 1)
                #endif*/
                    /*int3 local_position2;
                    for (local_position2.x = 0; local_position2.x < octree_node_size; local_position2.x++)
                    {
                        for (local_position2.y = 0; local_position2.y < octree_node_size; local_position2.y++)
                        {
                            for (local_position2.z = 0; local_position2.z < octree_node_size; local_position2.z++)
                            {

                            }
                        }
                    }*/
    // int3 local_position;
    //! Precount our index and vertex array lengths.
    /*for (local_position.x = 0; local_position.x < octree_node_size; local_position.x++)
    {
        for (local_position.y = 0; local_position.y < octree_node_size; local_position.y++)
        {
            for (local_position.z = 0; local_position.z < octree_node_size; local_position.z++)
            {
                int array_index = int3_array_index(local_position, octree_node_size3);
                if (chunkOctree->nodes[array_index].value == 0)
                {
                    continue;
                }
                if (chunkOctree->nodes[array_index].nodes == NULL)
                {
                    continue;
                }
                // add faces - based on neighbor voxels
                zoxel_add_voxel_face_counts()
                zoxel_add_voxel_face_counts()
                zoxel_add_voxel_face_counts()
                zoxel_add_voxel_face_counts()
                zoxel_add_voxel_face_counts()
                zoxel_add_voxel_face_counts()
            }
        }
    }*/
    //! Create our index and vertex arrays
    /*for (local_position.x = 0; local_position.x < octree_node_size; local_position.x++)
    {
        for (local_position.y = 0; local_position.y < octree_node_size; local_position.y++)
        {
            for (local_position.z = 0; local_position.z < octree_node_size; local_position.z++)
            {
                int array_index = int3_array_index(local_position, octree_node_size3);
                ChunkOctree node = chunkOctree->nodes[array_index];
                if (node.value == 0)
                {
                    continue;
                }
                float3 vertex_position_offset = float3_multiply_float(float3_from_int3(local_position), voxel_scale);
                if (chunkOctree->nodes[array_index].nodes != NULL)
                {
                    int3 local_position2;
                    for (local_position2.x = 0; local_position2.x < octree_node_size; local_position2.x++)
                    {
                        for (local_position2.y = 0; local_position2.y < octree_node_size; local_position2.y++)
                        {
                            for (local_position2.z = 0; local_position2.z < octree_node_size; local_position2.z++)
                            {

                            }
                        }
                    }
                    continue;
                }
                zoxel_add_voxel_face_uvs(left, 0)
                zoxel_add_voxel_face_uvs(right, 1)
                zoxel_add_voxel_face_uvs(down, 1)
                zoxel_add_voxel_face_uvs(up, 0)
                zoxel_add_voxel_face_uvs(back, 0)
                zoxel_add_voxel_face_uvs(front, 1)
            }
        }
    }*/
    /*int3 local_position;
    for (local_position.x = 0; local_position.x < octree_node_size; local_position.x++)
    {
        for (local_position.y = 0; local_position.y < octree_node_size; local_position.y++)
        {
            for (local_position.z = 0; local_position.z < octree_node_size; local_position.z++)
            {
                int array_index = int3_array_index(local_position, octree_node_size3);
                count_octree_chunk(&chunk_octree->nodes[array_index], meshIndicies, meshVertices, meshUVs, mesh_count);*/
                /*if (chunk_octree->nodes[array_index].value == 0)
                {
                    continue;
                }
                if (chunk_octree->nodes[array_index].nodes != NULL)
                {
                    count_octree_chunk(&chunk_octree->nodes[array_index], meshIndicies, meshVertices, meshUVs, mesh_count);
                }
                else
                {
                    // add faces - based on neighbor voxels
                    zoxel_add_voxel_face_counts()
                    zoxel_add_voxel_face_counts()
                    zoxel_add_voxel_face_counts()
                    zoxel_add_voxel_face_counts()
                    zoxel_add_voxel_face_counts()
                    zoxel_add_voxel_face_counts()
                }*/
            /*}
        }
    }*/
    /*if (chunk_octree == NULL)
    {
        if (chunk_octree->value)
        {
            zoxel_add_voxel_face_uvs(left, 0)
            zoxel_add_voxel_face_uvs(right, 1)
            zoxel_add_voxel_face_uvs(down, 1)
            zoxel_add_voxel_face_uvs(up, 0)
            zoxel_add_voxel_face_uvs(back, 0)
            zoxel_add_voxel_face_uvs(front, 1)
        }
        return;
    }*/

                /*if (chunk_octree->nodes[array_index].nodes != NULL)
                {
                    build_octree_chunk(&chunk_octree->nodes[array_index],
                        meshIndicies, meshVertices, meshUVs, start, vertex_position_offset, scale);
                }
                else
                {
                    zoxel_add_voxel_face_uvs(left, 0)
                    zoxel_add_voxel_face_uvs(right, 1)
                    zoxel_add_voxel_face_uvs(down, 1)
                    zoxel_add_voxel_face_uvs(up, 0)
                    zoxel_add_voxel_face_uvs(back, 0)
                    zoxel_add_voxel_face_uvs(front, 1)
                }*/
            /*#ifndef disable_voxel_left
            const ChunkOctree *octree_node_left = find_adjacent_ChunkOctree(parent_node, octree_position, node_position, depth, direction_left, root_node);
            if (octree_node_left == NULL || octree_node_left->value == 0)
            {
                zoxel_add_voxel_face_counts()
            }
            #endif*/
            /*#ifndef disable_voxel_right
            const ChunkOctree *octree_node_right = find_adjacent_ChunkOctree(parent_node, octree_position, node_position, depth, direction_right, root_node);
            if (octree_node_right == NULL || octree_node_right->value == 0)
            {
                zoxel_add_voxel_face_counts()
            }
            #endif
            #ifndef disable_voxel_down
            const ChunkOctree *octree_node_down = find_adjacent_ChunkOctree(parent_node, octree_position, node_position, depth, direction_down, root_node);
            if (octree_node_down == NULL || octree_node_down->value == 0)
            {
                zoxel_add_voxel_face_counts()
            }
            #endif
            #ifndef disable_voxel_up
            const ChunkOctree *octree_node_up = find_adjacent_ChunkOctree(parent_node, octree_position, node_position, depth, direction_up, root_node);
            if (octree_node_up == NULL || octree_node_up->value == 0)
            {
                zoxel_add_voxel_face_counts()
            }
            #endif
            #ifndef disable_voxel_back
            const ChunkOctree *octree_node_back = find_adjacent_ChunkOctree(parent_node, octree_position, node_position, depth, direction_back, root_node);
            if (octree_node_back == NULL || octree_node_back->value == 0)
            {
                zoxel_add_voxel_face_counts()
            }
            #endif
            #ifndef disable_voxel_front
            const ChunkOctree *octree_node_front = find_adjacent_ChunkOctree(parent_node, octree_position, node_position, depth, direction_front, root_node);
            if (octree_node_front == NULL || octree_node_front->value == 0)
            {
                zoxel_add_voxel_face_counts()
            }
            #endif*/
            /*#ifndef disable_voxel_left
            const ChunkOctree *octree_node_left = find_adjacent_ChunkOctree(parent_node, octree_position, node_position, depth, direction_left, root_node);
            if (octree_node_left == NULL || octree_node_left->value == 0)
            {
                zoxel_add_voxel_face_uvs(left, 0)
            }
            #endif
            #ifndef disable_voxel_right
            const ChunkOctree *octree_node_right = find_adjacent_ChunkOctree(parent_node, octree_position, node_position, depth, direction_right, root_node);
            if (octree_node_right == NULL || octree_node_right->value == 0)
            {
                zoxel_add_voxel_face_uvs(right, 1)
            }
            #endif
            #ifndef disable_voxel_down
            const ChunkOctree *octree_node_down = find_adjacent_ChunkOctree(parent_node, octree_position, node_position, depth, direction_down, root_node);
            if (octree_node_down == NULL || octree_node_down->value == 0)
            {
                zoxel_add_voxel_face_uvs(down, 1)
            }
            #endif
            #ifndef disable_voxel_up
            const ChunkOctree *octree_node_up = find_adjacent_ChunkOctree(parent_node, octree_position, node_position, depth, direction_up, root_node);
            if (octree_node_up == NULL || octree_node_up->value == 0)
            {
                zoxel_add_voxel_face_uvs(up, 0)
            }
            #endif
            #ifndef disable_voxel_back
            const ChunkOctree *octree_node_back = find_adjacent_ChunkOctree(parent_node, octree_position, node_position, depth, direction_back, root_node);
            if (octree_node_back == NULL || octree_node_back->value == 0)
            {
                zoxel_add_voxel_face_uvs(back, 0)
            }
            #endif
            #ifndef disable_voxel_front
            const ChunkOctree *octree_node_front = find_adjacent_ChunkOctree(parent_node, octree_position, node_position, depth, direction_front, root_node);
            if (octree_node_front == NULL || octree_node_front->value == 0)
            {
                zoxel_add_voxel_face_uvs(front, 1)
            }
            #endif*/