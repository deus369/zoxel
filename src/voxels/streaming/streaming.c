#ifndef zox_mod_streaming
#define zox_mod_streaming

// #define zox_enable_log_streaming
#if defined(zox_enable_log_streaming) && !defined(zox_disable_logs)
    #define zox_log_streaming(msg, ...) zox_log_line(msg, ##__VA_ARGS__)
#else
    #define zox_log_streaming(msg, ...) { }
#endif

#include "data/settings.c"
zox_declare_tag(Streamer)
zox_declare_tag(StreamedChunk)
zox_component_int3(StreamPoint)
zox_component_byte(StreamDirty)
zox_function_component(StreamEndEvent, void, ecs_world_t*, const ecs_entity_t)
#include "systems/systems.c"

zox_begin_module(Streaming)
    zox_define_tag(Streamer)
    zox_define_tag(StreamedChunk)
    zox_define_component_int3(StreamPoint)
    zox_define_component_byte(StreamDirty)
    zox_define_component(StreamEndEvent)
    define_systems_streaming(world);
zox_end_module(Streaming)

#endif