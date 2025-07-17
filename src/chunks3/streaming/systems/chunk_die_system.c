void ChunkDieSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(VoxLink, voxLinks, 1)
    zox_field_in(ChunkPosition, chunkPositions, 2)
    zox_field_in(RenderDistance, renderDistances, 3)
    zox_field_in(ChunkLodDirty, chunkLodDirtys, 4)
    zox_field_in(RenderLod, renderLods, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        zox_field_i(VoxLink, voxLinks, voxLink)
        if (!zox_valid(voxLink->value)) {
            zox_delete(e)
            continue;
        }
        zox_field_i(RenderLod, renderLods, renderLod)
        if (renderLod->value == render_lod_uninitialized) {
            continue;
        }
        zox_field_i(ChunkLodDirty, chunkLodDirtys, chunkLodDirty)
        if (chunkLodDirty->value) {
            continue;
        }
        // Pass if loading chunk
        zox_field_i(RenderDistance, renderDistances, renderDistance)
        if (renderDistance->value == 255) {
            continue;
        }
        // Pass if lod changing
        const byte kill = renderDistance->value > terrain_lod_far;
        if (kill) {
            // remove from hash - can i do this better?
            zox_field_i(ChunkPosition, chunkPositions, chunkPosition)
            // zox_get_muter(voxLink->value, ChunkLinks, chunkLinks)
            zox_geter(voxLink->value, ChunkLinks, chunkLinks)
            int3_hashmap_remove(chunkLinks->value, chunkPosition->value);
            // delete (adds to queue)
            zox_delete(e)
            /*#ifdef zox_enable_log_streaming
            if (log_individuals) {
                zox_geter_value(e, ChunkPosition, int3, chunk_position)
                zox_log_streaming("- streaming: remove chunk [%ix%ix%i]", chunk_position.x, chunk_position.y, chunk_position.z)
            }
            #endif*/
        }
    }
} zox_declare_system(ChunkDieSystem)