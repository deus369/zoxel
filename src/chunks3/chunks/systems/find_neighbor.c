// doesn't check for edge chunks
void ChunkFindNeighborSystem(iter *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(ChunkPosition)
    zox_sys_in(VoxLink)
    zox_sys_in(RenderLod)
    zox_sys_out(ChunkNeighbors)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ChunkPosition, chunkPosition)
        zox_sys_i(RenderLod, renderLod)
        zox_sys_i(VoxLink, voxLink)
        zox_sys_o(ChunkNeighbors, chunkNeighbors)
        // todo: use 255 and 254, 254 for invisible and 255 for initiated
        if (renderLod->value == render_lod_invisible || !voxLink->value) {
            continue;
        }
        byte need_find = 0;
        for (int j = 0; j < chunk_neighbors_length; j++) {
            if (!zox_valid(chunkNeighbors->value[j])) {
                need_find = 1;
                break;
            }
        }
        if (!need_find) {
            continue;
        }
        // link up neighbors if they need to be
        zox_get_muter(voxLink->value, ChunkLinks, chunkLinks)
        for (int j = 0; j < chunk_neighbors_length; j++) {
            if (zox_valid(chunkNeighbors->value[j])) {
                continue;
            }
            const int3 neighbor_position = int3_add(chunkPosition->value, int3_directions[j]);
            const entity neighbor = int3_hashmap_get(chunkLinks->value, neighbor_position);
            if (zox_valid(neighbor)) {
                chunkNeighbors->value[j] = neighbor;
            }
        }
    }
} zox_declare_system(ChunkFindNeighborSystem)