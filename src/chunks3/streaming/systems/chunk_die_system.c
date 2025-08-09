void ChunkDieSystem(iter *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(VoxLink)
    zox_sys_in(ChunkPosition)
    zox_sys_in(RenderDistance)
    zox_sys_in(ChunkLodDirty)
    zox_sys_in(RenderLod)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(VoxLink, voxLink)
        zox_sys_i(RenderLod, renderLod)
        zox_sys_i(ChunkLodDirty, chunkLodDirty)
        zox_sys_i(RenderDistance, renderDistance)
        zox_sys_i(ChunkPosition, chunkPosition)
        if (!zox_valid(voxLink->value)) {
            zox_delete(e)
            continue;
        }
        if (renderLod->value == render_lod_uninitialized) {
            continue;
        }
        if (chunkLodDirty->value) {
            continue;
        }
        // Pass if loading chunk
        if (renderDistance->value == 255) {
            continue;
        }
        // Pass if lod changing
        const byte kill = renderDistance->value > terrain_lod_far;
        if (kill) {
            // remove from hash - can i do this better?
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
} zoxd_system(ChunkDieSystem)