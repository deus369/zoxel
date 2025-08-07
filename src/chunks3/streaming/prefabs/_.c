#include "streamer.c"
entity prefab_chunk_streaming;
entity prefab_streamer;

void spawn_prefabs_streaming(ecs *world) {
    prefab_streamer = spawn_prefab_streamer(world);
}