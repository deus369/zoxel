//! When ui text updates, spawn/destroy font entities
void ZextUpdateSystem(ecs_iter_t *it) {
    // zox_change_check()
    zox_field_world()
    zox_field_in(ZextData, zextDatas, 1)
    zox_field_in(ZextSize, zextSizes, 2)
    zox_field_in(ZextPadding, zextPaddings, 3)
    zox_field_in(Layer2D, layer2Ds, 4)
    zox_field_in(CanvasPosition, canvasPositions, 5)
    zox_field_in(PixelSize, pixelSizes, 6)
    zox_field_in(MeshAlignment, meshAlignments, 7)
    zox_field_in(FontOutlineColor, fontOutlineColors, 8)
    zox_field_in(FontFillColor, fontFillColors, 9)
    zox_field_in(FontThickness, fontThicknesss, 10)
    zox_field_in(ZextDirty, zextDirtys, 11)
    zox_field_out(RenderDisabled, renderDisableds, 12)
    zox_field_out(Children, childrens, 13)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ZextDirty, zextDirtys, zextDirty)
        if (zextDirty->value != zext_update_update) continue;
        zox_field_i(ZextData, zextDatas, zextData)
        zox_field_o(Children, childrens, children)
        // if (is_zext_updating(world, children)) continue;
        zox_field_e()
        zox_field_i(ZextSize, zextSizes, zextSize)
        zox_field_i(ZextPadding, zextPaddings, zextPadding)
        zox_field_i(Layer2D, layer2Ds, layer2D)
        zox_field_i(CanvasPosition, canvasPositions, canvasPosition)
        zox_field_i(PixelSize, pixelSizes, pixelSize)
        zox_field_i(MeshAlignment, meshAlignments, meshAlignment)
        zox_field_i(FontOutlineColor, fontOutlineColors, fontOutlineColor)
        zox_field_i(FontFillColor, fontFillColors, fontFillColor)
        zox_field_i(FontThickness, fontThicknesss, fontThickness)
        zox_field_o(RenderDisabled, renderDisableds, renderDisabled)
        const ecs_entity_t canvas = get_root_canvas(world, e);
        const int2 canvas_size = zox_get_value(canvas, PixelSize)
        const byte zext_length = calculate_total_zigels(zextData->value, zextData->length);
        if (zox_has(e, ZextRenderEnabler)) renderDisabled->value = zextData->length == 0;
        // set parent to or refactor debug ui?
        SpawnZigel spawn_data = {
            .canvas = {
                .e = canvas,
                .size = canvas_size
            },
            .parent = {
                .e = e,
                .position = canvasPosition->value,
                .size = pixelSize->value
            },
            .element = {
                .layer = layer2D->value + 1,
                .size = int2_single(zextSize->value), // (int2) { zextSize->value, zextSize->value },
                .anchor = float2_half,
                .render_disabled = renderDisabled->value
            },
            .zext = {
                .font_thickness = fontThickness->value,
                .length = zext_length,
                .text_padding = zextPadding->value,
                .text_alignment = meshAlignment->value,
            },
            .zigel = {
                .outline_color = fontOutlineColor->value,
                .fill_color = fontFillColor->value
            }
        };
        spawn_zext_zigels(world, &spawn_data, children, zextData);
    }
} zox_declare_system(ZextUpdateSystem)
