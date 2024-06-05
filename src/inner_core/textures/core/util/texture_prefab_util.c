void prefab_add_texture(ecs_world_t *world, const ecs_entity_t e, const int2 size) {
    zox_add_tag(e, Texture)
    zox_add(e, TextureData)
    zox_prefab_set(e, TextureSize, { size })
    zox_prefab_set(e, TextureDirty, { 0 })
}


void prefab_add_texture_generated(ecs_world_t *world, const ecs_entity_t e, const int2 size, const unsigned char generate_state) {
    prefab_add_texture(world, e, size);
    add_seed(world, e, 666);
    zox_prefab_set(e, GenerateTexture, { generate_state })
}


void clone_texture_data(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t source) {
    if (!source || !zox_has(source, TextureSize) || !zox_has(source, TextureData)) return;
    const int2 size = zox_get_value(source, TextureSize)
    zox_set(e, TextureSize, { size })
    const TextureData *source_data = zox_get(source, TextureData)
    TextureData *data = zox_get_mut(e, TextureData)
    data->length = source_data->length;
    const int bytes_length = sizeof(color) * source_data->length;
    data->value = memcpy(malloc(bytes_length), source_data->value, bytes_length);
    zox_modified(e, TextureData)
}
