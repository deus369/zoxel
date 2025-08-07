#include "label.c"

extern ecs_entity_t get_linked_terrain(ecs_world_t*, ecs_entity_t);


void test_load_chunk(ecs_world_t *world, int32_t keycode) {
    if (keycode == SDLK_l) {
        zox_log("Testing Load Chunks");
        ecs_entity_t terrain = get_linked_terrain(world, local_realm);
        if (!zox_valid(terrain)) {
            zox_log("No Terrain.");
            return;
        }
        zox_geter(terrain, ChunkLinks, chunks);
        for (uint i = 0; i < chunks->value->size; i++) {
            int3_hashmap_pair* pair = chunks->value->data[i];
            uint checks = 0;
            while (pair != NULL && checks < max_safety_checks_hashmap) {
                ecs_entity_t chunk = pair->value;
                if (zox_valid(chunk)) {
                    zox_geter_value(chunk, ChunkPosition, int3, position);
                    zox_get_muter(chunk, VoxelNode, node);
                    load_chunk(world, position, node);
                    // make sure flagged
                    zox_set(chunk, VoxelNodeEdited, { 1 });
                    zox_set(chunk, VoxelNodeDirty, { 1 });
                }
                pair = pair->next;
                checks++;
            }
        }


    }
}