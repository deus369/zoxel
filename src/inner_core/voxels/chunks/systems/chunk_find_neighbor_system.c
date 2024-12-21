// doesn't check for edge chunks
void ChunkFindNeighborSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(ChunkPosition, chunkPositions, 1)
    zox_field_in(VoxLink, voxLinks, 2)
    zox_field_in(RenderLod, renderLods, 3)
    zox_field_out(ChunkNeighbors, chunkNeighborss, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(RenderLod, renderLods, renderLod)
        // todo: use 255 and 254, 254 for invisible and 255 for initiated
        if (renderLod->value == render_lod_invisible) continue;
        zox_field_i(VoxLink, voxLinks, voxLink)
        if (!voxLink->value) continue;
        zox_field_o(ChunkNeighbors, chunkNeighborss, chunkNeighbors)
        if (chunkNeighbors->length == 0) {
            // zox_log(" ! ChunkNeighbors when finding, length is 0..\n")
            resize_memory_component(ChunkNeighbors, chunkNeighbors, ecs_entity_t, 6)
            for (int i = 0; i < 6; i++) chunkNeighbors->value[i] = 0;
        }
        unsigned char need_find = 0;
        for (int j = 0; j < chunkNeighbors->length; j++) {
            if (!zox_valid(chunkNeighbors->value[j])) {
                need_find = 1;
                break;
            }
        }
        if (!need_find) continue;
        zox_field_i(ChunkPosition, chunkPositions, chunkPosition)
        // link up neighbors if they need to be
        zox_get_muter(voxLink->value, ChunkLinks, chunkLinks)
        for (int j = 0; j < chunkNeighbors->length; j++) {
            if (zox_valid(chunkNeighbors->value[j])) continue;
            chunkNeighbors->value[j] = int3_hashmap_get(chunkLinks->value, int3_add(chunkPosition->value, int3_directions[j]));
        }
    }
} zox_declare_system(ChunkFindNeighborSystem)
