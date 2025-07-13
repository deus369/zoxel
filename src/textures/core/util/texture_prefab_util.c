void prefab_add_texture(ecs_world_t *world, const ecs_entity_t e, const int2 size) {
    zox_add_tag(e, Texture)
    zox_prefab_set(e, TextureData, { 0, NULL })
    zox_prefab_set(e, TextureSize, { size })
    zox_prefab_set(e, TextureDirty, { 0 })
}

void prefab_add_texture_generated(ecs_world_t *world, const ecs_entity_t e, const int2 size, const byte generate_state) {
    prefab_add_texture(world, e, size);
    zox_prefab_set(e, Seed, { 666 })
    zox_prefab_set(e, GenerateTexture, { generate_state })
}

void clear_texture_data(ecs_world_t *world, const ecs_entity_t e) {
    if (!e || !zox_has(e, TextureData)) return;

    zox_geter(e, TextureData, oldData)
    if (oldData->value) free(oldData->value);

    TextureData *data = &((TextureData) { 0, NULL });
    zox_set(e, TextureData, { data->length, data->value })

    // zox_get_muter(e, TextureData, data)
    //if (data->value) free(data->value); // remember to free it first
    //data->value = NULL;
    //data->length = 0;
}

void clone_texture_data(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t source) {
    if (!source || !zox_has(source, TextureSize) || !zox_has(source, TextureData)) {
        if (!source) {
            zox_log_error("[texture not found] [%s]", zox_get_name(e))
        } else {
            zox_log_error("[texture invalid] [%s] > source [%s]", zox_get_name(e), zox_get_name(source))
        }
        return;
    }
    const TextureData *source_data = zox_get(source, TextureData)
    if (source_data->length == 0 || !source_data->value) {
        zox_log("! clone_texture_data invalid source data [%lu] > source [%lu]\n", e, source)
        return;
    }
    const int2 size = zox_get_value(source, TextureSize)
    const int bytes_length = sizeof(color) * source_data->length;
    // free old one
    if (zox_has(e, TextureData)) {
        zox_geter(e, TextureData, oldData)
        if (oldData->value) {
            free(oldData->value);
        }
    }
    TextureData data = { 0, NULL };
    data.length = source_data->length;
    data.value = malloc(bytes_length);
    if (!data.value) {
        zox_log("! texture data malloc failed\n")
        return;
    }
    memcpy(data.value, source_data->value, bytes_length);
    zox_set(e, TextureData, { data.length, data.value })
    zox_set(e, TextureSize, { size })
}
