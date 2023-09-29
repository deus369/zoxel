const unsigned char color_edge_voxel = 0;
const int max_color_chunks_build_per_frame = 16;
unsigned char zox_lowres_characters_mode = 0;

unsigned char colors_get_max_depth_from_division(unsigned char chunk_division) {
    unsigned char max_depth = max_octree_depth;
    max_depth = max_depth - chunk_division;
    return max_depth;
}

#define add_voxel_face_colors_indicies(index) indicies->data[indicies->size + index] = vertices->size + voxel_face_indicies[index];

#define add_voxel_face_colors_vertices(index) {\
    float3 vertex_position = voxel_face_vertices[index];\
    float3_multiply_float_p(&vertex_position, voxel_scale);\
    float3_add_float3_p(&vertex_position, vertex_position_offset);\
    vertices->data[vertices->size + index] = vertex_position;\
}

// this takes 14ms on a 24core cpu, 6ms though during streaming
// scales vertex, offsets vertex by voxel position in chunk, adds total mesh offset
void add_voxel_face_colors_d(int_array_d *indicies, float3_array_d* vertices, color_rgb_array_d* color_rgbs, float3 vertex_position_offset, color_rgb voxel_color, float voxel_scale, const int* voxel_face_indicies, const float3 voxel_face_vertices[], unsigned char direction) {
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

#define zoxel_octree_colors_build_face_d(direction_name, is_positive)\
if (!is_adjacent_all_solid(direction##_##direction_name, root_node, parent_node, neighbors,\
    octree_position, node_index, node_position, depth, max_depth, neighbor_lods, color_edge_voxel)) {\
    add_voxel_face_colors_d(indicies, vertices, color_rgbs, vertex_position_offset, voxel_color,\
        voxel_scale, get_voxel_indices(is_positive), voxel_face_vertices##_##direction_name,\
        direction##_##direction_name);\
}

// basically it goes downwards even if upper value nodes are air
// so with our optimizing somewhere it messed up and set the upper ones to zero? idk
// or maybe it was optimized properly
#define build_octree_chunk_colors_child_node(i)\
if (!(chunk_octree->nodes[i].nodes == NULL && chunk_octree->nodes[i].value == 0)) {\
    build_octree_chunk_colors_d(root_node, chunk_octree, &chunk_octree->nodes[i], neighbors, neighbor_lods, colorRGBs, indicies, vertices, color_rgbs, max_depth, depth, int3_add(octree_position, octree_positions[i]), i, total_mesh_offset);\
}

// test function builds one cube

void test_build_octree_chunk_colors_d(const ChunkOctree *root_node, const ChunkOctree *parent_node, const ChunkOctree *chunk_octree, const ChunkOctree *neighbors[], const unsigned char *neighbor_lods, const ColorRGBs *colorRGBs, int_array_d *indicies, float3_array_d* vertices, color_rgb_array_d* color_rgbs, const unsigned char max_depth, unsigned char depth, int3 octree_position, const unsigned char node_index, float3 total_mesh_offset) {
    unsigned char voxel = chunk_octree->value;
    float voxel_scale = octree_scales3[depth] * model_scale;
    float3 vertex_position_offset = float3_from_int3(octree_position);
    float3_multiply_float_p(&vertex_position_offset, voxel_scale);
    float3_add_float3_p(&vertex_position_offset, total_mesh_offset);
    byte3 node_position = octree_positions_b[node_index];
    //if (voxel != 0) {
        color_rgb voxel_color = colorRGBs->value[voxel - 1];
        zoxel_octree_colors_build_face_d(left, 0)
        zoxel_octree_colors_build_face_d(right, 1)
        zoxel_octree_colors_build_face_d(down, 1)
        zoxel_octree_colors_build_face_d(up, 0)
        zoxel_octree_colors_build_face_d(back, 0)
        zoxel_octree_colors_build_face_d(front, 1)
    //}
}

void test_build_chunk_octree_mesh_colors(const ChunkOctree *chunk_octree, const ColorRGBs *colorRGBs, MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshColorRGBs *meshColorRGBs, unsigned char chunk_depth, const ChunkOctree *neighbors[], unsigned char *neighbor_lods, float3 total_mesh_offset) {
    int_array_d* indicies = create_int_array_d();
    float3_array_d* vertices = create_float3_array_d();
    color_rgb_array_d* color_rgbs = create_color_rgb_array_d();
    test_build_octree_chunk_colors_d(chunk_octree, NULL, chunk_octree, neighbors, neighbor_lods, colorRGBs, indicies, vertices, color_rgbs, chunk_depth, 0, int3_zero, 0, total_mesh_offset);
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

void build_octree_chunk_colors_d(const ChunkOctree *root_node, const ChunkOctree *parent_node, const ChunkOctree *chunk_octree, const ChunkOctree *neighbors[], const unsigned char *neighbor_lods, const ColorRGBs *colorRGBs, int_array_d *indicies, float3_array_d* vertices, color_rgb_array_d* color_rgbs, const unsigned char max_depth, unsigned char depth, int3 octree_position, const unsigned char node_index, float3 total_mesh_offset) {
    if (depth >= max_depth || chunk_octree->nodes == NULL) {
        if (chunk_octree->value != 0) {
            float voxel_scale = octree_scales3[depth] * model_scale;
            float3 vertex_position_offset = float3_from_int3(octree_position);
            float3_multiply_float_p(&vertex_position_offset, voxel_scale);
            float3_add_float3_p(&vertex_position_offset, total_mesh_offset);
            byte3 node_position = octree_positions_b[node_index];
            unsigned char voxel = chunk_octree->value;
            color_rgb voxel_color = colorRGBs->value[voxel - 1];
            zoxel_octree_colors_build_face_d(left, 0)
            zoxel_octree_colors_build_face_d(right, 1)
            zoxel_octree_colors_build_face_d(down, 1)
            zoxel_octree_colors_build_face_d(up, 0)
            zoxel_octree_colors_build_face_d(back, 0)
            zoxel_octree_colors_build_face_d(front, 1)
        }
    } else {
        depth++;
        int3_multiply_int_p(&octree_position, 2);
        build_octree_chunk_colors_child_node(0)
        build_octree_chunk_colors_child_node(1)
        build_octree_chunk_colors_child_node(2)
        build_octree_chunk_colors_child_node(3)
        build_octree_chunk_colors_child_node(4)
        build_octree_chunk_colors_child_node(5)
        build_octree_chunk_colors_child_node(6)
        build_octree_chunk_colors_child_node(7)
    }
}

void build_chunk_octree_mesh_colors(const ChunkOctree *chunk_octree, const ColorRGBs *colorRGBs, MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshColorRGBs *meshColorRGBs, unsigned char chunk_depth, const ChunkOctree *neighbors[], unsigned char *neighbor_lods, float3 total_mesh_offset) {
    int_array_d* indicies = create_int_array_d();
    float3_array_d* vertices = create_float3_array_d();
    color_rgb_array_d* color_rgbs = create_color_rgb_array_d();
    build_octree_chunk_colors_d(chunk_octree, NULL, chunk_octree, neighbors, neighbor_lods, colorRGBs, indicies, vertices, color_rgbs, chunk_depth, 0, int3_zero, 0, total_mesh_offset);
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

void ChunkOctreeColorsBuildSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(it->ctx, NULL)) return;
    #ifdef zoxel_time_octree_chunk_builds_system
        begin_timing()
    #endif
    int chunks_built = 0;
    ChunkDirty *chunkDirtys = ecs_field(it, ChunkDirty, 1);
    const ChunkOctree *chunkOctrees = ecs_field(it, ChunkOctree, 2);
    const RenderLod *renderLods = ecs_field(it, RenderLod, 3);
    const ChunkNeighbors *chunkNeighbors = ecs_field(it, ChunkNeighbors, 4);
    const ColorRGBs *colorRGBs = ecs_field(it, ColorRGBs, 5);
    const ChunkSize *chunkSizes = ecs_field(it, ChunkSize, 6);
    MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 7);
    MeshVertices *meshVertices = ecs_field(it, MeshVertices, 8);
    MeshColorRGBs *meshColorRGBs = ecs_field(it, MeshColorRGBs, 9);
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 10);
    unsigned char *neighbor_lods = malloc(6);
    for (int i = 0; i < it->count; i++) {
        ChunkDirty *chunkDirty = &chunkDirtys[i];
        if (chunkDirty->value != 1) continue;
        MeshDirty *meshDirty = &meshDirtys[i];
        const RenderLod *renderLod = &renderLods[i];
        MeshIndicies *meshIndicies2 = &meshIndicies[i];
        MeshVertices *meshVertices2 = &meshVertices[i];
        MeshColorRGBs *meshColorRGBs2 = &meshColorRGBs[i];
        if (renderLod->value == 255) { // hides mesh
            chunkDirty->value = 0;
            meshDirty->value = 1;
            clear_mesh(meshIndicies2, meshVertices2, meshColorRGBs2);
            continue;
        }
        const ChunkOctree *chunkOctree = &chunkOctrees[i];
        const ChunkNeighbors *chunkNeighbors2 = &chunkNeighbors[i];
        const ColorRGBs *colorRGBs2 = &colorRGBs[i];
        const ChunkSize *chunkSize = &chunkSizes[i];
        const ChunkOctree *chunk_left = chunkNeighbors2->value[0] == 0 ? NULL : ecs_get(it->world, chunkNeighbors2->value[0], ChunkOctree);
        const ChunkOctree *chunk_right = chunkNeighbors2->value[1] == 0 ? NULL : ecs_get(it->world, chunkNeighbors2->value[1], ChunkOctree);
        const ChunkOctree *chunk_down = chunkNeighbors2->value[2] == 0 ? NULL : ecs_get(it->world, chunkNeighbors2->value[2], ChunkOctree);
        const ChunkOctree *chunk_up = chunkNeighbors2->value[3] == 0 ? NULL : ecs_get(it->world, chunkNeighbors2->value[3], ChunkOctree);
        const ChunkOctree *chunk_back = chunkNeighbors2->value[4] == 0 ? NULL : ecs_get(it->world, chunkNeighbors2->value[4], ChunkOctree);
        const ChunkOctree *chunk_front = chunkNeighbors2->value[5] == 0 ? NULL : ecs_get(it->world, chunkNeighbors2->value[5], ChunkOctree);
        const ChunkOctree *neighbors[] =  { chunk_left, chunk_right, chunk_down, chunk_up, chunk_back, chunk_front };
        unsigned char chunk_left_max_distance = chunkNeighbors2->value[0] == 0 ? 0 : ecs_get(it->world, chunkNeighbors2->value[0], RenderLod)->value;
        unsigned char chunk_right_max_distance = chunkNeighbors2->value[1] == 0 ? 0 : ecs_get(it->world, chunkNeighbors2->value[1], RenderLod)->value;
        unsigned char chunk_down_max_distance = chunkNeighbors2->value[2] == 0 ? 0 : ecs_get(it->world, chunkNeighbors2->value[2], RenderLod)->value;
        unsigned char chunk_up_max_distance = chunkNeighbors2->value[3] == 0 ? 0 : ecs_get(it->world, chunkNeighbors2->value[3], RenderLod)->value;
        unsigned char chunk_back_max_distance = chunkNeighbors2->value[4] == 0 ? 0 : ecs_get(it->world, chunkNeighbors2->value[4], RenderLod)->value;
        unsigned char chunk_front_max_distance = chunkNeighbors2->value[5] == 0 ? 0 : ecs_get(it->world, chunkNeighbors2->value[5], RenderLod)->value;
        neighbor_lods[0] = colors_get_max_depth_from_division(chunk_left_max_distance);
        neighbor_lods[1] = colors_get_max_depth_from_division(chunk_right_max_distance);
        neighbor_lods[2] = colors_get_max_depth_from_division(chunk_down_max_distance);
        neighbor_lods[3] = colors_get_max_depth_from_division(chunk_up_max_distance);
        neighbor_lods[4] = colors_get_max_depth_from_division(chunk_back_max_distance);
        neighbor_lods[5] = colors_get_max_depth_from_division(chunk_front_max_distance);
        float3 total_mesh_offset = calculate_vox_bounds(chunkSize->value);
        float3_multiply_float_p(&total_mesh_offset, -1); // * 4.0f);
        unsigned char chunk_depth = colors_get_max_depth_from_division(renderLod->value);
        if (zox_lowres_characters_mode) test_build_chunk_octree_mesh_colors(chunkOctree, colorRGBs2, meshIndicies2, meshVertices2, meshColorRGBs2, chunk_depth, neighbors, neighbor_lods, total_mesh_offset);
        else build_chunk_octree_mesh_colors(chunkOctree, colorRGBs2, meshIndicies2, meshVertices2, meshColorRGBs2, chunk_depth, neighbors, neighbor_lods, total_mesh_offset);
        chunkDirty->value = 0;
        meshDirty->value = 1;
        // zoxel_log(" > built character [%lu] [%i]\n", it->entities[i], meshIndicies2->length);
        chunks_built++;
        if (chunks_built >= max_color_chunks_build_per_frame) break;
        #ifdef zoxel_time_octree_chunk_builds_system
            did_do_timing()
        #endif
    }
    free(neighbor_lods);
    #ifdef zoxel_time_octree_chunk_builds_system
        end_timing_cutoff("    - octree_chunk_build_system", zoxel_time_octree_chunk_builds_system_cutoff)
    #endif
} zox_declare_system(ChunkOctreeColorsBuildSystem)