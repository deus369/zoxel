void prefab_add_texture(ecs_world_t *world, const ecs_entity_t e, const int2 size) {
    zox_add_tag(e, Texture)
    zox_add(e, TextureData)
    zox_prefab_set(e, TextureSize, { size })
    zox_prefab_set(e, TextureDirty, { 0 })
}

void prefab_add_texture_generated(ecs_world_t *world, const ecs_entity_t e, const int2 size, const byte generate_state) {
    prefab_add_texture(world, e, size);
    add_seed(world, e, 666);
    zox_prefab_set(e, GenerateTexture, { generate_state })
}

void clear_texture_data(ecs_world_t *world, const ecs_entity_t e) {
    if (!e || !zox_has(e, TextureData)) return;
    zox_get_muter(e, TextureData, data)
    if (data->value) free(data->value); // remember to free it first
    data->value = NULL;
    data->length = 0;
}

void clone_texture_data(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t source) {
    if (!source || !zox_has(source, TextureSize) || !zox_has(source, TextureData)) return;
    const int2 size = zox_get_value(source, TextureSize)
    zox_set(e, TextureSize, { size })
    const TextureData *source_data = zox_get(source, TextureData)
    zox_get_muter(e, TextureData, data)
    data->length = source_data->length;
    const int bytes_length = sizeof(color) * source_data->length;
    if (data->value) free(data->value); // remember to free it first
    data->value = memcpy(malloc(bytes_length), source_data->value, bytes_length);
}
