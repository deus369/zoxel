void update_text3D(ecs_world_t *world, const Children *children, const TextData *textData) {
    // calculate checks for spaces new lines etc and removes those
    const int new_children_length = calculate_total_zigels(textData->value, textData->length);
    const int update_count = integer_min(children->length, new_children_length);
    for (int i = 0; i < update_count; i++) {
        const ecs_entity_t e = children->value[i];
        if (!zox_valid(e)) {
            continue;
        }
        const byte zigel_index = calculate_zigel_index(textData->value, textData->length, i);
        const byte old_zigel_index = zox_get_value(e, ZigelIndex)
        if (old_zigel_index != zigel_index) {
            zox_get_muter(e, ZigelIndex, zigelIndex2)
            zox_get_muter(e, GenerateTexture, generateTexture)
            zigelIndex2->value = zigel_index;
            generateTexture->value = zox_generate_texture_trigger;
            zox_log_text("    + zigel [%i] updated [%i:%i]", i, old_zigel_index, zigel_index)
        }
    }
}

// just updates previous zigels to new data
void TextUpdateSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(ZextDirty, zextDirtys, 1)
    zox_field_in(TextData, textDatas, 2)
    zox_field_in(Children, childrens, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ZextDirty, zextDirtys, zextDirty)
        if (zextDirty->value != zext_update_update) {
            continue;
        }
        zox_field_i(Children, childrens, children)
        zox_field_i(TextData, textDatas, textData)
        if (!textData->length) {
            continue;
        }
        char *debug_text = convert_zext_to_text(textData->value, textData->length);
        if (debug_text) {
            zox_log_text("+ updating [%s] text: %s", zox_get_name(it->entities[i]), debug_text)
            free(debug_text);
        } else {
            zox_log_text("+ updating [%s] text [null]",  zox_get_name(it->entities[i]))
        }
        update_text3D(world, children, textData);
        // zox_field_e()
        // zox_log("+ updating text [%s]", zox_get_name(e))
    }
} zox_declare_system(TextUpdateSystem)