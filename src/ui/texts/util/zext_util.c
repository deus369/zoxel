// #define zoxel_debug_zext_updates

void set_zox_name(ZoxName *zoxName, const char* text) {
    // int text_length = strlen(text);
    const int text_length = text != NULL ? strlen(text) : 0;
    if (zoxName->length != text_length) resize_memory_component(ZoxName, zoxName, unsigned char, text_length)
    for (int i = 0; i < text_length; i++) zoxName->value[i] = convert_ascii(text[i]);
}

char* get_zext_text(const ZextData *zextData) {
    return convert_zext_to_text(zextData->value, zextData->length);
}

unsigned char is_zext(ZextData *zext, const char* text) {
    if (zext == NULL || zext->value == NULL) return 0; // error
    // int text_length = strlen(text);
    const int text_length = text != NULL ? strlen(text) : 0;
    if (zext->length != text_length) return 0;
    if (text_length == 0 && zext->length == 0) return 1;
    for (int i = 0; i < text_length; i++) {
        if (convert_ascii(text[i]) != zext->value[i]) return 0;
    }
    return 1;
}

void set_zext(ZextData *zextData, const char* text) {
    // const int text_length = strlen(text);
    const int text_length = text != NULL ? strlen(text) : 0;
    // zox_log("   - set zext [%i]\n", text_length)
    if (zextData->length != text_length) resize_memory_component(ZextData, zextData, unsigned char, text_length)
    for (int i = 0; i < text_length; i++) zextData->value[i] = convert_ascii(text[i]);
}

void print_entity_zext(ecs_world_t *world, const ecs_entity_t e) {
    if (!zox_has(e, ZextData)) return;
    const ZextData *zextData = zox_get(e, ZextData)
    char *text = get_zext_text(zextData);
    zox_log("   > zext %lu [%s] length %i\n", e, text, zextData->length)
    free(text);
}

unsigned char is_zext_updating(ecs_world_t *world, const Children *children) {
    for (int i = 0; i < children->length; i++) { // update the reused ones
        const ecs_entity_t zigel = children->value[i];
        const unsigned char generate_texture = zox_get_value(zigel, GenerateTexture)
        if (generate_texture) return 1;
    }
    return 0;
}

//! Dynamically updates zext by spawning/destroying zigels and updating remaining
void spawn_zext_zigels(ecs_world_t *world, SpawnZigel *data, Children *children, const ZextData *zextData) {
    const int old_children_length = children->length;
    const int new_children_length = calculate_total_zigels(zextData->value, zextData->length);
    const int has_old_children = old_children_length > 0;
    const int reuse_count = integer_min(old_children_length, new_children_length);
#ifdef zoxel_debug_zext_updates
    zox_log("spawn_zext_zigels :: [%i] -> [%i]; reuse [%i];\n", children->length, zextData->length, reuse_count)
#endif
#ifdef zoxel_debug_zext_updates
    if (children->length == zextData->length) zox_log("    - zext remained the same [%i]\n", zextData->length)
#endif
    ecs_entity_t *old_children = children->value;
    ecs_entity_t *new_children = NULL;
    if (new_children_length > 0) new_children = malloc(new_children_length * sizeof(ecs_entity_t));
    children->value = new_children;
    children->length = new_children_length;
    // Set Data for Old Zigels
    for (int i = 0; i < reuse_count; i++) {
        const ecs_entity_t e = old_children[i];
        const unsigned char zigel_index = calculate_zigel_index(zextData->value, zextData->length, i);
        const int data_index = calculate_zigel_data_index(zextData->value, zextData->length, i);
        set_zigel_position(world, zextData, e, data_index, data->element.size.y, data->zext.text_alignment, data->zext.text_padding, data->element.anchor, new_children_length, data->parent.position, data->parent.size, data->canvas.size);
        const unsigned char old_zigel_index = zox_get_value(e, ZigelIndex)
        // only if ZigelIndex has changed!
        if (old_zigel_index != zigel_index) {
#ifdef zoxel_debug_zigel_updates
            zox_log("    - zig updated [%i] [%i] -> [%i]\n", i, old_zigel_index, zigel_index)
#endif
            ZigelIndex *zigelIndex2 = zox_get_mut(e, ZigelIndex)
            GenerateTexture *generateTexture = zox_get_mut(e, GenerateTexture)
            zigelIndex2->value = zigel_index;
            generateTexture->value = zox_generate_texture_trigger;
            zox_modified(e, ZigelIndex)
            zox_modified(e, GenerateTexture)
        }
        new_children[i] = e;
    }
    // Spawn New Zigels
    if (new_children_length > old_children_length) {
#ifdef zoxel_debug_zext_updates
        zox_log("    - spawning new_children [%i]\n", new_children_length - old_children_length)
#endif
        for (int i = old_children_length; i < new_children_length; i++) {
            const unsigned char zigel_index = calculate_zigel_index(zextData->value, zextData->length, i);
            const int data_index = calculate_zigel_data_index(zextData->value, zextData->length, i);
            data->zigel.zigel_index = zigel_index;
            data->zigel.data_index = data_index;
            const ecs_entity_t zigel = spawn_zext_zigel(world, zextData, data);
            new_children[i] = zigel;
            zox_set(zigel, RenderDisabled, { data->element.render_disabled })
        }
    }
    // Delete Old Zigels
    else if (new_children_length < old_children_length) {
        for (int i = new_children_length; i < old_children_length; i++) zox_delete(old_children[i])
#ifdef zoxel_debug_zext_updates
        zox_log("    - deleted old_children [%i].\n", (old_children_length - new_children_length))
#endif
    }
    if (!has_old_children && new_children) total_memorys_allocated++;
    else if (has_old_children && !new_children) total_memorys_allocated--;
    if (has_old_children) free(old_children);
}

void set_entity_label_with_zext(ecs_world_t *world, const ecs_entity_t parent, unsigned char *value, int length) {
    const Children *name_label_children = zox_get(parent, Children)
    ecs_entity_t e = name_label_children->value[0];
    ZextData *zextData = zox_get_mut(e, ZextData)
    if (zextData->value) free(zextData->value);
    zextData->value = memcpy(malloc(length), value, length);
    zextData->length = length;
    zox_modified(e, ZextData)
    zox_set(e, ZextDirty, { zext_update_start })
    /*ZextDirty *zextDirty = zox_get_mut(zext_entity, ZextDirty)
    zextDirty->value = zext_update_start;
    zox_modified(zext_entity, ZextDirty)*/
}

unsigned char set_entity_with_text(ecs_world_t *world, const ecs_entity_t e, const char* text) {
    zox_get_muter(e, ZextData, zextData)
    if (is_zext(zextData, text)) return 0;
    set_zext(zextData, text);
    zox_modified(e, ZextData)
    zox_set(e, ZextDirty, { zext_update_start })
    return 1;
}

unsigned char set_entity_with_text_raw(ecs_world_t *world, const ecs_entity_t e, const char* text) {
    zox_get_muter(e, ZextData, zextData)
    set_zext(zextData, text);
    zox_set(e, ZextDirty, { zext_update_start })
    return 1;
}

unsigned char set_entity_label_with_text(ecs_world_t *world, const ecs_entity_t e, const char* text) {
    const Children *children = zox_get(e, Children)
    if (children->length == 0) return 0;
    return set_entity_with_text(world, children->value[0], text);
}

void set_new_zox_name(ecs_world_t *world, const ecs_entity_t e, const char* text) {
    zox_set_zext_component(e, ZoxName, text)
}


int get_zexts_count(ecs_world_t *world) {
    return zox_count_entities(world, ecs_id(Zext));
}
