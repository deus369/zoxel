void resize_text3D(ecs_world_t *world, Children *children, const TextData *textData, Zigel3DData zigel_data) {
    // no need to resize / reposition text if same size
    if (children->length == textData->length) {
        return;
    }
    ecs_entity_t *old_children = children->value;
    const int old_children_length = children->length;
    const int has_old_children = old_children_length > 0;
    const int new_children_length = calculate_total_zigels(textData->value, textData->length);
    const int reuse_count = int_min(old_children_length, new_children_length);
    ecs_entity_t *new_children = NULL;
    if (new_children_length > 0) {
        new_children = malloc(new_children_length * sizeof(ecs_entity_t));
    }
    if (new_children_length > old_children_length) {    // spawn new zigels
        for (int i = old_children_length; i < new_children_length; i++) {
            const int data_index = calculate_zigel_data_index(textData->value, textData->length, i);
            const byte zigel_index = calculate_zigel_index(textData->value, textData->length, i);
            zigel_data.zigel_index = zigel_index;
            zigel_data.position = calculate_zigel3D_position(zigel3D_size, data_index, new_children_length, zigel_data.scale);
            const ecs_entity_t e = spawn_zigel3(world, zigel_data);
            new_children[i] = e;
            zox_log_text3D("    + spawned [%i] zigel [%s]", i, zox_get_name(e))
        }
    } else if (new_children_length < old_children_length) { // remove old zigels
        for (int i = new_children_length; i < old_children_length; i++) {
            const ecs_entity_t e = old_children[i];
            zox_log_text3D("    - deleting [%i] zigel [%s]", i, zox_get_name(e))
            zox_delete(e)
        }
    }
    for (int i = 0; i < reuse_count; i++) {     // Reposition old zigels!
        const int data_index = calculate_zigel_data_index(textData->value, textData->length, i);
        const float3 zigel_position = calculate_zigel3D_position(zigel3D_size, data_index, new_children_length, zigel_data.scale);
        const ecs_entity_t e = old_children[i];
        zox_set(e, LocalPosition3D, { zigel_position })
        new_children[i] = e;
        zox_log_text3D("    > reusing [%i] zigel [%s]", i, zox_get_name(e))
    }
    children->value = new_children;
    children->length = new_children_length;
    if (has_old_children) {
        free(old_children);
    }
    if (!has_old_children && new_children) {    // stats
        total_memorys_allocated++;
    } else if (has_old_children && !new_children) {
        total_memorys_allocated--;
    }
}

// todo: split up into update system, and resize system
// note: update system can be generically for 2D and 3D text
void Text3DResizeSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(TextData)
    zox_sys_in(FontOutlineColor)
    zox_sys_in(FontFillColor)
    zox_sys_in(FontThickness)
    zox_sys_in(ZextDirty)
    zox_sys_in(RenderDisabled)
    zox_sys_in(Text3DScale)
    zox_sys_in(TextSize)
    zox_sys_out(Children)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(ZextDirty, zextDirty)
        zox_sys_i(FontThickness, fontThickness)
        zox_sys_i(FontFillColor, fontFillColor)
        zox_sys_i(FontOutlineColor, fontOutlineColor)
        zox_sys_i(RenderDisabled, renderDisabled)
        zox_sys_i(Text3DScale, text3DScale)
        zox_sys_i(TextSize, textSize)
        zox_sys_i(TextData, textData)
        zox_sys_o(Children, children)
        if (zextDirty->value != zext_update_update) {
            continue;
        }
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
        Zigel3DData zigel_data = {
            .prefab = prefab_zigel3D,
            .resolution = textSize->value, // 128,
        };
        zigel_data.parent = e;
        zigel_data.font_thickness = fontThickness->value;
        zigel_data.fill_color = fontFillColor->value;
        zigel_data.outline_color = fontOutlineColor->value;
        zigel_data.render_disabled = renderDisabled->value;
        zigel_data.scale = text3DScale->value;
        resize_text3D(world, children, textData, zigel_data);
    }
} zox_declare_system(Text3DResizeSystem)