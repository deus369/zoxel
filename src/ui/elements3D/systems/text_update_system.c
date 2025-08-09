void update_text3D(ecs *world, const Children *children, const TextData *textData) {
    // calculate checks for spaces new lines etc and removes those
    const int new_children_length = calculate_total_zigels(textData->value, textData->length);
    const int update_count = int_min(children->length, new_children_length);
    for (int i = 0; i < update_count; i++) {
        const entity e = children->value[i];
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
void TextUpdateSystem(iter *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(ZextDirty)
    zox_sys_in(TextData)
    zox_sys_in(Children)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ZextDirty, zextDirty)
        zox_sys_i(Children, children)
        zox_sys_i(TextData, textData)
        if (zextDirty->value != zext_update_update || !textData->length) {
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
        // zox_sys_e()
        // zox_log("+ updating text [%s]", zox_get_name(e))
    }
} zoxd_system(TextUpdateSystem)