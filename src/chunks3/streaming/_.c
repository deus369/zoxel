#ifndef zox_mod_streaming
#define zox_mod_streaming

#include "settings/_.c"
zox_declare_tag(Streamer)
zox_declare_tag(StreamedChunk)
zox_component_int3(StreamPoint)
zox_component_byte(StreamDirty)
zox_function_component(StreamEndEvent, void, ecs_world_t*, const ecs_entity_t)
#include "prefabs/_.c"
#include "util/_.c"
#include "systems/_.c"

zox_begin_module(Streaming)
    zox_define_tag(Streamer)
    zox_define_tag(StreamedChunk)
    zox_define_component_int3(StreamPoint)
    zox_define_component_byte(StreamDirty)
    zox_define_component(StreamEndEvent)
    define_systems_streaming(world);
    initialize_settings_streaming(world);
zox_end_module(Streaming)

#endif