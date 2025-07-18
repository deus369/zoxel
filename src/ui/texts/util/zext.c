// #define zoxel_debug_zext_updates

void set_zox_name(ZoxName *zoxName, const char* text) {
    const int text_length = text != NULL ? strlen(text) : 0;
    if (zoxName->length != text_length) {
        resize_memory_component(ZoxName, zoxName, byte, text_length)
    }
    for (int i = 0; i < text_length; i++) {
        zoxName->value[i] = convert_ascii(text[i]);
    }
}

char* get_zext_text(const TextData *textData) {
    return convert_zext_to_text(textData->value, textData->length);
}

byte is_zext(TextData *zext, const char* text) {
    if (!zext || !zext->value) {
        return 0; // error
    }
    const int text_length = text != NULL ? strlen(text) : 0;
    if (zext->length != text_length) {
        return 0;
    }
    if (text_length == 0 && zext->length == 0) {
        return 1;
    }
    for (int i = 0; i < text_length; i++) {
        byte j = convert_ascii(text[i]);
        byte k = zext->value[i];
        if (j != k) {
            return 0;
        }
    }
    return 1;
}

void set_zext(TextData *textData, const char* text) {
    const int text_length = text != NULL ? strlen(text) : 0;
    if (textData->length != text_length) {
        resize_memory_component(TextData, textData, byte, text_length)
    }
    for (int i = 0; i < text_length; i++) {
        textData->value[i] = convert_ascii(text[i]);
    }
}

void print_entity_zext(ecs_world_t *world, const ecs_entity_t e) {
    if (!zox_has(e, TextData)) {
        return;
    }
    const TextData *textData = zox_get(e, TextData)
    char *text = get_zext_text(textData);
    zox_log("   > zext %lu [%s] length %i\n", e, text, textData->length)
    free(text);
}

byte is_zext_updating(ecs_world_t *world, const Children *children) {
    for (int i = 0; i < children->length; i++) { // update the reused ones
        const ecs_entity_t zigel = children->value[i];
        const byte generate_texture = zox_get_value(zigel, GenerateTexture)
        if (generate_texture) {
            return 1;
        }
    }
    return 0;
}


void set_entity_label_with_zext(ecs_world_t *world, const ecs_entity_t parent, byte *value, int length) {
    const Children *name_label_children = zox_get(parent, Children)
    ecs_entity_t e = name_label_children->value[0];
    zox_get_muter(e, TextData, textData)
    if (textData->value) {
        free(textData->value);
    }
    textData->value = memcpy(malloc(length), value, length);
    textData->length = length;
    zox_modified(e, TextData)
    zox_set(e, ZextDirty, { zext_update_start })
}

byte set_entity_text(ecs_world_t *world, const ecs_entity_t e, const char* text) {
    if (!zox_valid(e) || !zox_has(e, TextData) || !zox_has(e, ZextDirty)) {
        zox_log_error("invalid zext in [set_entity_text]")
        return 0;
    }
    zox_mut_begin(e, TextData, textData)
    if (!is_zext(textData, text)) {
        set_zext(textData, text);
        zox_mut_end(e, TextData)
        zox_set(e, ZextDirty, { zext_update_start })
        return 1;
    } else {
        return 0;
    }
}

byte set_entity_text_raw(ecs_world_t *world, const ecs_entity_t e, const char* text) {
    TextData *textData = &((TextData) { 0, NULL });
    set_zext(textData, text);
    zox_set(e, TextData, { textData->length, textData->value })
    zox_set(e, ZextDirty, { zext_update_start })
    return 1;
}

byte set_entity_label_with_text(ecs_world_t *world, const ecs_entity_t e, const char* text) {
    const Children *children = zox_get(e, Children)
    if (children->length == 0) return 0;
    return set_entity_text(world, children->value[0], text);
}

void set_new_zox_name(ecs_world_t *world, const ecs_entity_t e, const char* text) {
    zox_set_zext_component(e, ZoxName, text)
}


int get_zexts_count(ecs_world_t *world) {
    return zox_count_types(Zext)
}
