// todo: keep this in hashmap for processed Voxes - atm its gonna check 10k chunks * voxels length which is bad
// todo: support for multiple terrains using hashmap

#define set_neightbor_chunk_data(dir)\
if (chunkNeighbors->length == 6) {\
    const byte index = direction##_##dir;\
    const ecs_entity_t neighbor = chunkNeighbors->value[index];\
    if (zox_valid(neighbor) && zox_has(neighbor, RenderLod) && zox_has(neighbor, ChunkOctree)) {\
        zox_geter_value(neighbor, RenderLod, byte, neighbor_lod)\
        neighbor_depths[index] =  get_chunk_terrain_depth_from_lod(neighbor_lod);\
        neighbors[index] = zox_get(neighbor, ChunkOctree);\
    } else {\
        neighbor_depths[index] = 0;\
        neighbors[index] = 0;\
    }\
}

void ChunkTerrainBuildSystem(ecs_iter_t *it) {
#ifdef zox_disable_chunk_building
    return;
#endif
    // zox_change_check()
    // begin_timing()
    zox_field_world()
    zox_field_in(VoxLink, voxLinks, 1)
    int voxels_length = 0;
    ecs_entity_t terrain;
    for (int i = 0; i < it->count; i++) {
        zox_field_i(VoxLink, voxLinks, voxLink)
        if (!voxLink->value) continue;
        terrain = voxLink->value;
        break;
    }
    if (!zox_valid(terrain) || !zox_has(terrain, RealmLink) || !zox_has(terrain, TilemapLink)) return; // if failed to find terrain parents
    const ecs_entity_t realm = zox_get_value(terrain, RealmLink)
    if (!zox_valid(realm) || !zox_has(realm, VoxelLinks)) return;
    const VoxelLinks *voxelLinks = zox_get(realm, VoxelLinks)
    voxels_length = voxelLinks->length;
    if (voxels_length == 0) return; // if failed to find terrain parents
    const ecs_entity_t tilemap = zox_get_value(terrain, TilemapLink)
    if (!zox_valid(tilemap) || !zox_has(tilemap, TilemapUVs)) return;
    const TilemapUVs *tilemapUVs = zox_get(tilemap, TilemapUVs)
    if (tilemapUVs->value == NULL || tilemapUVs->length == 0) {
        // zox_log(" ! tilemap troubles in chunk building: %lu %i\n", tilemap, tilemapUVs->length)
        return; // if tilemap generating still
    }
    ChunkTexturedBuildData build_data;
    byte solidity[voxels_length];
    int uvs[voxels_length * 6 * sizeof(int)];
    build_data.solidity = solidity;
    build_data.uvs = uvs;
    // calculate tileuv indexes - voxel and face to index  in tilemapUVs
    int uvs_index = 0;
    for (int j = 0; j < voxelLinks->length; j++) {
        const ecs_entity_t block = voxelLinks->value[j];
        // solidity
        if (!zox_valid(block) || !zox_has(block, BlockModel)) build_data.solidity[j] = 1;
        else build_data.solidity[j] = zox_gett_value(block, BlockModel) == zox_block_solid;
        // uvs
        if (!zox_has(block, Textures)) continue;    // no textures...!
        const byte block_textures_length = zox_gett(block, Textures)->length;
        int voxel_uv_indexes_index = j * 6;
        if (block_textures_length == 1) {
            // per voxel, 24 uvs
            for (byte k = 0; k < 6; k++) build_data.uvs[voxel_uv_indexes_index + k] = uvs_index;
            uvs_index += 4;
        } else {
            // for 6 sides textured voxes
            for (byte k = 0; k < 6; k++) {
                build_data.uvs[voxel_uv_indexes_index + k] = uvs_index;
                uvs_index += 4;
            }
        }
    }
    zox_field_in(ChunkOctree, chunkOctrees, 2)
    zox_field_in(RenderLod, renderLods, 3)
    zox_field_in(ChunkNeighbors, chunkNeighborss, 4)
    zox_field_in(VoxScale, voxScales, 5)
    zox_field_in(RenderDisabled, renderDisableds, 6)
    zox_field_in(ChunkMeshDirty, chunkMeshDirtys, 7)
    zox_field_out(MeshIndicies, meshIndiciess, 8)
    zox_field_out(MeshVertices, meshVerticess, 9)
    zox_field_out(MeshUVs, meshUVss, 10)
    zox_field_out(MeshColorRGBs, meshColorRGBss, 11)
    zox_field_out(MeshDirty, meshDirtys, 12)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ChunkMeshDirty, chunkMeshDirtys, chunkMeshDirty)
        if (chunkMeshDirty->value != chunk_dirty_state_update) continue;
        zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
        if (renderDisabled->value)
        {
            // todo: add prerequisite for states -> renderDisabled must be 0 for trigger to change to update
            //continue;
        }
        zox_field_i(ChunkNeighbors, chunkNeighborss, chunkNeighbors)
        if (chunkNeighbors->length == 0) {
            zox_log(" ! chunkNeighbors issue...\n")
            continue;
        }
        zox_field_i(RenderLod, renderLods, renderLod)
        if (renderLod->value == render_lod_uninitialized) {
            zox_log(" ! render_lod_uninitialized...\n")
            continue;
        }
        zox_field_i(VoxScale, voxScales, voxScale)
        zox_field_o(MeshIndicies, meshIndiciess, meshIndicies)
        zox_field_o(MeshVertices, meshVerticess, meshVertices)
        zox_field_o(MeshColorRGBs, meshColorRGBss, meshColorRGBs)
        zox_field_o(MeshUVs, meshUVss, meshUVs)
        clear_mesh_uvs(meshIndicies, meshVertices, meshColorRGBs, meshUVs);
        if (renderLod->value != render_lod_invisible) {
            const ChunkOctree *neighbors[chunkNeighbors->length];
            byte neighbor_depths[chunkNeighbors->length];
            set_neightbor_chunk_data(left)
            set_neightbor_chunk_data(right)
            set_neightbor_chunk_data(down)
            set_neightbor_chunk_data(up)
            set_neightbor_chunk_data(back)
            set_neightbor_chunk_data(front)
            zox_field_i(ChunkOctree, chunkOctrees, chunkOctree)

            const byte is_max_depth_chunk = renderLod->value == 0;
            const byte chunk_depth = get_chunk_terrain_depth_from_lod(renderLod->value);

            build_chunk_terrain_mesh(chunkOctree, tilemapUVs, meshIndicies, meshVertices, meshUVs, meshColorRGBs, is_max_depth_chunk, chunk_depth, neighbors, neighbor_depths, voxScale->value, build_data.solidity, build_data.uvs);
        }
        zox_field_o(MeshDirty, meshDirtys, meshDirty)
        meshDirty->value = mesh_state_trigger;
    }
} zox_declare_system(ChunkTerrainBuildSystem)
