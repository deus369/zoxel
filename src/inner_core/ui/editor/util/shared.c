void set_entity_label_with_zext(ecs_world_t *world, ecs_entity_t e, unsigned char *value, int length) {
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

void set_entity_label_with_text(ecs_world_t *world, ecs_entity_t e, const char* text) {
    const Children *name_label_children = zox_get(e, Children)
    ecs_entity_t zext_entity = name_label_children->value[0];
    ZextData *zextData = zox_get_mut(zext_entity, ZextData)
    if (is_zext(zextData, text)) return;
    set_zext(zextData, text);
    zox_modified(zext_entity, ZextData)
    // zox_set(zext_entity, ZextDirty, { 1 })
    ZextDirty *zextDirty = zox_get_mut(zext_entity, ZextDirty)
    zextDirty->value = 1;
    zox_modified(zext_entity, ZextDirty)
}
