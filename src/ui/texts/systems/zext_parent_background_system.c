void ZextParentBackgroundSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(ZextDirty, zextDirtys, 2)
    zox_field_in(TextData, textDatas, 3)
    zox_field_in(TextSize, textSizes, 4)
    zox_field_in(TextPadding, textPaddings, 5)
    zox_field_in(MeshAlignment, meshAlignments, 6)
    zox_field_in(ParentLink, parentLinks, 8)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ZextDirty, zextDirtys, zextDirty)
        if (zextDirty->value != zext_update_update) continue;
        zox_field_i(ParentLink, parentLinks, parentLink)
        const ecs_entity_t e2 = parentLink->value;
        if (!zox_has(e2, ZextLabel)) continue;
        // const byte mesh_dirty = zox_get_value(e2, MeshDirty)
        // if (mesh_dirty) return;
        const byte generate_texture = zox_get_value(e2, GenerateTexture)
        if (generate_texture) return;
        zox_field_i(TextData, textDatas, textData)
        zox_field_i(TextSize, textSizes, textSize)
        zox_field_i(TextPadding, textPaddings, textPadding)
        zox_field_i(MeshAlignment, meshAlignments, meshAlignment)
        const int2 size = calculate_zext_size(textData->value, textData->length, textSize->value, textPadding->value, default_line_padding);
        on_element_pixels_resized(world, e2, size, meshAlignment->value);
    }
} zox_declare_system(ZextParentBackgroundSystem)
