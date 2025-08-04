
void clear_texture_data(ecs_world_t *world, const ecs_entity_t e) {
    if (!zox_valid(e) || !zox_has(e, TextureData)) {
        return;
    }
    //zox_geter(e, TextureData, old)
    zox_muter(e, TextureData, old)
    if (old->value) {
        dispose_TextureData_const(old);
    }
}

void clone_texture_data(ecs_world_t *world,
    const ecs_entity_t e,
    const ecs_entity_t source)
{
    if (!source || !zox_has(source, TextureSize) || !zox_has(source, TextureData)) {
        if (!source) {
            zox_log_error("[texture not found] [%s]", zox_get_name(e))
        } else {
            zox_log_error("[texture invalid] [%s] > source [%s]", zox_get_name(e), zox_get_name(source))
        }
        return;
    }
    zox_geter(source, TextureData, source_data)
    if (source_data->length == 0 || !source_data->value) {
        zox_log("! clone_texture_data invalid source data [%lu] > source [%lu]\n", e, source)
        return;
    }
    zox_geter_value(source, TextureSize, int2, size)
    const int bytes_length = sizeof(color) * source_data->length;
    // free old one
    if (zox_has(e, TextureData)) {
        zox_geter(e, TextureData, oldData);
        if (oldData->value) {
            dispose_TextureData_const(oldData);
        }
    }
    TextureData data = { 0, NULL };
    initialize_TextureData(&data, source_data->length);
    //data.length = source_data->length;
    //data.value = malloc(bytes_length);
    if (!data.value) {
        zox_log_error("texture data malloc failed")
        return;
    }
    memcpy(data.value, source_data->value, bytes_length);
    zox_set_ptr(e, TextureData, data);
    zox_set(e, TextureSize, { size });
}
