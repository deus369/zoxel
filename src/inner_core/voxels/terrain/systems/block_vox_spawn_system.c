// spawning block vox entities during generation step!
// ChunkDirty process or nah?
extern unsigned char get_voxes_lod_from_camera_distance(unsigned char distance_to_camera);
int spawned_block_voxes = 0;
// todo: destroy block voxes if removed from chunk, check hashes / current block voxes
// todo: also check if hashes exist but voxel type has changed!

// first check if exists, if it does check if voxel type differs, for removing/adding
// goes through nodes, if not in hashmap, it  will spawn anew
void spawn_block_vox_in_tree(const ChunkOctree *octree, BlockSpawns *block_spawns, SpawnBlockVox *spawn_data, const float3 chunk_position_real, int3 octree_position, unsigned char depth, const ecs_entity_t *block_voxes, const unsigned char *block_vox_offsets) {
    // todo: pass in array of index to is_models
    if (depth == max_octree_depth) {
        if (octree->value == 0) return; // air returns!
        // cheeck if vox model
        const unsigned char block_index = octree->value - 1;
        if (!block_voxes[block_index]) return; // only for block vox models
        /*if (octree->value != zox_block_grass_vox) return; // only spawn for grass_vox atm */
        if (count_byte3_hash_map(block_spawns->value) == max_vox_blocks) return; // max
        spawn_data->position_local = int3_to_byte3(octree_position);
        if (byte3_hash_map_has(block_spawns->value, spawn_data->position_local)) return;

        spawn_data->vox = block_voxes[block_index];
        // ChunkScale (0.5f) * ChunkSize (16)
        const float voxel_scale = octree_scales2[depth] * 0.5f * 16.0f; // todo: use voxel scale passed in
        float3 position_real = float3_from_int3(octree_position);
        float3_multiply_float_p(&position_real, voxel_scale);
        float3_add_float3_p(&position_real, chunk_position_real);
        // 0.5f * ChunkScale - which is 0.5f = 0.25f
        float3_add_float3_p(&position_real, (float3) { -0.25f, -0.25f, -0.25f });
        if (block_vox_offsets[block_index]) {
            float3_add_float3_p(&position_real, (float3) { 0, -0.125f, 0 });
        }
        spawn_data->position_real = position_real;
        // spawn our block voxes
        const ecs_entity_t e2 = spawn_block_vox(world, spawn_data);
        byte3_hash_map_add(block_spawns->value, spawn_data->position_local, e2);
        // zox_log(" + spawned vox model: depth %i - scale %f - %ix%ix%i - r [%fx%fx%f] - [%i]\n", depth, voxel_scale, octree_position.x, octree_position.y, octree_position.z, position_real.x, position_real.y, position_real.z, count_byte3_hash_map(block_spawns->value))
        spawned_block_voxes++;
    } else if (octree->nodes) {
        int3_multiply_int_p(&octree_position, 2);
        for (int i = 0; i < octree_length; i++) {
            int3 child_octree_position = int3_add(octree_position, octree_positions[i]);
            spawn_block_vox_in_tree(&octree->nodes[i], block_spawns, spawn_data, chunk_position_real, child_octree_position, depth + 1, block_voxes, block_vox_offsets);
        }
    }
}

void BlockVoxSpawnSystem(ecs_iter_t *it) {
#ifdef zox_disable_block_voxes
    return;
#endif
    ecs_entity_t *block_voxes = NULL;
    unsigned char *block_vox_offsets = NULL;
    begin_timing()
    zox_iter_world()
    zox_field_in(ChunkLodDirty, chunkLodDirtys, 1)
    zox_field_in(ChunkOctree, chunkOctrees, 2)
    zox_field_in(ChunkPosition, chunkPositions, 3)
    zox_field_in(ChunkSize, chunkSizes, 4)
    zox_field_in(VoxLink, voxLinks, 5)
    zox_field_in(RenderLod, renderLods, 6)
    zox_field_in(RenderDisabled, renderDisableds, 7)
    zox_field_out(BlockSpawns, blockSpawnss, 8)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(ChunkLodDirty, chunkLodDirtys, chunkLodDirty)
        if (chunkLodDirty->value != 3) continue;
        zox_field_i_in(VoxLink, voxLinks, voxLink)
        if (!voxLink->value) continue;
        zox_field_i_in(ChunkOctree, chunkOctrees, chunkOctree)
        zox_field_i_in(ChunkPosition, chunkPositions, chunkPosition)
        zox_field_i_in(ChunkSize, chunkSizes, chunkSize)
        zox_field_i_in(RenderLod, renderLods, renderLod)
        zox_field_i_in(RenderDisabled, renderDisableds, renderDisabled)
        zox_field_i_out(BlockSpawns, blockSpawnss, blockSpawns)
        const unsigned char camera_distance = renderLod->value;
        const unsigned char can_have_block_voxes = camera_distance <= block_vox_render_distance;
        if (can_have_block_voxes) {
            if (block_voxes == NULL) {
                const ecs_entity_t realm = zox_get_value(voxLink->value, RealmLink)
                const VoxelLinks *voxelLinks = zox_get(realm, VoxelLinks)
                block_voxes = malloc(voxelLinks->length * sizeof(ecs_entity_t));
                block_vox_offsets = malloc(voxelLinks->length);
                for (int j = 0; j < voxelLinks->length; j++) {
                    const ecs_entity_t block = voxelLinks->value[j];
                    if (zox_gett_value(block, BlockModel) == zox_block_vox) {
                        // block_voxes[j] = vox_files[test_block_vox_index];
                        block_voxes[j] = zox_get_value(block, ModelLink)
                        if (zox_has(block, BlockVoxOffset)) block_vox_offsets[j] = zox_get_value(block, BlockVoxOffset)
                        else block_vox_offsets[j] = 0;
                    } else {
                        block_voxes[j] = 0;
                        block_vox_offsets[j] = 0;
                    }
                }

            }
            if (blockSpawns->value == NULL) blockSpawns->value = create_byte3_hash_map(max_vox_blocks);
            const unsigned char vox_lod = get_voxes_lod_from_camera_distance(camera_distance);
            float3 chunk_position_real = float3_add(float3_half, float3_multiply_float(int3_to_float3(chunkPosition->value), 16.0f)); // calculate
            SpawnBlockVox spawn_data = {
                .prefab = prefab_block_vox,
                // .vox = vox_files[test_block_vox_index],
                .render_lod = vox_lod,
                .render_disabled = renderDisabled->value // until i get frustum to cull these
            };
            spawn_block_vox_in_tree(chunkOctree, blockSpawns, &spawn_data, chunk_position_real, int3_zero, 0, block_voxes, block_vox_offsets);
        } else {
            if (blockSpawns->value) {
                for (int j = 0; j < blockSpawns->value->size; j++) {
                    const byte3_hash_map_pair* pair = blockSpawns->value->data[j];
                    while (pair != NULL) {
                        const ecs_entity_t e2 = pair->value;
                        if (e2) zox_delete(e2)
                        pair = pair->next;
                    }
                }
                byte3_hash_map_dispose(blockSpawns->value);
                blockSpawns->value = NULL;
            }
        }
        did_do_timing()
    }
    if (block_voxes) free(block_voxes);
    if (block_vox_offsets) free(block_vox_offsets);
    //end_timing("BlockVoxSpawnSystem")
    //if (did_do) zox_log("   + spawned_block_voxes [%i] delta_time [%f]\n", spawned_block_voxes, zox_delta_time * 1000)
    // if (did_do == 1) zox_log("   + block spawns spawned / destroyed\n")
} zox_declare_system(BlockVoxSpawnSystem)

// spawn the things as children to terrain Chunks!
// first initt our vox types array here so i can use that in node checks
// next find blocks of vox type in nodes, and call a spawn_voxel_in_world function!
// Need a ChunkBlocks component - uses voxel positions to store them!
// test for now, with spawn_block_vox


// function here that returns voxel local position, and type
/*typedef struct {
    byte3 position_local;
    float3 position_real;
    unsigned char value;
} GetVoxelData;

void get_voxel_data(const ChunkOctree *chunk_octree, GetVoxelData *data) {

}*/
