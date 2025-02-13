// runs even when all chunks have stopped generating
void StreamEndEventSystem(ecs_iter_t *it) {
    zox_field_in(EventInput, eventInputs, 1)
    zox_field_in(ChunkLinks, chunkLinkss, 2)
    zox_field_out(StreamEndEvent, events, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(StreamEndEvent, events, event)
        if (!event->value) continue;
        zox_field_i(ChunkLinks, chunkLinkss, chunkLinks)
        if (!chunkLinks->value || ! chunkLinks->value->size) continue;
        // check all chunkLinks chunks if chunks are dirty
        byte is_skip = 0;
        for (int j = 0; j < chunkLinks->value->size; j++) {
            int3_hashmap_pair* pair = chunkLinks->value->data[j];
            uint checks = 0;
            while (pair != NULL && checks < max_safety_checks_hashmap) {
                ecs_entity_t chunk = pair->value;
                const byte valid_chunk = zox_valid(chunk) && zox_has(chunk, GenerateChunk) && zox_has(chunk, ChunkMeshDirty) && zox_has(chunk, ChunkLodDirty);
                if (!valid_chunk || zox_gett_value(chunk, GenerateChunk) || zox_gett_value(chunk, ChunkMeshDirty) || zox_gett_value(chunk, ChunkLodDirty)) {
                    is_skip = 1;
                    break;
                }
                int3_hashmap_pair* next_pair = pair->next;
                pair = next_pair;
                checks++;
            }
            if (is_skip) break;
        }
        if (!is_skip) {
            // we should check if all chunks have finished here
            zox_field_world()
            zox_field_i(EventInput, eventInputs, eventInput)
            (*event->value)(world, eventInput->value);
            event->value = NULL;
        }
    }
} zox_declare_system(StreamEndEventSystem)

// zox_field_i(StreamDirty, streamDirtys, streamDirty)
// todo: use this to trigger a check when done state on chunks
// for now we check per frame
// if (streamDirty->value) continue;
