// spawning block vox entities during generation step!
// ChunkDirty process or nah?
void BlockVoxSpawnSystem(ecs_iter_t *it) {
    return;
    zox_iter_world()
    zox_field_in(ChunkDirty, chunkDirtys, 1)
    zox_field_in(ChunkOctree, chunkOctrees, 2)
    zox_field_in(ChunkPosition, chunkPositions, 3)
    zox_field_in(ChunkSize, chunkSizes, 4)
    zox_field_in(VoxLink, voxLinks, 5)
    zox_field_in(RenderLod, renderLods, 6)
    zox_field_out(BlockSpawns, blockSpawnss, 7)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(ChunkDirty, chunkDirtys, chunkDirty)
        if (chunkDirty->value != 1) continue;
        zox_field_i_in(VoxLink, voxLinks, voxLink)
        if (!voxLink->value) continue;
        zox_field_i_in(ChunkOctree, chunkOctrees, chunkOctree)
        zox_field_i_in(RenderLod, renderLods, renderLod)
        zox_field_i_in(ChunkPosition, chunkPositions, chunkPosition)
        zox_field_i_in(ChunkSize, chunkSizes, chunkSize)
        zox_field_i_out(BlockSpawns, blockSpawnss, blockSpawns)
        const unsigned char lod = get_terrain_lod_from_camera_distance(renderLod->value);
        // zox_log(" > renderLod->value: %i => %i\n", renderLod->value, lod)
        if (lod == max_octree_depth) {
            byte3 position_local = byte3_zero;
            // VoxelPosition to RealPosition function
            // multiply by VoxScale - position_real
            // add to voxel spawns
            // need a resize function here like arrays
            if (blockSpawns->value == NULL) blockSpawns->value = create_byte3_hash_map(1);
            if (!byte3_hash_map_has(blockSpawns->value, position_local)) {
                int3 position_global = int3_zero; //  int3_add(chunkPosition->value, )
                float3 position_real = float3_add(float3_half, float3_multiply_float(int3_to_float3(chunkPosition->value), 16.0f)); // calculate based on global
                SpawnBlockVox spawn_data = {
                    .prefab = prefab_block_vox,
                    .vox = &vox_files[0],
                    .position_local = position_local,
                    .position_global = position_global,
                    .position_real =position_real,
                    .render_lod = 0, // renderLod->value,
                    .render_disabled = 0 // until i get frustum to cull these
                };
                const ecs_entity_t e2 = spawn_block_vox(world, &spawn_data);
                byte3_hash_map_add(blockSpawns->value, spawn_data.position_local, e2);
                // zox_log(" + spawned vox model: %ix%ix%i\n", chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z)
            }
        } else {
            byte3 position_local = byte3_zero;
            if (blockSpawns->value && byte3_hash_map_has(blockSpawns->value, position_local)) {
                const ecs_entity_t e2 = byte3_hash_map_get(blockSpawns->value, position_local);
                if (e2) {
                    zox_delete(e2)
                    byte3_hash_map_remove(blockSpawns->value, position_local);
                    // zox_log(" + deleted vox model: %ix%ix%i\n", chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z)
                }
            }
        }

        // todo: destroy block voxes if renderLOD not 0
    }
} zox_declare_system(BlockVoxSpawnSystem)

// spawn the things as children to terrain Chunks!
// first initt our vox types array here so i can use that in node checks
// next find blocks of vox type in nodes, and call a spawn_voxel_in_world function!
// Need a ChunkBlocks component - uses voxel positions to store them!
// test for now, with spawn_block_vox
