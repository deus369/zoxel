// builds the character vox meshes
void ChunkOctreeColorsBuildSystem(ecs_iter_t *it) {
    begin_timing()
    zox_change_check()
    int chunks_built = 0;
    zox_iter_world()
    zox_field_out(ChunkDirty, chunkDirtys, 1)
    zox_field_in(ChunkOctree, chunkOctrees, 2)
    zox_field_in(RenderLod, renderLods, 3)
    zox_field_in(ChunkNeighbors, chunkNeighbors, 4)
    zox_field_in(ColorRGBs, colorRGBs, 5)
    zox_field_in(ChunkSize, chunkSizes, 6)
    zox_field_in(VoxScale, voxScales, 7)
    zox_field_in(RenderDisabled, renderDisableds, 8)
    zox_field_out(MeshIndicies, meshIndicies, 9)
    zox_field_out(MeshVertices, meshVertices, 10)
    zox_field_out(MeshColorRGBs, meshColorRGBs, 11)
    zox_field_out(MeshDirty, meshDirtys, 12)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(ChunkDirty, chunkDirtys, chunkDirty)
        if (chunkDirty->value == 0) continue;
        zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
        if (renderDisabled->value) continue;
        zox_field_i(RenderLod, renderLods, renderLod)
        zox_field_i(VoxScale, voxScales, voxScale)
        zox_field_o(MeshDirty, meshDirtys, meshDirty)
        zox_field_o(MeshIndicies, meshIndicies, meshIndicies2)
        zox_field_o(MeshVertices, meshVertices, meshVertices2)
        zox_field_o(MeshColorRGBs, meshColorRGBs, meshColorRGBs2)
        if (renderLod->value == 255) { // removes mesh
            clear_mesh(meshIndicies2, meshVertices2, meshColorRGBs2);
            chunkDirty->value = 0;
            meshDirty->value = 1;
            // zox_log("cleared of vox\n")
            continue;
        }
        zox_field_i(ChunkOctree, chunkOctrees, chunkOctree)
        zox_field_i(ChunkNeighbors, chunkNeighbors, chunkNeighbors2)
        zox_field_i(ColorRGBs, colorRGBs, colorRGBs2)
        zox_field_i(ChunkSize, chunkSizes, chunkSize)
        const ChunkOctree *chunk_left = chunkNeighbors2->value[0] == 0 ? NULL : zox_get(chunkNeighbors2->value[0], ChunkOctree)
        const ChunkOctree *chunk_right = chunkNeighbors2->value[1] == 0 ? NULL : zox_get(chunkNeighbors2->value[1], ChunkOctree)
        const ChunkOctree *chunk_down = chunkNeighbors2->value[2] == 0 ? NULL : zox_get(chunkNeighbors2->value[2], ChunkOctree)
        const ChunkOctree *chunk_up = chunkNeighbors2->value[3] == 0 ? NULL : zox_get(chunkNeighbors2->value[3], ChunkOctree)
        const ChunkOctree *chunk_back = chunkNeighbors2->value[4] == 0 ? NULL : zox_get(chunkNeighbors2->value[4], ChunkOctree)
        const ChunkOctree *chunk_front = chunkNeighbors2->value[5] == 0 ? NULL : zox_get(chunkNeighbors2->value[5], ChunkOctree)
        const ChunkOctree *neighbors[] =  { chunk_left, chunk_right, chunk_down, chunk_up, chunk_back, chunk_front };
        const unsigned char chunk_left_max_distance = chunkNeighbors2->value[0] == 0 ? 0 : zox_get_value(chunkNeighbors2->value[0], RenderLod)
        const unsigned char chunk_right_max_distance = chunkNeighbors2->value[1] == 0 ? 0 : zox_get_value(chunkNeighbors2->value[1], RenderLod)
        const unsigned char chunk_down_max_distance = chunkNeighbors2->value[2] == 0 ? 0 : zox_get_value(chunkNeighbors2->value[2], RenderLod)
        const unsigned char chunk_up_max_distance = chunkNeighbors2->value[3] == 0 ? 0 : zox_get_value(chunkNeighbors2->value[3], RenderLod)
        const unsigned char chunk_back_max_distance = chunkNeighbors2->value[4] == 0 ? 0 : zox_get_value(chunkNeighbors2->value[4], RenderLod)
        const unsigned char chunk_front_max_distance = chunkNeighbors2->value[5] == 0 ? 0 : zox_get_value(chunkNeighbors2->value[5], RenderLod)
        unsigned char neighbor_lods[6];
        neighbor_lods[0] = colors_get_max_depth_from_division(chunk_left_max_distance);
        neighbor_lods[1] = colors_get_max_depth_from_division(chunk_right_max_distance);
        neighbor_lods[2] = colors_get_max_depth_from_division(chunk_down_max_distance);
        neighbor_lods[3] = colors_get_max_depth_from_division(chunk_up_max_distance);
        neighbor_lods[4] = colors_get_max_depth_from_division(chunk_back_max_distance);
        neighbor_lods[5] = colors_get_max_depth_from_division(chunk_front_max_distance);
        const float3 total_mesh_offset = float3_multiply_float(calculate_vox_bounds(chunkSize->value, voxScale->value), -1);
        const unsigned char chunk_depth = colors_get_max_depth_from_division(renderLod->value);
        build_chunk_octree_mesh_colors(chunkOctree, colorRGBs2, meshIndicies2, meshVertices2, meshColorRGBs2, chunk_depth, neighbors, neighbor_lods, total_mesh_offset, voxScale->value);
        chunkDirty->value = 0;
        meshDirty->value = 1;
        did_do_timing()
        if (max_color_chunks_build_per_frame != 0) {
            chunks_built++;
            if (chunks_built >= max_color_chunks_build_per_frame) break;
        }
    }
    // end_timing("ChunkOctreeColorsBuildSystem")
} zox_declare_system(ChunkOctreeColorsBuildSystem)

