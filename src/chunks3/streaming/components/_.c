zox_tag(Streamer);
zox_tag(StreamedChunk);
zoxc_int3(StreamPoint);
zoxc_byte(StreamDirty);
zoxc_function(StreamEndEvent, void, ecs*, const entity);

void define_components_streaming(ecs *world) {
    zox_define_tag(Streamer);
    zox_define_tag(StreamedChunk);
    zox_define_component_int3(StreamPoint);
    zoxd_byte(StreamDirty);
    zox_define_component(StreamEndEvent);
}