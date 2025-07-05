ecs_entity_t spawn_element_texture(ecs_world_t *world, const ecs_entity_t canvas, const ecs_entity_t source_texture, const int2 position, const int2 size) {
    if (!source_texture) {
        zox_log_error("[spawn_texture_element]: source_texture is empty.")
        return 0;
    }
    const int2 source_size = zox_get_value(source_texture, TextureSize)
    const TextureData *source_data = zox_get(source_texture, TextureData)
    const ecs_entity_t e = spawn_element_basic_on_canvas(world, canvas, position, size, source_size, float2_zero);
    zox_set(e, TextureData, { source_data->length, source_data->value })
    zox_set(e, TextureDirty, { 1 })
    return e;
}
