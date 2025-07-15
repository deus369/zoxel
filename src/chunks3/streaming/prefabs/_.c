#include "streamer.c"
ecs_entity_t prefab_chunk_streaming;
ecs_entity_t prefab_streamer;

void spawn_prefabs_streaming(ecs_world_t *world) {
    prefab_streamer = spawn_prefab_streamer(world);
}