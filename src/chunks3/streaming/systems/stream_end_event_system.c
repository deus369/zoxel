// A state checker for stream loading
void StreamEndEventSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(EventInput, eventInputs, 1)
    zox_field_in(ChunkLinks, chunkLinkss, 2)
    zox_field_out(StreamEndEvent, events, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(StreamEndEvent, events, event)
        if (!event->value) {
            continue;
        }
        zox_field_i(ChunkLinks, chunkLinkss, chunkLinks)
        if (!chunkLinks->value || ! chunkLinks->value->size) {
            continue;
        }
        // check all chunkLinks chunks if chunks are dirty
        byte is_skip = 0;
        for (int j = 0; j < chunkLinks->value->size; j++) {
            int3_hashmap_pair* pair = chunkLinks->value->data[j];
            uint checks = 0;
            while (pair != NULL && checks < max_safety_checks_hashmap) {
                const ecs_entity_t chunk = pair->value;
                if (!zox_valid(chunk) || !zox_has(chunk, GenerateChunk) || !zox_has(chunk, ChunkMeshDirty) || !zox_has(chunk, ChunkLodDirty)) {
                    if (!zox_valid(chunk)) {
                        zox_log_error("chunk invalid in stream end system [%lu]", chunk)
                    } else if (!zox_has(chunk, GenerateChunk)) {
                        zox_log_error("chunk has no GenerateChunk [%lu]", chunk)
                    } else if (!zox_has(chunk, ChunkMeshDirty)) {
                        zox_log_error("chunk has no ChunkMeshDirty [%lu]", chunk)
                    }  else if (!zox_has(chunk, ChunkLodDirty)) {
                        zox_log_error("chunk has no ChunkLodDirty [%lu]", chunk)
                    } else {
                        zox_log_error("chunk invalid not sure why[%lu]", chunk)
                    }
                    is_skip = 1;
                } else if (zox_gett_value(chunk, RenderLod) == render_lod_uninitialized) {
                    is_skip = 1;
                } else if (zox_gett_value(chunk, ChunkMeshDirty)) {
                    is_skip = 1;
                } else if (zox_gett_value(chunk, ChunkLodDirty)) {
                    is_skip = 1;
                } else if (zox_gett_value(chunk, GenerateChunk)) {
                    is_skip = 1;
                }
                if (is_skip) {
                    break;
                }
                int3_hashmap_pair* next_pair = pair->next;
                pair = next_pair;
                checks++;
            }
            if (is_skip) {
                break;
            }
        }
        if (!is_skip) {
            if (is_log_streaming) {
                zox_log("+ terrain spawning ended spawning at [%f]", zox_current_time)
            }
            // we should check if all chunks have finished here
            zox_field_world()
            zox_field_i(EventInput, eventInputs, eventInput)
            (*event->value)(world, eventInput->value);
            event->value = NULL;
        }
    }
} zox_declare_system(StreamEndEventSystem)