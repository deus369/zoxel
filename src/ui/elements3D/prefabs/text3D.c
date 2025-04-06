typedef struct {
    ecs_entity_t prefab;
    ecs_entity_t parent;
    ecs_entity_t prefab_zigel;
    const char* text;
    float3 position;
    byte font_size;         // zigel_size
    byte font_thickness;    // zigel_size
    byte alignment;         // mesh_alignment
    byte2 padding;          // around zigels
    color fill_color;
    color outline_color;
    byte render_disabled;
} Text3DData;

ecs_entity_t spawn_prefab_text3D(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_text3D")
    zox_add_tag(e, Zext)
    zox_add_tag(e, Text3D)
    zox_prefab_set(e, TextSize, { 0 })
    zox_prefab_set(e, TextPadding, { byte2_zero })
    zox_prefab_set(e, ZextDirty, { 0 })
    zox_prefab_set(e, ParentLink, { 0 })
    zox_prefab_set(e, FontOutlineColor, { { 255, 0, 0, 255 }})
    zox_prefab_set(e, FontFillColor, { { 0, 255, 0, 255 }})
    zox_prefab_set(e, FontThickness, { 1 })
    zox_prefab_add(e, TextData)
    zox_prefab_set(e, Children, { 0, NULL })
    zox_set(e, Color, { back_bar_color_3D_start })
    prefab_set_mesh3D_vertices(world, e, square_vertices, 4, text3D_size);
    return e;
}

ecs_entity_t spawn_text3D(ecs_world_t *world, const Text3DData *data) {
    zox_instance(data->prefab)
    zox_name("text3D")
    // zox_log("+ spawned text3D: %lu\n", e)
    zox_set(e, ParentLink, { data->parent })
    zox_set(e, RenderDisabled, { data->render_disabled })
    zox_set(e, TextSize, { data->font_size })
    zox_set(e, TextPadding, { data->padding })
    zox_set(e, MeshAlignment, { data->alignment })
    zox_set(e, FontThickness, { data->font_thickness })
    zox_set(e, FontFillColor, { color_black })
    zox_set(e, FontOutlineColor, { color_white})
    //zox_set(e, FontFillColor, { data->font_fill_color })
    //zox_set(e, FontOutlineColor, { data->font_outline_color })
    zox_set(e, LocalPosition3D, { data->position })

    Children *children = &((Children) { 0, NULL });
    TextData *textData = &((TextData) { 0, NULL });
    const int zext_data_length = data->text != NULL ? strlen(data->text) : 0;
    initialize_memory_component(TextData, textData, byte, zext_data_length)
    for (int i = 0; i < textData->length; i++) {
        textData->value[i] = convert_ascii(data->text[i]);
    }
    const int zigels_count = calculate_total_zigels(textData->value, textData->length);
    initialize_memory_component(Children, children, ecs_entity_t, zigels_count)
    const int2 pixel_size = calculate_zext_size(textData->value, textData->length, data->font_size, data->padding, default_line_padding);
    for (int i = 0; i < zigels_count; i++) {
        const int data_index = calculate_zigel_data_index(textData->value, textData->length, i);
        const byte zigel_index = calculate_zigel_index(textData->value, textData->length, i);
        Zigel3DData zigel_data = {
            .parent = e,
            .prefab = data->prefab_zigel,
            .zigel_index = zigel_index,
            .data_index = data_index,
            .data_max = zigels_count,
            .font_size = data->font_size,
            .font_thickness = data->font_thickness,
            .fill_color = data->fill_color,
            .outline_color = data->outline_color,
            .position = data->position
        };
        // todo pass in Text3DData, instead of using zigels data
        const ecs_entity_t zigel = spawn_zigel3D(world, &zigel_data);
        children->value[i] = zigel;
    }
    zox_set(e, TextData, { textData->length, textData->value })
    zox_set(e, Children, { children->length, children->value })
    debug_entity_text3D = e;
    return e;
}
