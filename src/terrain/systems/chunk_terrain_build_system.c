// todo: keep this in hashmap for processed Voxes - atm its gonna check 10k chunks * voxels length which is bad
// todo: support for multiple terrains using hashmap

void build_chunk_terrain_mesh(const ChunkOctree *chunk_octree, const TilemapUVs *tilemap_uvs, MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshUVs *meshUVs, MeshColorRGBs *meshColorRGBs, const byte is_max_depth_chunk, const byte render_depth, const ChunkOctree *neighbors[], const byte neighbor_depths[], const float vert_scale, const byte *voxel_solidity, const int *voxel_uv_indexes, const byte max_depth) {
    const mesh_uvs_build_data mesh_data = {
        .indicies = create_int_array_d(initial_dynamic_array_size),
        .vertices = create_float3_array_d(initial_dynamic_array_size),
        .uvs = create_float2_array_d(initial_dynamic_array_size),
        .color_rgbs = create_color_rgb_array_d(initial_dynamic_array_size)
    };
    // build out mesh data
    const terrain_build_data data = {
        // vox data
        .tilemap_uvs = tilemap_uvs,
        .voxel_solidity = voxel_solidity,
        .voxel_uv_indexes = voxel_uv_indexes,
        .mesh_data = &mesh_data,
        .scale = vert_scale,
        // neighbor data
        .neighbors = neighbors,
        .neighbor_depths = neighbor_depths,
        // chunk data
        .root = chunk_octree,
        .is_max_depth_chunk = is_max_depth_chunk,
        .render_depth = render_depth,
        .max_depth = max_depth,
        #ifndef zox_disable_hidden_terrain_edge
        .edge_voxel = 1,
        #endif
    };
    octree_dig_data dig = {
        .parent = NULL,
        .node = chunk_octree,
        .scale = 2 * terrain_voxel_scale,
        // .index = 0,
        // .position = int3_zero,
        // .depth = 0, // start here and increase
    };
    zox_terrain_building_dig(data, dig);
    // sizes
    meshIndicies->length = mesh_data.indicies->size;
    meshVertices->length = mesh_data.vertices->size;
    meshUVs->length = mesh_data.uvs->size;
    meshColorRGBs->length = mesh_data.color_rgbs->size;
    // data
    meshIndicies->value = finalize_int_array_d(mesh_data.indicies);
    meshVertices->value = finalize_float3_array_d(mesh_data.vertices);
    meshColorRGBs->value = finalize_color_rgb_array_d(mesh_data.color_rgbs);
    meshUVs->value = finalize_float2_array_d(mesh_data.uvs);
    // for data statistics
    on_memory_component_created(meshIndicies, MeshIndicies)
    on_memory_component_created(meshVertices, MeshVertices)
    on_memory_component_created(meshColorRGBs, MeshColorRGBs)
    on_memory_component_created(meshUVs, MeshUVs)
}

#define set_neightbor_chunk_data(dir)\
if (chunkNeighbors->length == 6) {\
    const byte index = direction##_##dir;\
    const ecs_entity_t neighbor = chunkNeighbors->value[index];\
    if (zox_valid(neighbor) && zox_has(neighbor, RenderLod) && zox_has(neighbor, ChunkOctree)) {\
        zox_geter_value(neighbor, RenderLod, byte, neighbor_lod)\
        neighbor_depths[index] = get_chunk_terrain_depth_from_lod(neighbor_lod, max_depth);\
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
    uint updated_count = 0;
    const byte max_depth = max_octree_depth;
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
    if (!zox_valid(terrain) || !zox_has(terrain, RealmLink) || !zox_has(terrain, TilemapLink)) {
        return;
    } // if failed to find terrain parents
    const ecs_entity_t realm = zox_get_value(terrain, RealmLink)
    if (!zox_valid(realm) || !zox_has(realm, VoxelLinks)) {
        return;
    }
    const VoxelLinks *voxelLinks = zox_get(realm, VoxelLinks)
    voxels_length = voxelLinks->length;
    if (voxels_length == 0) {
        return; // if failed to find terrain parents
    }
    const ecs_entity_t tilemap = zox_get_value(terrain, TilemapLink)
    if (!zox_valid(tilemap) || !zox_has(tilemap, TilemapUVs)) {
        return;
    }
    const TilemapUVs *tilemap_uvs = zox_get(tilemap, TilemapUVs)
    if (tilemap_uvs->value == NULL || tilemap_uvs->length == 0) {
        // zox_log(" ! tilemap troubles in chunk building: %lu %i\n", tilemap, tilemap_uvs->length)
        return; // if tilemap generating still
    }
    ChunkTexturedBuildData build_data;
    byte solidity[voxels_length];
    build_data.solidity = solidity;
    int uvs[voxels_length * 6]; //  * sizeof(int)];
    build_data.uvs = uvs;
    // calculate tileuv indexes - voxel and face to index  in tilemap_uvs
    int uvs_index = 0;
    for (int j = 0; j < voxels_length; j++) {
        const ecs_entity_t block = voxelLinks->value[j];
        // solidity
        if (!zox_valid(block) || !zox_has(block, BlockModel)) {
            build_data.solidity[j] = 1;
        } else {
            build_data.solidity[j] = zox_gett_value(block, BlockModel) == zox_block_solid;
        }
        // uvs
        if (!zox_has(block, Textures)) {
            continue;    // no textures...!
        }
        const byte block_textures_length = zox_gett(block, Textures)->length;
        int voxel_uv_indexes_index = j * 6;
        if (block_textures_length == 1) {
            // per voxel, 24 uvs
            for (byte k = 0; k < 6; k++) {
                build_data.uvs[voxel_uv_indexes_index + k] = uvs_index;
                uvs_index += 4;
            }
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
    // zox_field_in(RenderDisabled, renderDisableds, 6)
    zox_field_in(ChunkMeshDirty, chunkMeshDirtys, 7)
    zox_field_out(MeshIndicies, meshIndiciess, 8)
    zox_field_out(MeshVertices, meshVerticess, 9)
    zox_field_out(MeshUVs, meshUVss, 10)
    zox_field_out(MeshColorRGBs, meshColorRGBss, 11)
    zox_field_out(MeshDirty, meshDirtys, 12)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ChunkMeshDirty, chunkMeshDirtys, chunkMeshDirty)
        if (chunkMeshDirty->value != chunk_dirty_state_update) {
            continue;
        }
        /*zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
        if (renderDisabled->value)
        {
            // todo: add prerequisite for states -> renderDisabled must be 0 for trigger to change to update
            //continue;
        }*/
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
            const byte render_depth = get_chunk_terrain_depth_from_lod(renderLod->value, max_depth);

            build_chunk_terrain_mesh(chunkOctree, tilemap_uvs, meshIndicies, meshVertices, meshUVs, meshColorRGBs, is_max_depth_chunk, render_depth, neighbors, neighbor_depths, voxScale->value, build_data.solidity, build_data.uvs, max_depth);
        }
        zox_field_o(MeshDirty, meshDirtys, meshDirty)
        meshDirty->value = mesh_state_trigger;
        updated_count++;
    }
    if (updated_count > 0) {
        zox_log_streaming(" - [%i] updated [%i]", ecs_run_count, updated_count)
    }
} zox_declare_system(ChunkTerrainBuildSystem)