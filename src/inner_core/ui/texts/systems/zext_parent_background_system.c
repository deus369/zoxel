void ZextParentBackgroundSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(ZextDirty, zextDirtys, 2)
    zox_field_in(ZextData, zextDatas, 3)
    zox_field_in(ZextSize, zextSizes, 4)
    zox_field_in(ZextPadding, zextPaddings, 5)
    zox_field_in(MeshAlignment, meshAlignments, 6)
    zox_field_in(ParentLink, parentLinks, 8)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ZextDirty, zextDirtys, zextDirty)
        if (!zextDirty->value) continue;
        zox_field_i(ParentLink, parentLinks, parentLink)
        const ecs_entity_t e2 = parentLink->value;
        if (!zox_has(e2, ZextLabel)) continue;
        const unsigned char mesh_dirty = zox_get_value(e2, MeshDirty)
        if (mesh_dirty) return;
        const unsigned char generate_texture = zox_get_value(e2, GenerateTexture)
        if (generate_texture) return;
        zox_field_i(ZextData, zextDatas, zextData)
        zox_field_i(ZextSize, zextSizes, zextSize)
        zox_field_i(ZextPadding, zextPaddings, zextPadding)
        zox_field_i(MeshAlignment, meshAlignments, meshAlignment)
        const int2 size = calculate_zext_size(zextData->value, zextData->length, zextSize->value, zextPadding->value, default_line_padding);
        on_element_pixels_resized(world, e2, size, meshAlignment->value);
    }
} zox_declare_system(ZextParentBackgroundSystem)
