// builds the character vox meshes
void ChunkOctreeColorsBuildSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(ChunkMeshDirty, chunkMeshDirtys, 1)
    zox_field_in(ChunkOctree, chunkOctrees, 2)
    zox_field_in(RenderLod, renderLods, 3)
    zox_field_in(ChunkNeighbors, chunkNeighbors, 4)
    zox_field_in(ColorRGBs, colorRGBss, 5)
    zox_field_in(ChunkSize, chunkSizes, 6)
    zox_field_in(VoxScale, voxScales, 7)
    zox_field_out(MeshIndicies, meshIndiciess, 9)
    zox_field_out(MeshVertices, meshVerticess, 10)
    zox_field_out(MeshColorRGBs, meshColorRGBss, 11)
    zox_field_out(MeshDirty, meshDirtys, 12)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ChunkMeshDirty, chunkMeshDirtys, chunkMeshDirty)
        if (chunkMeshDirty->value != chunk_dirty_state_update) {
            continue;
        }
        zox_field_i(RenderLod, renderLods, renderLod)
        zox_field_o(MeshDirty, meshDirtys, meshDirty)
        zox_field_o(MeshIndicies, meshIndiciess, meshIndicies)
        zox_field_o(MeshVertices, meshVerticess, meshVertices)
        zox_field_o(MeshColorRGBs, meshColorRGBss, meshColorRGBs)
        // removes mesh when 255
        clear_mesh(meshIndicies, meshVertices, meshColorRGBs);
        if (renderLod->value < 254) {
            // clear_mesh(meshIndicies, meshVertices, meshColorRGBs);
        // } else {
            // zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
            // if (renderDisabled->value) continue;
            zox_field_i(ChunkOctree, chunkOctrees, chunkOctree)
            zox_field_i(ChunkNeighbors, chunkNeighbors, chunkNeighbors2)
            zox_field_i(ColorRGBs, colorRGBss, colorRGBs)
            zox_field_i(ChunkSize, chunkSizes, chunkSize)
            zox_field_i(VoxScale, voxScales, voxScale)
            const byte max_depth = chunkOctree->linked;
            const ChunkOctree *chunk_left = chunkNeighbors2->value[0] == 0 ? NULL : zox_get(chunkNeighbors2->value[0], ChunkOctree)
            const ChunkOctree *chunk_right = chunkNeighbors2->value[1] == 0 ? NULL : zox_get(chunkNeighbors2->value[1], ChunkOctree)
            const ChunkOctree *chunk_down = chunkNeighbors2->value[2] == 0 ? NULL : zox_get(chunkNeighbors2->value[2], ChunkOctree)
            const ChunkOctree *chunk_up = chunkNeighbors2->value[3] == 0 ? NULL : zox_get(chunkNeighbors2->value[3], ChunkOctree)
            const ChunkOctree *chunk_back = chunkNeighbors2->value[4] == 0 ? NULL : zox_get(chunkNeighbors2->value[4], ChunkOctree)
            const ChunkOctree *chunk_front = chunkNeighbors2->value[5] == 0 ? NULL : zox_get(chunkNeighbors2->value[5], ChunkOctree)
            const ChunkOctree *neighbors[] =  { chunk_left, chunk_right, chunk_down, chunk_up, chunk_back, chunk_front };
            const byte chunk_left_max_distance = chunkNeighbors2->value[0] == 0 ? 0 : zox_get_value(chunkNeighbors2->value[0], RenderLod)
            const byte chunk_right_max_distance = chunkNeighbors2->value[1] == 0 ? 0 : zox_get_value(chunkNeighbors2->value[1], RenderLod)
            const byte chunk_down_max_distance = chunkNeighbors2->value[2] == 0 ? 0 : zox_get_value(chunkNeighbors2->value[2], RenderLod)
            const byte chunk_up_max_distance = chunkNeighbors2->value[3] == 0 ? 0 : zox_get_value(chunkNeighbors2->value[3], RenderLod)
            const byte chunk_back_max_distance = chunkNeighbors2->value[4] == 0 ? 0 : zox_get_value(chunkNeighbors2->value[4], RenderLod)
            const byte chunk_front_max_distance = chunkNeighbors2->value[5] == 0 ? 0 : zox_get_value(chunkNeighbors2->value[5], RenderLod)
            byte neighbor_lods[6];
            neighbor_lods[0] = get_chunk_division_from_lod(chunk_left_max_distance, max_depth);
            neighbor_lods[1] = get_chunk_division_from_lod(chunk_right_max_distance, max_depth);
            neighbor_lods[2] = get_chunk_division_from_lod(chunk_down_max_distance, max_depth);
            neighbor_lods[3] = get_chunk_division_from_lod(chunk_up_max_distance, max_depth);
            neighbor_lods[4] = get_chunk_division_from_lod(chunk_back_max_distance, max_depth);
            neighbor_lods[5] = get_chunk_division_from_lod(chunk_front_max_distance, max_depth);
            const float3 total_mesh_offset = float3_multiply_float(calculate_vox_bounds(chunkSize->value, voxScale->value), -1);
            const byte chunk_depth = get_chunk_division_from_lod(renderLod->value, max_depth);
            // BuildChunkColored build_chunk_colored = { };
            build_chunk_octree_mesh_colors(chunkOctree, colorRGBs, meshIndicies, meshVertices, meshColorRGBs, chunk_depth, neighbors, neighbor_lods, total_mesh_offset, voxScale->value);
        }
        meshDirty->value = mesh_state_trigger;
        // zox_log("+ built vox [%s]: [%i]\n", zox_get_name(it->entities[i]), meshIndicies->length)
    }
} zox_declare_system(ChunkOctreeColorsBuildSystem)

