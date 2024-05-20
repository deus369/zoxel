void ChunkOctreeBuildSystem(ecs_iter_t *it) {
    zox_change_check()
#ifdef zoxel_time_octree_chunk_builds_system
    begin_timing()
#endif
#ifdef zox_octree_chunk_build_limits
    int chunks_built = 0;
#endif
    unsigned char *neighbor_lods = NULL;
    unsigned char *voxel_solidity = NULL;
    zox_iter_world()
    zox_field_in(ChunkOctree, chunkOctrees, 2)
    zox_field_in(RenderLod, renderLods, 3)
    zox_field_in(ChunkNeighbors, chunkNeighbors, 4)
    zox_field_in(VoxLink, voxLinks, 5)
    zox_field_out(ChunkDirty, chunkDirtys, 1)
    zox_field_out(MeshIndicies, meshIndiciess, 6)
    zox_field_out(MeshVertices, meshVerticess, 7)
    zox_field_out(MeshUVs, meshUVss, 8)
    zox_field_out(MeshColorRGBs, meshColorRGBss, 9)
    zox_field_out(MeshDirty, meshDirtys, 10)
    zox_field_in(VoxScale, voxScales, 11)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(ChunkDirty, chunkDirtys, chunkDirty)
        if (!chunkDirty->value) continue;
        zox_field_i_in(RenderLod, renderLods, renderLod)
        zox_field_i_in(VoxScale, voxScales, voxScale)
        const unsigned char lod = get_terrain_lod_from_camera_distance(renderLod->value);
        zox_field_i_out(MeshDirty, meshDirtys, meshDirty)
        zox_field_i_out(MeshIndicies, meshIndiciess, meshIndicies)
        zox_field_i_out(MeshVertices, meshVerticess, meshVertices)
        zox_field_i_out(MeshColorRGBs, meshColorRGBss, meshColorRGBs)
        zox_field_i_out(MeshUVs, meshUVss, meshUVs)
        if (lod == 255) { // hides mesh
            clear_mesh_uvs(meshIndicies, meshVertices, meshColorRGBs, meshUVs);
            chunkDirty->value = 0;
            meshDirty->value = 1;
            continue;
        }
        zox_field_i_in(VoxLink, voxLinks, voxLink)
        // waits for tilemap generation to finish
        const TilemapLink *tilemapLink = zox_get(voxLink->value, TilemapLink)
        const TilemapUVs *tilemapUVs = zox_get(tilemapLink->value, TilemapUVs)
        // get solidity from voxel links
        // todo: keep this in hashmap for processed Voxes - atm its gonna check 10k chunks * voxels length which is bad
        if (!voxel_solidity) {
            const ecs_entity_t realm = zox_get_value(voxLink->value, RealmLink)
            const VoxelLinks *voxelLinks = zox_get(realm, VoxelLinks)
            voxel_solidity = malloc(voxelLinks->length);
            for (int j = 0; j < voxelLinks->length; j++) {
                const ecs_entity_t block = voxelLinks->value[j];
                voxel_solidity[j] = zox_gett_value(block, BlockModel) == zox_block_solid;
                // zox_log(" > [%i] solid? %i\n", j, voxel_solidity[j])
            }
        }
        // waits for tilemap generation to be done
        if (tilemapUVs->value == NULL || tilemapUVs->length == 0) continue;
        zox_field_i_in(ChunkOctree, chunkOctrees, chunkOctree)
        zox_field_i_in(ChunkNeighbors, chunkNeighbors, chunkNeighbors2)
        const ChunkOctree *neighbors[6];
        if (!neighbor_lods) neighbor_lods = malloc(6);
        set_neightbor_chunk_data(left)
        set_neightbor_chunk_data(right)
        set_neightbor_chunk_data(down)
        set_neightbor_chunk_data(up)
        set_neightbor_chunk_data(back)
        set_neightbor_chunk_data(front)
        build_chunk_octree_mesh_uvs(chunkOctree, tilemapUVs, meshIndicies, meshVertices, meshUVs, meshColorRGBs, renderLod->value, lod, neighbors, neighbor_lods, voxScale->value, voxel_solidity);
        chunkDirty->value = 0;
        meshDirty->value = 1;
#ifdef zox_octree_chunk_build_limits
        chunks_built++;
        if (chunks_built >= max_chunks_build_per_frame) break;
#endif
#ifdef zoxel_time_octree_chunk_builds_system
        did_do_timing()
#endif
    }
    if (voxel_solidity) free(voxel_solidity);
    if (neighbor_lods) free(neighbor_lods);
#ifdef zoxel_time_octree_chunk_builds_system
    end_timing_cutoff("    - octree_chunk_build_system", zoxel_time_octree_chunk_builds_system_cutoff)
#endif
} zox_declare_system(ChunkOctreeBuildSystem)
