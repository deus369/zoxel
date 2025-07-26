void ZextParentBackgroundSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(ZextDirty)
    zox_sys_in(TextData)
    zox_sys_in(TextSize)
    zox_sys_in(TextPadding)
    zox_sys_in(MeshAlignment)
    zox_sys_in(ParentLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ZextDirty, zextDirty)
        zox_sys_i(ParentLink, parentLink)
        zox_sys_i(TextData, textData)
        zox_sys_i(TextSize, textSize)
        zox_sys_i(TextPadding, textPadding)
        zox_sys_i(MeshAlignment, meshAlignment)
        if (zextDirty->value != zext_update_update) {
            continue;
        }
        const ecs_entity_t e2 = parentLink->value;
        if (!zox_has(e2, ZextLabel)) {
            continue;
        }
        const byte generate_texture = zox_get_value(e2, GenerateTexture)
        if (generate_texture) {
            return;
        }
        const int2 size = calculate_zext_size(textData->value, textData->length, textSize->value, textPadding->value, default_line_padding);
        on_element_pixels_resized(world, e2, size, meshAlignment->value);
    }
} zox_declare_system(ZextParentBackgroundSystem)
