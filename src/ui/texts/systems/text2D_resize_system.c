//! Dynamically updates zext by spawning/destroying zigels and updating remaining
// #define zoxel_debug_zext_updates

void spawn_text2D_zigels(ecs_world_t *world, SpawnZigel *data, Children *children, const TextData *textData) {
    const int old_children_length = children->length;
    const int new_children_length = calculate_total_zigels(textData->value, textData->length);
    const int has_old_children = old_children_length > 0;
    const int reuse_count = int_min(old_children_length, new_children_length);
#ifdef zoxel_debug_zext_updates
    zox_log("spawn_zext_zigels :: [%i] -> [%i]; reuse [%i];", children->length, textData->length, reuse_count)
    if (children->length == textData->length) {
        zox_log("    - zext remained the same [%i]", textData->length)
    }
#endif
    ecs_entity_t *old_children = children->value;
    ecs_entity_t *new_children = NULL;
    if (new_children_length > 0) {
        new_children = malloc(new_children_length * sizeof(ecs_entity_t));
    }
    children->value = new_children;
    children->length = new_children_length;
    // old children needs new
    //  - set old positions, as we are resizing
    for (int i = 0; i < reuse_count; i++) {
        const ecs_entity_t e = old_children[i];
        const int data_index = calculate_zigel_data_index(textData->value, textData->length, i);
        set_zigel_position(world, textData, e, data_index, data->element.size.y, data->zext.text_alignment, data->zext.text_padding, data->element.anchor, new_children_length, data->parent.position, data->parent.size, data->canvas.size);
        new_children[i] = e;
    }
    // Spawn New Zigels
    if (new_children_length > old_children_length) {
#ifdef zoxel_debug_zext_updates
        zox_log("    - spawning new_children [%i]", new_children_length - old_children_length)
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
        zox_log("    - deleted old_children [%i]", (old_children_length - new_children_length))
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
void Text2DResizeSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(TextData)
    zox_sys_in(TextSize)
    zox_sys_in(TextPadding)
    zox_sys_in(Layer2D)
    zox_sys_in(CanvasPosition)
    zox_sys_in(PixelSize)
    zox_sys_in(MeshAlignment)
    zox_sys_in(FontOutlineColor)
    zox_sys_in(FontFillColor)
    zox_sys_in(FontThickness)
    zox_sys_in(FontOutlineThickness)
    zox_sys_in(TextResolution)
    zox_sys_in(ZextDirty)
    zox_sys_out(RenderDisabled)
    zox_sys_out(Children)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(ZextDirty, zextDirty)
        zox_sys_i(TextData, textData)
        zox_sys_i(TextSize, textSize)
        zox_sys_i(TextPadding, textPadding)
        zox_sys_i(Layer2D, layer2D)
        zox_sys_i(CanvasPosition, canvasPosition)
        zox_sys_i(PixelSize, pixelSize)
        zox_sys_i(MeshAlignment, meshAlignment)
        zox_sys_i(FontOutlineColor, fontOutlineColor)
        zox_sys_i(FontFillColor, fontFillColor)
        zox_sys_i(FontThickness, fontThickness)
        zox_sys_i(FontOutlineThickness, fontOutlineThickness)
        zox_sys_i(TextResolution, textResolution)
        zox_sys_o(Children, children)
        zox_sys_o(RenderDisabled, renderDisabled)
        if (zextDirty->value != zext_update_update) {
            continue;
        }
        const ecs_entity_t canvas = get_root_canvas(world, e);
        if (!zox_valid(canvas)) {
            zox_log_error("no canvas found on text")
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
                .anchor = float2_half,
                .render_disabled = renderDisabled->value,
                .size = int2_single(textSize->value),
                .texture_size = int2_single(textResolution->value),
            },
            .zext = {
                .font_thickness = fontThickness->value,
                .font_outline_thickness = fontOutlineThickness->value,
                .length = zext_length,
                .text_padding = textPadding->value,
                .text_alignment = meshAlignment->value,
            },
            .zigel = {
                .outline_color = fontOutlineColor->value,
                .fill_color = fontFillColor->value
            }
        };
        spawn_text2D_zigels(world, &spawn_data, children, textData);
        // zox_log("+ resizing text [%s]", zox_get_name(e))
    }
} zox_declare_system(Text2DResizeSystem)