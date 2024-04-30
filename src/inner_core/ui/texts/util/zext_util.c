// #define zoxel_debug_zext_updates

void set_zox_name(ZoxName *zoxName, const char* text) {
    unsigned char text_length = strlen(text);
    if (zoxName->length != text_length) resize_memory_component(ZoxName, zoxName, unsigned char, text_length)
    for (unsigned char i = 0; i < text_length; i++) zoxName->value[i] = convert_ascii(text[i]);
}

char* get_zext_text(const ZextData *zextData) {
    return convert_zext_to_text(zextData->value, zextData->length);
    /*char* text = malloc(zextData->length);
    for (unsigned char i = 0; i < zextData->length; i++) text[i] = convert_to_ascii(zextData->value[i]);
    return text;*/
}

unsigned char is_zext(ZextData *zextData, const char* text) {
    unsigned char text_length = strlen(text);
    if (zextData->length != text_length) return 0;
    for (int i = 0; i < text_length; i++) if (convert_ascii(text[i]) != zextData->value[i]) return 0;
    return 1;
}

void set_zext(ZextData *zextData, const char* text) {
    unsigned char text_length = strlen(text);
    // zox_log("   - set zext [%i]\n", text_length)
    if (zextData->length != text_length) resize_memory_component(ZextData, zextData, unsigned char, text_length)
    for (unsigned char i = 0; i < text_length; i++) zextData->value[i] = convert_ascii(text[i]);
}

void print_entity_zext(ecs_world_t *world, const ecs_entity_t e) {
    if (!zox_has(e, ZextData)) return;
    const ZextData *zextData = zox_get(e, ZextData)
    char *text = get_zext_text(zextData);
    zox_log("   > zext %lu [%s] length %i\n", e, text, zextData->length)
    free(text);
}

unsigned char is_zext_updating(ecs_world_t *world, const Children *children) {
    for (unsigned char i = 0; i < children->length; i++) { // update the reused ones
        ecs_entity_t zigel = children->value[i];
        const unsigned char generate_texture = zox_get_value(zigel, GenerateTexture)
        if (generate_texture) return 1;
    }
    return 0;
}

//! Dynamically updates zext by spawning/destroying zigels and updating remaining
void spawn_zext_zigels(ecs_world_t *world, const ecs_entity_t zext, const ecs_entity_t canvas, Children *children, const ZextData *zextData, const int font_size, const unsigned char text_alignment, const byte2 text_padding, const unsigned char zext_layer, int2 parent_position, int2 parent_pixel_size, unsigned char render_disabled) {
    const float2 anchor = float2_half; // (float2) { 0.5f, 0.5f };
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    unsigned char old_children_length = children->length;
    unsigned char new_children_length = zextData->length;
    unsigned char has_old_children = old_children_length > 0;
    int reuse_count = integer_min(old_children_length, new_children_length);
    unsigned char zigel_layer = zext_layer + 1;
#ifdef zoxel_debug_zext_updates
    zox_log("spawn_zext_zigels :: [%i] -> [%i]; reuse [%i];\n", children->length, zextData->length, reuse_count)
#endif
    // re set all old zigels, if index changes, regenerate font textureData
    for (unsigned char i = 0; i < reuse_count; i++) { // update the reused ones
        ecs_entity_t old_zigel = children->value[i];
        const ZigelIndex *zigelIndex = zox_get(old_zigel, ZigelIndex)
        if (zigelIndex->value != zextData->value[i]) {
#ifdef zoxel_debug_zigel_updates
            zox_log("    - zig updated [%i] [%i] -> [%i]\n", i, zigelIndex->value, zextData->value[i])
#endif
            ZigelIndex *zigelIndex2 = zox_get_mut(old_zigel, ZigelIndex)
            GenerateTexture *generateTexture = zox_get_mut(old_zigel, GenerateTexture)
            zigelIndex2->value = zextData->value[i];
            generateTexture->value = 1;
            zox_modified(old_zigel, ZigelIndex)
            zox_modified(old_zigel, GenerateTexture)
        }
    }
#ifdef zoxel_debug_zext_updates
    if (children->length == zextData->length) zox_log("    - zext remained the same [%i]\n", zextData->length)
#endif
    if (children->length == zextData->length) return;
    int reusing_length = int_min(old_children_length, new_children_length);
    ecs_entity_t *old_children = children->value;
    ecs_entity_t *new_children = NULL;
    if (new_children_length > 0) new_children = malloc(new_children_length * sizeof(ecs_entity_t));
    for (unsigned char i = 0; i < reusing_length; i++) {
        ecs_entity_t old_zigel = old_children[i];
        new_children[i] = old_zigel;
        set_zigel_position(world, old_zigel, i, font_size, text_alignment, text_padding, anchor, new_children_length, parent_position, parent_pixel_size, canvas_size);
    }
    if (new_children_length > old_children_length) {
#ifdef zoxel_debug_zext_updates
        zox_log("    - spawning new_children [%i]\n", new_children_length - old_children_length)
#endif
        for (unsigned char i = old_children_length; i < new_children_length; i++) {
            unsigned char zigel_type = zextData->value[i];
            ecs_entity_t zigel = spawn_zext_zigel(world, zext, canvas, zigel_layer, i, new_children_length, zigel_type, font_size, text_alignment, text_padding, parent_position, parent_pixel_size, canvas_size);
            new_children[i] = zigel;
            zox_set(zigel, RenderDisabled, { render_disabled })
        }
    } else if (new_children_length < old_children_length) {
#ifdef zoxel_debug_zext_updates
        zoxel_log("    - deleting old_children [%i].\n", (old_children_length - new_children_length));
#endif
        for (int i = new_children_length; i < old_children_length; i++) zox_delete(old_children[i])
    }
    if (!has_old_children && new_children) total_memorys_allocated++;
    else if (has_old_children && !new_children) total_memorys_allocated--;
    if (has_old_children) free(old_children);
    children->value = new_children;
    children->length = new_children_length;
    // zox_log("   > has_old_children [%i]\n", has_old_children)
    // zox_log("   > children [%i]\n", new_children_length)
    // zox_log("   > new_children_length [%i] reusing_length [%i] old_children_length [%i]\n", new_children_length, reusing_length, old_children_length)
    // zox_log("   > finished [%i]\n", children->length)
}
void set_entity_label_with_zext(ecs_world_t *world, const ecs_entity_t e, unsigned char *value, int length) {
    const Children *name_label_children = zox_get(e, Children)
    ecs_entity_t zext_entity = name_label_children->value[0];
    ZextData *zextData = zox_get_mut(zext_entity, ZextData)
    if (zextData->value) free(zextData->value);
    zextData->value = memcpy(malloc(length), value, length);
    zextData->length = length;
    zox_modified(zext_entity, ZextData)
    // zox_set(zext_entity, ZextDirty, { 1 })
    ZextDirty *zextDirty = zox_get_mut(zext_entity, ZextDirty)
    zextDirty->value = 1;
    zox_modified(zext_entity, ZextDirty)
}

unsigned char set_entity_label_with_text(ecs_world_t *world, const ecs_entity_t e, const char* text) {
    const Children *name_label_children = zox_get(e, Children)
    const ecs_entity_t zext_entity = name_label_children->value[0];
    ZextDirty *zextDirty = zox_get_mut(zext_entity, ZextDirty)
    if (zextDirty->value) return 0;
    ZextData *zextData = zox_get_mut(zext_entity, ZextData)
    if (is_zext(zextData, text)) return 0;
    set_zext(zextData, text);
    zextDirty->value = 1;
    zox_modified(zext_entity, ZextData)
    zox_modified(zext_entity, ZextDirty)
    return 1;
}

unsigned char set_entity_with_text(ecs_world_t *world, const ecs_entity_t e, const char* text) {
    ZextDirty *zextDirty = zox_get_mut(e, ZextDirty)
    if (zextDirty->value) return 0;
    ZextData *zextData = zox_get_mut(e, ZextData)
    if (is_zext(zextData, text)) return 0;
    set_zext(zextData, text);
    zextDirty->value = 1;
    zox_modified(e, ZextData)
    zox_modified(e, ZextDirty)
    return 1;
}


void set_new_zox_name(ecs_world_t *world, const ecs_entity_t e, const char* text) {
    zox_set(e, ZoxName, { strlen(text), convert_string_to_zext(text) })
    /*if (!zox_has(e, ZextData)) zox_set(e, ZextData, { 0, NULL })
    ZextData *zextData = zox_get_mut(e, ZextData)
    if (is_zext(zextData, text)) return 0;
    set_zext(zextData, text);
    zox_modified(e, ZextData)
    return 1;*/
}
