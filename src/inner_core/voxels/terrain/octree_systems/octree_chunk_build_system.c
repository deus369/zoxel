// add uv splitting here based on voxel uvs - voxel_face_uvs based on voxel
// for now lets try 

// const float3 center_mesh_offset = (float3) { - overall_voxel_scale / 2.0f, - overall_voxel_scale / 2.0f, - overall_voxel_scale / 2.0f };
const color_rgb color_rgb_white = (color_rgb) { 255, 255, 255 };

#define add_voxel_face_uvs_indicies(index)\
    indicies->data[indicies->size + index] = vertices->size + voxel_face_indicies[index];

#define add_voxel_face_uvs_vertices(index) {\
    float3 vertex_position = voxel_face_vertices[index];\
    float3_multiply_float_p(&vertex_position, voxel_scale);\
    float3_add_float3_p(&vertex_position, vertex_position_offset);\
    vertices->data[vertices->size + index] = vertex_position;\
}

#define add_voxel_face_uvs_uvs(index)\
    uvs->data[uvs->size + index] = voxel_face_uvs[index];

// this takes 14ms on a 24core cpu, 6ms though during streaming
// scales vertex, offsets vertex by voxel position in chunk, adds total mesh offset
void add_voxel_face_uvs_d(int_array_d *indicies, float3_array_d* vertices, float2_array_d* uvs, color_rgb_array_d* color_rgbs,
    float3 vertex_position_offset, unsigned char voxel, float voxel_scale,
    const int* voxel_face_indicies, const float3 voxel_face_vertices[], const float2 voxel_face_uvs[], unsigned char direction) {
    expand_capacity_int_array_d(indicies, voxel_face_indicies_length);
        add_voxel_face_uvs_indicies(0)
        add_voxel_face_uvs_indicies(1)
        add_voxel_face_uvs_indicies(2)
        add_voxel_face_uvs_indicies(3)
        add_voxel_face_uvs_indicies(4)
        add_voxel_face_uvs_indicies(5)
    indicies->size += voxel_face_indicies_length;
    expand_capacity_float3_array_d(vertices, voxel_face_vertices_length);
        add_voxel_face_uvs_vertices(0)
        add_voxel_face_uvs_vertices(1)
        add_voxel_face_uvs_vertices(2)
        add_voxel_face_uvs_vertices(3)
    vertices->size += voxel_face_vertices_length;
    expand_capacity_float2_array_d(uvs, voxel_face_vertices_length);
        add_voxel_face_uvs_uvs(0)
        add_voxel_face_uvs_uvs(1)
        add_voxel_face_uvs_uvs(2)
        add_voxel_face_uvs_uvs(3)
    uvs->size += voxel_face_vertices_length;
    for (int a = 0; a < voxel_face_vertices_length; a++) {
        color_rgb vertex_color = color_rgb_white;
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

#define zoxel_octree_build_face_d(direction_name, is_positive, voxel_uvs)\
if (!is_adjacent_all_solid(direction##_##direction_name, root_node, parent_node, neighbors,\
    octree_position, node_index, node_position, depth, max_depth, neighbors_max_depths)) {\
    add_voxel_face_uvs_d(indicies, vertices, uvs, color_rgbs, vertex_position_offset, voxel,\
    voxel_scale, get_voxel_indices(is_positive), voxel_face_vertices##_##direction_name,\
    voxel_uvs, direction##_##direction_name);\
}

#define build_octree_chunk_child_node(i)\
if (chunk_octree->nodes[i].value != 0) {\
    build_octree_chunk_d(root_node, chunk_octree, &chunk_octree->nodes[i], neighbors, neighbors_max_depths,\
        indicies, vertices, uvs, color_rgbs, max_depth, depth, int3_add(octree_position, octree_positions[i]), i);\
}

void build_octree_chunk_d(const ChunkOctree *root_node, const ChunkOctree *parent_node, const ChunkOctree *chunk_octree,
    const ChunkOctree *neighbors[], const unsigned char *neighbors_max_depths,
    int_array_d *indicies, float3_array_d* vertices, float2_array_d* uvs, color_rgb_array_d* color_rgbs,
    const unsigned char max_depth, unsigned char depth, int3 octree_position, const unsigned char node_index) {
    if (depth >= max_depth || chunk_octree->nodes == NULL) {
        if (chunk_octree->value != 0) {
            float voxel_scale = octree_scales3[depth];
            float3 vertex_position_offset = { octree_position.x * voxel_scale, octree_position.y * voxel_scale, octree_position.z * voxel_scale }; //float3_from_int3(octree_position);
            byte3 node_position = octree_positions_b[node_index];
            unsigned char voxel = chunk_octree->value;
            if (voxel == 1) {
                zoxel_octree_build_face_d(left, 0, voxel_uvs_0)
                zoxel_octree_build_face_d(right, 1, voxel_uvs_0)
                zoxel_octree_build_face_d(down, 1, voxel_uvs_0)
                zoxel_octree_build_face_d(up, 0, voxel_uvs_0)
                zoxel_octree_build_face_d(back, 0, voxel_uvs_0)
                zoxel_octree_build_face_d(front, 1, voxel_uvs_0)
            } else { // if (voxel == 2) {
                zoxel_octree_build_face_d(left, 0, voxel_uvs_1)
                zoxel_octree_build_face_d(right, 1, voxel_uvs_1)
                zoxel_octree_build_face_d(down, 1, voxel_uvs_1)
                zoxel_octree_build_face_d(up, 0, voxel_uvs_1)
                zoxel_octree_build_face_d(back, 0, voxel_uvs_1)
                zoxel_octree_build_face_d(front, 1, voxel_uvs_1)
            }
        }
    } else {
        depth++;
        int3_multiply_int_p(&octree_position, 2);
        build_octree_chunk_child_node(0)
        build_octree_chunk_child_node(1)
        build_octree_chunk_child_node(2)
        build_octree_chunk_child_node(3)
        build_octree_chunk_child_node(4)
        build_octree_chunk_child_node(5)
        build_octree_chunk_child_node(6)
        build_octree_chunk_child_node(7)
    }
}

void build_octree_chunk_mesh_uvs(const ChunkOctree *chunk_octree, MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshUVs *meshUVs, MeshColorRGBs *meshColorRGBs,
    unsigned char chunk_division, const ChunkOctree *neighbors[], unsigned char *neighbors_max_depths) {
    unsigned char max_depth = get_max_depth_from_division(chunk_division);
    #ifdef zoxel_voxels_dynamic_array
        int_array_d* indicies = create_int_array_d();
        float3_array_d* vertices = create_float3_array_d();
        float2_array_d* uvs = create_float2_array_d();
        color_rgb_array_d* color_rgbs = create_color_rgb_array_d();
        build_octree_chunk_d(chunk_octree, NULL, chunk_octree, neighbors, neighbors_max_depths, indicies, vertices, uvs, color_rgbs, max_depth, 0, int3_zero, 0);
        if (meshIndicies->length != 0) {
            free(meshIndicies->value);
        }
        if (meshVertices->length != 0) {
            free(meshVertices->value);
        }
        if (meshUVs->length != 0) {
            free(meshUVs->value);
        }
        meshIndicies->length = indicies->size;
        meshVertices->length = vertices->size;
        meshUVs->length = uvs->size;
        meshColorRGBs->length = color_rgbs->size;
        meshIndicies->value = finalize_int_array_d(indicies);
        meshVertices->value = finalize_float3_array_d(vertices);
        meshUVs->value = finalize_float2_array_d(uvs);
        meshColorRGBs->value = finalize_color_rgb_array_d(color_rgbs);
    #else
        int2 *start = &((int2) { 0, 0 });
        count_octree_chunk(chunk_octree, NULL, chunk_octree, neighbors, neighbors_max_depths, meshIndicies, meshVertices, meshUVs, &mesh_count, 0, max_depth, int3_zero, 0, int3_zero);
        re_initialize_memory_component(meshIndicies, int, mesh_count.x);
        re_initialize_memory_component(meshVertices, float3, mesh_count.y);
        re_initialize_memory_component(meshUVs, float2, mesh_count.y);
        build_octree_chunk(chunk_octree, NULL, chunk_octree, neighbors, neighbors_max_depths, meshIndicies, meshVertices, meshUVs, start, 0, max_depth, int3_zero, 0, int3_zero);
    #endif
}

void OctreeChunkBuildSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(it->ctx, NULL)) {
        return;
    }
    #ifdef zoxel_time_octree_chunk_builds_system
        begin_timing()
    #endif
    int chunks_built = 0;
    ChunkDirty *chunkDirtys = ecs_field(it, ChunkDirty, 1);
    const ChunkOctree *chunkOctrees = ecs_field(it, ChunkOctree, 2);
    const ChunkDivision *chunkDivisions = ecs_field(it, ChunkDivision, 3);
    const ChunkNeighbors *chunkNeighbors = ecs_field(it, ChunkNeighbors, 4);
    MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 5);
    MeshVertices *meshVertices = ecs_field(it, MeshVertices, 6);
    MeshUVs *meshUVs = ecs_field(it, MeshUVs, 7);
    MeshColorRGBs *meshColorRGBs = ecs_field(it, MeshColorRGBs, 8);
    ChunkDirtier *chunkDirtiers = ecs_field(it, ChunkDirtier, 9);
    for (int i = 0; i < it->count; i++) {
        ChunkDirty *chunkDirty = &chunkDirtys[i];
        if (chunkDirty->value == 1) {
            // time_cycle_begin()
            ChunkDirtier *chunkDirtier = &chunkDirtiers[i];
            const ChunkOctree *chunkOctree = &chunkOctrees[i];
            const ChunkDivision *chunkDivision = &chunkDivisions[i];
            const ChunkNeighbors *chunkNeighbors2 = &chunkNeighbors[i];
            MeshIndicies *meshIndicies2 = &meshIndicies[i];
            MeshVertices *meshVertices2 = &meshVertices[i];
            MeshUVs *meshUVs2 = &meshUVs[i];
            MeshColorRGBs *meshColorRGBs2 = &meshColorRGBs[i];
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
            unsigned char *neighbors_max_depths = malloc(6);
            neighbors_max_depths[0] = get_max_depth_from_division(chunk_left_max_distance);
            neighbors_max_depths[1] = get_max_depth_from_division(chunk_right_max_distance);
            neighbors_max_depths[2] = get_max_depth_from_division(chunk_down_max_distance);
            neighbors_max_depths[3] = get_max_depth_from_division(chunk_up_max_distance);
            neighbors_max_depths[4] = get_max_depth_from_division(chunk_back_max_distance);
            neighbors_max_depths[5] = get_max_depth_from_division(chunk_front_max_distance);
            chunkDirty->value = 0;
            chunkDirtier->value = 1;
            if (meshIndicies2->length != 0) {
                tri_count -= meshIndicies2->length / 3;
            }
            build_octree_chunk_mesh_uvs(chunkOctree, meshIndicies2, meshVertices2, meshUVs2, meshColorRGBs2, chunkDivision->value, neighbors, neighbors_max_depths);
            if (meshIndicies2->length != 0) {
                tri_count += meshIndicies2->length / 3;
            }
            free(neighbors_max_depths);
            // time_cycle_end("       - octree_chunk_build_cycle")
            chunks_built++;
            if (chunks_built >= max_chunks_build_per_frame) {
                break;
            }
            #ifdef zoxel_time_octree_chunk_builds_system
                did_do_timing()
            #endif
        }
    }
    #ifdef zoxel_time_octree_chunk_builds_system
        end_timing_cutoff("    - octree_chunk_build_system", zoxel_time_octree_chunk_builds_system_cutoff)
    #endif
}
zoxel_declare_system(OctreeChunkBuildSystem)

/*add_block_to_int_array_d(indicies, voxel_face_indicies, voxel_face_indicies_length);
int vertices_size = vertices->size;
for (int a = indicies->size - voxel_face_indicies_length; a < indicies->size; a++) {
    indicies->data[a] += vertices_size;
    // add_to_int_array_d(indicies, vertices->size + voxel_face_indicies[a]);
}*/
// add_block_to_float2_array_d2(uvs, voxel_face_uvs, voxel_face_vertices_length);
// add_block_to_float3_array_d(uvs, vertices, voxel_face_vertices_length);

/*for (unsigned char i = 0; i < octree_length; i++) {
    if (chunk_octree->nodes[i].value != 0)
        build_octree_chunk_d(root_node, chunk_octree, &chunk_octree->nodes[i],
            neighbors, neighbors_max_depths, indicies, vertices, uvs, max_depth, depth,
            int3_add(octree_position, octree_positions[i]), i);
}*/
    /*for (unsigned char a = 0; a < voxel_face_indicies_length; a++) {
        add_to_int_array_d(indicies, vertices->size + voxel_face_indicies[a]);
    }*/

    /*for (unsigned char a = 0; a < voxel_face_vertices_length; a++) {
        float3 vertex_position = voxel_face_vertices[a];
        float3_multiply_float_p(&vertex_position, voxel_scale);
        float3_add_float3_p(&vertex_position, vertex_position_offset);
        float3_add_float3_p(&vertex_position, center_mesh_offset);    
        add_to_float3_array_d(vertices, vertex_position);
        add_to_float2_array_d(uvs, voxel_face_uvs[a]);
    }*/
// making these static is hard...
/*typedef struct {
    float3 *verts_left;
    float3 *verts_right;
    float3 *verts_down;
    float3 *verts_up;
    float3 *verts_back;
    float3 *verts_front;
} cube_verts;*/