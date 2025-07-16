zox_declare_tag(Streamer)
zox_declare_tag(StreamedChunk)
zox_component_int3(StreamPoint)
zox_component_byte(StreamDirty)
zox_function_component(StreamEndEvent, void, ecs_world_t*, const ecs_entity_t)

void define_components_streaming(ecs_world_t *world) {
    zox_define_tag(Streamer)
    zox_define_tag(StreamedChunk)
    zox_define_component_int3(StreamPoint)
    zox_define_component_byte(StreamDirty)
    zox_define_component(StreamEndEvent)
}