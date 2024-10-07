void StreamEndEventSystem(ecs_iter_t *it) {
    zox_iter_world()
    const double delta = zox_delta_time;
    zox_field_out(StreamEndEvent, events, 1)
    zox_field_in(EventInput, eventInputs, 2)
    zox_field_in(StreamDirty, streamDirtys, 3)
    zox_field_in(ChunkLinks, chunkLinkss, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(StreamEndEvent, events, event)
        if (!event->value) continue;
        zox_field_i(StreamDirty, streamDirtys, streamDirty)
        // todo: use this to trigger a check when done state on chunks
        // for now we check per frame
        if (streamDirty->value) continue;
        zox_field_i(ChunkLinks, chunkLinkss, chunkLinks)
        // check all chunkLinks chunks if chunks are dirty
        unsigned char is_terrain_dirty = 0;
        for (int j = 0; j < chunkLinks->value->size; j++) {
            int3_hashmap_pair* pair = chunkLinks->value->data[j];
            uint checks = 0;
            while (pair != NULL && checks < max_safety_checks_hashmap) {
                // use value from pair
                ecs_entity_t chunk = pair->value;
                const unsigned char is_generating = zox_get_value(chunk, GenerateChunk)
                const unsigned char is_dirty = zox_get_value(chunk, ChunkDirty)
                if (is_generating || is_dirty) {
                    is_terrain_dirty = 1;
                    break;
                }
                int3_hashmap_pair* next_pair = pair->next;
                pair = next_pair;
                checks++;
            }
            if (is_terrain_dirty) break;
        }
        if (is_terrain_dirty) break;
        // we should check if all chunks have finished here
        zox_field_i(EventInput, eventInputs, eventInput)
        (*event->value)(world, eventInput->value);
        event->value = NULL;
        zox_log("Streaming Ended!\n")

    }
} zox_declare_system(StreamEndEventSystem)
