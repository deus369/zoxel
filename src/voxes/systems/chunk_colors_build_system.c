// builds the character vox meshes
void ChunkColorsBuildSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(ChunkMeshDirty)
    zox_sys_in(VoxelNode)
    zox_sys_in(NodeDepth)
    zox_sys_in(RenderLod)
    zox_sys_in(ChunkNeighbors)
    zox_sys_in(ColorRGBs)
    zox_sys_in(ChunkSize)
    zox_sys_in(VoxScale)
    zox_sys_out(MeshIndicies)
    zox_sys_out(MeshVertices)
    zox_sys_out(MeshColorRGBs)
    zox_sys_out(MeshDirty)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ChunkMeshDirty, chunkMeshDirty)
        zox_sys_i(VoxelNode, voxelNode)
        zox_sys_i(NodeDepth, nodeDepth)
        zox_sys_i(RenderLod, renderLod)
        zox_sys_i(ChunkNeighbors, chunkNeighbors)
        zox_sys_i(ColorRGBs, colorRGBs)
        zox_sys_i(ChunkSize, chunkSize)
        zox_sys_i(VoxScale, voxScale)
        zox_sys_o(MeshDirty, meshDirty)
        zox_sys_o(MeshIndicies, meshIndicies)
        zox_sys_o(MeshVertices, meshVertices)
        zox_sys_o(MeshColorRGBs, meshColorRGBs)
        if (chunkMeshDirty->value != chunk_dirty_state_update) {
            continue;
        }
        // removes mesh when 255
        clear_mesh(meshIndicies, meshVertices, meshColorRGBs);
        if (renderLod->value < 254) {
            const byte max_depth = nodeDepth->value;
            const VoxelNode *chunk_left = chunkNeighbors->value[0] == 0 ? NULL : zox_get(chunkNeighbors->value[0], VoxelNode)
            const VoxelNode *chunk_right = chunkNeighbors->value[1] == 0 ? NULL : zox_get(chunkNeighbors->value[1], VoxelNode)
            const VoxelNode *chunk_down = chunkNeighbors->value[2] == 0 ? NULL : zox_get(chunkNeighbors->value[2], VoxelNode)
            const VoxelNode *chunk_up = chunkNeighbors->value[3] == 0 ? NULL : zox_get(chunkNeighbors->value[3], VoxelNode)
            const VoxelNode *chunk_back = chunkNeighbors->value[4] == 0 ? NULL : zox_get(chunkNeighbors->value[4], VoxelNode)
            const VoxelNode *chunk_front = chunkNeighbors->value[5] == 0 ? NULL : zox_get(chunkNeighbors->value[5], VoxelNode)
            const VoxelNode *neighbors[] =  { chunk_left, chunk_right, chunk_down, chunk_up, chunk_back, chunk_front };
            const byte chunk_left_max_distance = chunkNeighbors->value[0] == 0 ? 0 : zox_get_value(chunkNeighbors->value[0], RenderLod)
            const byte chunk_right_max_distance = chunkNeighbors->value[1] == 0 ? 0 : zox_get_value(chunkNeighbors->value[1], RenderLod)
            const byte chunk_down_max_distance = chunkNeighbors->value[2] == 0 ? 0 : zox_get_value(chunkNeighbors->value[2], RenderLod)
            const byte chunk_up_max_distance = chunkNeighbors->value[3] == 0 ? 0 : zox_get_value(chunkNeighbors->value[3], RenderLod)
            const byte chunk_back_max_distance = chunkNeighbors->value[4] == 0 ? 0 : zox_get_value(chunkNeighbors->value[4], RenderLod)
            const byte chunk_front_max_distance = chunkNeighbors->value[5] == 0 ? 0 : zox_get_value(chunkNeighbors->value[5], RenderLod)
            byte neighbor_lods[6];
            neighbor_lods[0] = get_chunk_division_from_lod(chunk_left_max_distance, max_depth);
            neighbor_lods[1] = get_chunk_division_from_lod(chunk_right_max_distance, max_depth);
            neighbor_lods[2] = get_chunk_division_from_lod(chunk_down_max_distance, max_depth);
            neighbor_lods[3] = get_chunk_division_from_lod(chunk_up_max_distance, max_depth);
            neighbor_lods[4] = get_chunk_division_from_lod(chunk_back_max_distance, max_depth);
            neighbor_lods[5] = get_chunk_division_from_lod(chunk_front_max_distance, max_depth);
            const float3 total_mesh_offset = float3_multiply_float(calculate_vox_bounds(chunkSize->value, voxScale->value), -1);
            const byte chunk_depth = get_chunk_division_from_lod(renderLod->value, max_depth);
            build_node_mesh_colors(
                voxelNode,
                colorRGBs,
                meshIndicies,
                meshVertices,
                meshColorRGBs,
                chunk_depth,
                neighbors,
                neighbor_lods,
                total_mesh_offset,
                voxScale->value);
        }
        meshDirty->value = mesh_state_trigger;
    }
} zox_declare_system(ChunkColorsBuildSystem)