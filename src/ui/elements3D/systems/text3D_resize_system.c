void resize_text3D(ecs_world_t *world, Children *children, const TextData *textData) {
    if (children->length == textData->length) {
        // no need to resize / reposition text
        return;
    }
    const int old_children_length = children->length;
    const int new_children_length = calculate_total_zigels(textData->value, textData->length);
    const int has_old_children = old_children_length > 0;
    const int reuse_count = integer_min(old_children_length, new_children_length);
    ecs_entity_t *old_children = children->value;
    ecs_entity_t *new_children = NULL;
    if (new_children_length > 0) {
        new_children = malloc(new_children_length * sizeof(ecs_entity_t));
    }
    children->value = new_children;
    children->length = new_children_length;
    // Here, reposition old text
    for (int i = 0; i < reuse_count; i++) {
        const ecs_entity_t e = old_children[i];
        /*const byte zigel_index = calculate_zigel_index(textData->value, textData->length, i);
         *        const int data_index = calculate_zigel_data_index(textData->value, textData->length, i);
         *        const byte old_zigel_index = zox_get_value(e, ZigelIndex)
         *        // only if ZigelIndex has changed!
         *        if (old_zigel_index != zigel_index) {
         *            zox_get_muter(e, ZigelIndex, zigelIndex2)
         *            zox_get_muter(e, GenerateTexture, generateTexture)
         *            zigelIndex2->value = zigel_index;
         *            generateTexture->value = zox_generate_texture_trigger;
         *            zox_log_text3D("    + zigel [%i] updated [%i:%i]", i, old_zigel_index, zigel_index)
    }
    new_children[i] = e;*/
        // if size of text changes, set position differently
        // set_zigel_position(world, textData, e, data_index, data->element.size.y, data->zext.text_alignment, data->zext.text_padding, data->element.anchor, new_children_length, data->parent.position, data->parent.size, data->canvas.size);
    }
    // Spawn New Zigels
    /*if (new_children_length > old_children_length) {
     *        for (int i = old_children_length; i < new_children_length; i++) {
     *            const byte zigel_index = calculate_zigel_index(textData->value, textData->length, i);
     *            const int data_index = calculate_zigel_data_index(textData->value, textData->length, i);
     *            data->zigel.zigel_index = zigel_index;
     *            data->zigel.data_index = data_index;
     *            const ecs_entity_t zigel = spawn_zext_zigel(world, textData, data);
     *            zox_set(zigel, RenderDisabled, { data->element.render_disabled })
     *            new_children[i] = zigel;
}
}
// Delete Old Zigels
else if (new_children_length < old_children_length) {
    for (int i = new_children_length; i < old_children_length; i++) {
        zox_delete(old_children[i])
}
}*/
    if (!has_old_children && new_children) {
        total_memorys_allocated++;
    } else if (has_old_children && !new_children) {
        total_memorys_allocated--;
    }
    if (has_old_children) {
        free(old_children);
    }
}

// todo: split up into update system, and resize system
// note: update system can be generically for 2D and 3D text
void Text3DResizeSystem(ecs_iter_t *it) {
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
        zox_field_i(TextData, textDatas, textData)
        zox_field_o(Children, childrens, children)
        const int new_children_length = calculate_total_zigels(textData->value, textData->length);
        if (children->length == new_children_length) {
            continue;
        }
        char *debug_text = convert_zext_to_text(textData->value, textData->length);
        if (debug_text) {
            zox_log_text3D("+ resizing text3D [%s] [%i:%i]", debug_text, children->length, new_children_length)
            free(debug_text);
        } else {
            zox_log_text3D("+ resizing text3D [null]")
        }

        /*zox_field_e()
        zox_field_i(TextSize, textSizes, textSize)
        zox_field_i(TextPadding, textPaddings, textPadding)
        zox_field_i(Layer2D, layer2Ds, layer2D)
        zox_field_i(CanvasPosition, canvasPositions, canvasPosition)
        zox_field_i(PixelSize, pixelSizes, pixelSize)
        zox_field_i(MeshAlignment, meshAlignments, meshAlignment)
        zox_field_i(FontOutlineColor, fontOutlineColors, fontOutlineColor)
        zox_field_i(FontFillColor, fontFillColors, fontFillColor)
        zox_field_i(FontThickness, fontThicknesss, fontThickness)
        zox_field_o(RenderDisabled, renderDisableds, renderDisabled)
        resize_text3D(world, children, textData);*/
    }
} zox_declare_system(Text3DResizeSystem)
