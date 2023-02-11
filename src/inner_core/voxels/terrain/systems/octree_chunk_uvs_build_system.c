// Check all voxels on a side, instead of just one, a big voxel with 4 small voxels on its side should be face culled.
// max_depth is per chunk... refactor that
// Fix issues between chunks of different levels of division
// function to check all adjacent voxels are solid on the face
unsigned char is_adjacent_all_solid(unsigned char direction,
    const ChunkOctree *root_node, const ChunkOctree *parent_node, const ChunkOctree *neighbors[],
    int3 octree_position, int3 node_position,
    unsigned char depth, unsigned char max_depth, unsigned char neighbors_max_depths[])
{
    unsigned char chunk_index = 0;
    const ChunkOctree *adjacent_node = find_adjacent_ChunkOctree(root_node, parent_node,
        octree_position, node_position, depth, direction, neighbors, &chunk_index);
    if (adjacent_node == NULL || adjacent_node->value == 0)
    {
        if (adjacent_node == NULL && chunk_index != 0)
        {
            return 1;
        }
        return 0;
    }
    // check underneath nodes
    else if (adjacent_node->nodes &&
        ((chunk_index == 0 && depth < max_depth) || 
        (chunk_index != 0 && depth < neighbors_max_depths[chunk_index - 1])))
    {
        depth++;
        octree_position.x *= 2;
        octree_position.y *= 2;
        octree_position.z *= 2;
        for (unsigned char i = 0; i < octree_length; i++)
        {
            int3 local_position = octree_positions[i];
            if (direction == direction_left)
            {
                if (local_position.x != 0)
                {
                    continue;
                }
            }
            else if (direction == direction_right)
            {
                if (local_position.x != 1)
                {
                    continue;
                }
            }
            else if (direction == direction_down)
            {
                if (local_position.y != 0)
                {
                    continue;
                }
            }
            else if (direction == direction_up)
            {
                if (local_position.y != 1)
                {
                    continue;
                }
            }
            else if (direction == direction_back)
            {
                if (local_position.z != 0)
                {
                    continue;
                }
            }
            else if (direction == direction_front)
            {
                if (local_position.z != 1)
                {
                    continue;
                }
            }
            else
            {
                continue;
            }
            if (is_adjacent_all_solid(direction, root_node,
                &adjacent_node->nodes[i], neighbors,
                int3_add(octree_position, local_position), local_position,
                    depth, max_depth, neighbors_max_depths) == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}


//  && depth > max_depth
//  && (chunk_index != 0 || depth > max_depth)
// (chunk_index == 0 && depth > max_depth))
// || (chunk_index != 0 && depth > neighbors_max_depths[chunk_index - 1]) 
// if (octree_node != NULL && octree_node->nodes != NULL) octree_node = NULL;
// if (octree_node != NULL && octree_node->nodes != NULL) octree_node = NULL;
// if (octree_node != NULL && octree_node->nodes != NULL) octree_node = NULL;

/*#define zoxel_set_octree_adjacent(direction_name)\
    const ChunkOctree *octree_node = find_adjacent_ChunkOctree(root_node, parent_node,\
        octree_position, node_position, depth, direction##_##direction_name, neighbors);\
    if (octree_node != NULL && octree_node->nodes != NULL)\
            octree_node = NULL;*/

/*#define zoxel_octree_check(direction_name)\
    zoxel_set_octree_adjacent(direction_name)\
        if (octree_node == NULL || octree_node->value == 0)*/

#define zoxel_octree_check(direction_name)\
    if (!is_adjacent_all_solid(direction##_##direction_name, root_node, parent_node, neighbors,\
         octree_position, node_position, depth, max_depth, neighbors_max_depths))

#define zoxel_octree_add_face_counts(direction_name)\
{\
    zoxel_octree_check(direction_name)\
    {\
        zoxel_add_voxel_face_counts()\
    }\
}

#define zoxel_octree_build_face(direction_name, is_positive)\
{\
    zoxel_octree_check(direction_name)\
    {\
        zoxel_add_voxel_face_uvs(direction_name, is_positive)\
    }\
}

void count_octree_chunk(
    const ChunkOctree *root_node, const ChunkOctree *parent_node, const ChunkOctree *chunk_octree,
    const ChunkOctree *neighbors[], unsigned char neighbors_max_depths[],
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
    }
    else
    {
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
                count_octree_chunk(root_node, chunk_octree, &chunk_octree->nodes[i],
                    neighbors, neighbors_max_depths,
                    meshIndicies, meshVertices, meshUVs,
                    mesh_count, depth, max_depth,
                    int3_add(octree_position, local_position), local_position);
            }
        }
    }
}

void build_octree_chunk(
    const ChunkOctree *root_node, const ChunkOctree *parent_node, const ChunkOctree *chunk_octree, 
    const ChunkOctree *neighbors[], unsigned char neighbors_max_depths[],
    MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshUVs *meshUVs,
    int2 *start, unsigned char depth, unsigned char max_depth,
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
    }
    else
    {
        depth++;
        scale *= 0.5f;
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
                        neighbors, neighbors_max_depths,
                        meshIndicies, meshVertices, meshUVs,
                        start,
                        depth, max_depth,
                        child_octree_position, local_position, scale);
                }
            }
        }
    }
}

unsigned char get_max_depth_from_division(unsigned char chunk_division)
{
    #ifdef zoxel_voxel_disable_distance_division
        unsigned char max_depth = max_octree_depth;
    #else
        unsigned char depth_addition = chunk_division / 2;
        unsigned char max_depth;
        if (depth_addition < inner_render_buffer)
        {
            max_depth = max_octree_depth;
        }
        else if ((depth_addition - inner_render_buffer) > max_octree_depth)
        {
            max_depth = 0;
        }
        else
        {
            max_depth = max_octree_depth - (depth_addition - inner_render_buffer);
        }
    #endif
    return max_depth;
}

void build_octree_chunk_mesh_uvs(const ChunkOctree *chunk_octree,
    MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshUVs *meshUVs,
    unsigned char chunk_division,
    const ChunkOctree *neighbors[], unsigned char neighbors_max_depths[])
{
    int2 mesh_count = { 0, 0 };
    int2 *start = &((int2) { 0, 0 });
    unsigned char max_depth = get_max_depth_from_division(chunk_division);
    count_octree_chunk(chunk_octree, NULL, chunk_octree,
        neighbors, neighbors_max_depths,
        meshIndicies, meshVertices, meshUVs, &mesh_count, 0, max_depth,
        int3_zero, int3_zero);
    re_initialize_memory_component(meshIndicies, int, mesh_count.x);
    re_initialize_memory_component(meshVertices, float3, mesh_count.y);
    re_initialize_memory_component(meshUVs, float2, mesh_count.y);
    build_octree_chunk(chunk_octree, NULL, chunk_octree,
        neighbors, neighbors_max_depths,
        meshIndicies, meshVertices, meshUVs, start, 0, max_depth,
        int3_zero, int3_zero, 2.0f);
}

//! Builds a mesh data from the chunk!
void OctreeChunkUVsBuildSystem(ecs_iter_t *it)
{
    if (disable_chunk_systems) return;
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
        const ChunkOctree *chunk_down = chunkNeighbors2->value[2] == 0 ?
            NULL : ecs_get(it->world, chunkNeighbors2->value[2], ChunkOctree);
        const ChunkOctree *chunk_up = chunkNeighbors2->value[3] == 0 ?
            NULL : ecs_get(it->world, chunkNeighbors2->value[3], ChunkOctree);
        const ChunkOctree *chunk_back = chunkNeighbors2->value[4] == 0 ?
            NULL : ecs_get(it->world, chunkNeighbors2->value[4], ChunkOctree);
        const ChunkOctree *chunk_front = chunkNeighbors2->value[5] == 0 ?
            NULL : ecs_get(it->world, chunkNeighbors2->value[5], ChunkOctree);
        const ChunkOctree *neighbors[] =  { chunk_left, chunk_right, chunk_down, chunk_up, chunk_back, chunk_front };
        unsigned char chunk_left_max_distance = chunkNeighbors2->value[0] == 0 ?
            0 : ecs_get(it->world, chunkNeighbors2->value[0], ChunkDivision)->value;
        unsigned char chunk_right_max_distance = chunkNeighbors2->value[1] == 0 ?
            0 : ecs_get(it->world, chunkNeighbors2->value[1], ChunkDivision)->value;
        unsigned char chunk_down_max_distance = chunkNeighbors2->value[2] == 0 ?
            0 : ecs_get(it->world, chunkNeighbors2->value[2], ChunkDivision)->value;
        unsigned char chunk_up_max_distance = chunkNeighbors2->value[3] == 0 ?
            0 : ecs_get(it->world, chunkNeighbors2->value[3], ChunkDivision)->value;
        unsigned char chunk_back_max_distance = chunkNeighbors2->value[4] == 0 ?
            0 : ecs_get(it->world, chunkNeighbors2->value[4], ChunkDivision)->value;
        unsigned char chunk_front_max_distance = chunkNeighbors2->value[5] == 0 ?
            0 : ecs_get(it->world, chunkNeighbors2->value[5], ChunkDivision)->value;
        unsigned char neighbors_max_depths[] =  {
            get_max_depth_from_division(chunk_left_max_distance),
            get_max_depth_from_division(chunk_right_max_distance),
            get_max_depth_from_division(chunk_down_max_distance),
            get_max_depth_from_division(chunk_up_max_distance),
            get_max_depth_from_division(chunk_back_max_distance),
            get_max_depth_from_division(chunk_front_max_distance)
        };
        build_octree_chunk_mesh_uvs(chunkOctree, meshIndicies2, meshVertices2, meshUVs2,
            chunkDivision->value, neighbors, neighbors_max_depths);
    }
}
zoxel_declare_system(OctreeChunkUVsBuildSystem)