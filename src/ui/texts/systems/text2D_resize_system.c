//! Dynamically updates zext by spawning/destroying zigels and updating remaining
void spawn_zext_zigels(ecs_world_t *world, SpawnZigel *data, Children *children, const TextData *textData) {
    const int old_children_length = children->length;
    const int new_children_length = calculate_total_zigels(textData->value, textData->length);
    const int has_old_children = old_children_length > 0;
    const int reuse_count = integer_min(old_children_length, new_children_length);
    #ifdef zoxel_debug_zext_updates
        zox_log("spawn_zext_zigels :: [%i] -> [%i]; reuse [%i];\n", children->length, textData->length, reuse_count)
    #endif
    #ifdef zoxel_debug_zext_updates
    if (children->length == textData->length) {
        zox_log("    - zext remained the same [%i]\n", textData->length)
    }
    #endif
    ecs_entity_t *old_children = children->value;
    ecs_entity_t *new_children = NULL;
    if (new_children_length > 0) {
        new_children = malloc(new_children_length * sizeof(ecs_entity_t));
    }
    children->value = new_children;
    children->length = new_children_length;
    // Set Data for Old Zigels
    for (int i = 0; i < reuse_count; i++) {
        const ecs_entity_t e = old_children[i];
        const byte zigel_index = calculate_zigel_index(textData->value, textData->length, i);
        const int data_index = calculate_zigel_data_index(textData->value, textData->length, i);
        set_zigel_position(world, textData, e, data_index, data->element.size.y, data->zext.text_alignment, data->zext.text_padding, data->element.anchor, new_children_length, data->parent.position, data->parent.size, data->canvas.size);
        new_children[i] = e;

        /*const byte old_zigel_index = zox_get_value(e, ZigelIndex)
        // only if ZigelIndex has changed!
        if (old_zigel_index != zigel_index) {
            #ifdef zoxel_debug_zigel_updates
                zox_log("    - zig updated [%i] [%i] -> [%i]\n", i, old_zigel_index, zigel_index)
            #endif
            zox_get_muter(e, ZigelIndex, zigelIndex2)
            zox_get_muter(e, GenerateTexture, generateTexture)
            zigelIndex2->value = zigel_index;
            generateTexture->value = zox_generate_texture_trigger;
        }*/
    }
    // Spawn New Zigels
    if (new_children_length > old_children_length) {
        #ifdef zoxel_debug_zext_updates
            zox_log("    - spawning new_children [%i]\n", new_children_length - old_children_length)
        #endif
        for (int i = old_children_length; i < new_children_length; i++) {
            const byte zigel_index = calculate_zigel_index(textData->value, textData->length, i);
            const int data_index = calculate_zigel_data_index(textData->value, textData->length, i);
            data->zigel.zigel_index = zigel_index;
            data->zigel.data_index = data_index;
            const ecs_entity_t zigel = spawn_zext_zigel(world, textData, data);
            zox_set(zigel, RenderDisabled, { data->element.render_disabled })
            new_children[i] = zigel;
        }
    }
    // Delete Old Zigels
    else if (new_children_length < old_children_length) {
        for (int i = new_children_length; i < old_children_length; i++) {
            zox_delete(old_children[i])
        }
        #ifdef zoxel_debug_zext_updates
            zox_log("    - deleted old_children [%i].\n", (old_children_length - new_children_length))
        #endif
    }
    if (!has_old_children && new_children) {
        total_memorys_allocated++;
    } else if (has_old_children && !new_children) {
        total_memorys_allocated--;
    }
    if (has_old_children) {
        free(old_children);
    }
}

//! When ui text updates, spawn/destroy font entities
void ZextUpdateSystem(ecs_iter_t *it) {
    // zox_change_check()
    zox_field_world()
    zox_field_in(TextData, textDatas, 1)
    zox_field_in(TextSize, textSizes, 2)
    zox_field_in(TextPadding, textPaddings, 3)
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
        if (zextDirty->value != zext_update_update) {
            continue;
        }
        zox_field_e()
        zox_field_i(TextData, textDatas, textData)
        zox_field_i(TextSize, textSizes, textSize)
        zox_field_i(TextPadding, textPaddings, textPadding)
        zox_field_i(Layer2D, layer2Ds, layer2D)
        zox_field_i(CanvasPosition, canvasPositions, canvasPosition)
        zox_field_i(PixelSize, pixelSizes, pixelSize)
        zox_field_i(MeshAlignment, meshAlignments, meshAlignment)
        zox_field_i(FontOutlineColor, fontOutlineColors, fontOutlineColor)
        zox_field_i(FontFillColor, fontFillColors, fontFillColor)
        zox_field_i(FontThickness, fontThicknesss, fontThickness)
        zox_field_o(Children, childrens, children)
        zox_field_o(RenderDisabled, renderDisableds, renderDisabled)
        const ecs_entity_t canvas = get_root_canvas(world, e);
        if (!canvas) {
            zox_log("! no canvas found on text\n")
            continue;
        }
        const int2 canvas_size = zox_get_value(canvas, PixelSize)
        const byte zext_length = calculate_total_zigels(textData->value, textData->length);
        if (zox_has(e, ZextRenderEnabler)) {
            renderDisabled->value = textData->length == 0;
        }
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
                .size = int2_single(textSize->value),
                .anchor = float2_half,
                .render_disabled = renderDisabled->value
            },
            .zext = {
                .font_thickness = fontThickness->value,
                .length = zext_length,
                .text_padding = textPadding->value,
                .text_alignment = meshAlignment->value,
            },
            .zigel = {
                .outline_color = fontOutlineColor->value,
                .fill_color = fontFillColor->value
            }
        };
        spawn_zext_zigels(world, &spawn_data, children, textData);
    }
} zox_declare_system(ZextUpdateSystem)
