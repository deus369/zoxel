//! When ui text updates, spawn/destroy font entities
void ZextUpdateSystem(ecs_iter_t *it) {
    zox_change_check()
    zox_iter_world()
    zox_field_in(ZextData, zextDatas, 1)
    zox_field_in(ZextSize, zextSizes, 2)
    zox_field_in(ZextPadding, zextPaddings, 3)
    zox_field_in(Layer2D, layer2Ds, 4)
    zox_field_in(CanvasPosition, canvasPositions, 5)
    zox_field_in(PixelSize, pixelSizes, 6)
    zox_field_in(MeshAlignment, meshAlignments, 7)
    zox_field_in(RenderDisabled, renderDisableds, 8)
    zox_field_in(FontOutlineColor, fontOutlineColors, 9)
    zox_field_in(FontFillColor, fontFillColors, 10)
    zox_field_out(ZextDirty, zextDirtys, 11)
    zox_field_out(Children, childrens, 12)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(ZextDirty, zextDirtys, zextDirty)
        if (!zextDirty->value) continue;
        zox_field_i_in(ZextData, zextDatas, zextData)
        zox_field_i_out(Children, childrens, children)
        if (is_zext_updating(world, children)) continue;
        zox_field_e()
        zox_field_i_in(ZextSize, zextSizes, zextSize)
        zox_field_i_in(ZextPadding, zextPaddings, zextPadding)
        zox_field_i_in(Layer2D, layer2Ds, layer2D)
        zox_field_i_in(CanvasPosition, canvasPositions, canvasPosition)
        zox_field_i_in(PixelSize, pixelSizes, pixelSize)
        zox_field_i_in(MeshAlignment, meshAlignments, meshAlignment)
        zox_field_i_in(RenderDisabled, renderDisableds, renderDisabled)
        zox_field_i_in(FontOutlineColor, fontOutlineColors, fontOutlineColor)
        zox_field_i_in(FontFillColor, fontFillColors, fontFillColor)
        const ecs_entity_t canvas = get_root_canvas(world, e);
        const int2 canvas_size = zox_get_value(canvas, PixelSize)
        const unsigned char zext_length = calculate_total_zigels(zextData->value, zextData->length);
        ZigelSpawnData spawn_data = {
            .canvas = { .e = canvas, .size = canvas_size },
            .parent = { .e = e, .position = canvasPosition->value, .size = pixelSize->value },
            .zext = { .length = zext_length, .text_padding = zextPadding->value, .text_alignment = meshAlignment->value },
            .element = { .layer = layer2D->value + 1, .size = (int2) { zextSize->value, zextSize->value }, .anchor = float2_half, .render_disabled = renderDisabled->value },
            .outline_color = fontOutlineColor->value,
            .fill_color = fontFillColor->value,
        };
        spawn_zext_zigels(world, &spawn_data, children, zextData);
        zextDirty->value = 0;
#ifdef zoxel_debug_zigel_updates
        zox_log(" > zext is updating [%lu] [%i]\n", it->entities[i], zextData->length)
#endif
    }
} zox_declare_system(ZextUpdateSystem)
