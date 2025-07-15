typedef struct {
    ecs_entity_t prefab;
    ecs_entity_t parent;
    float3 position;
    byte alignment;         // mesh_alignment
    byte2 padding;          // around zigels
    const char* text;
} Text3DData;

ecs_entity_t spawn_prefab_text3D(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("text3D")
    zox_add_tag(e, Zext)
    zox_add_tag(e, Text3D)
    zox_prefab_set(e, MeshAlignment, { 0 })
    zox_prefab_set(e, TextSize, { 0 })
    zox_prefab_set(e, TextResolution, { 0 })
    zox_prefab_set(e, TextPadding, { byte2_zero })
    zox_prefab_set(e, ZextDirty, { 0 })
    zox_prefab_set(e, ParentLink, { 0 })
    zox_prefab_set(e, FontOutlineColor, { { 255, 0, 0, 255 }})
    zox_prefab_set(e, FontFillColor, { { 0, 255, 0, 255 }})
    zox_prefab_set(e, FontThickness, { 1 })
    zox_prefab_set(e, FontOutlineThickness, { 1 })
    zox_prefab_add(e, TextData)
    zox_prefab_add(e, Children)
    zox_prefab_set(e, RenderDisabled, { 0 })
    zox_prefab_set(e, Text3DScale, { 1 })
    return e;
}

float3 calculate_zigel3D_position(const float2 zigel3D_size, const int data_index, const int zigels_count, float scale) {
    if (scale == 0) {
        scale = 1;
    }
    float3 position = float3_zero;
    position.x += zigel3D_size.x * 0.5f * scale;
    position.x -= zigel3D_size.x * 0.5f * zigels_count * scale; // centre
    position.x += zigel3D_size.x * data_index * scale;
    return position;
}

ecs_entity_t spawn_text3D(ecs_world_t *world, const Text3DData data, Zigel3DData zigel_data) {
    zox_instance(data.prefab)
    zox_name("text3D")
    zox_set(e, ParentLink, { data.parent })
    zox_set(e, LocalPosition3D, { data.position })
    zox_set(e, TextPadding, { data.padding })
    zox_set(e, MeshAlignment, { data.alignment })
    zox_set(e, FontThickness, { zigel_data.font_thickness })
    zox_set(e, FontFillColor, { zigel_data.fill_color })
    zox_set(e, FontOutlineColor, { zigel_data.outline_color })
    zox_set(e, Text3DScale, { zigel_data.scale })
    zox_set(e, TextSize, { zigel_data.resolution })
    Children *children = &((Children) { 0, NULL });
    TextData *textData = &((TextData) { 0, NULL });
    const int zext_data_length = data.text != NULL ? strlen(data.text) : 0;
    initialize_memory_component(TextData, textData, byte, zext_data_length)
    for (int i = 0; i < textData->length; i++) {
        textData->value[i] = convert_ascii(data.text[i]);
    }
    const int zigels_count = calculate_total_zigels(textData->value, textData->length);
    initialize_memory_component(Children, children, ecs_entity_t, zigels_count)
    zigel_data.parent = e;
    for (int i = 0; i < zigels_count; i++) {
        const int data_index = calculate_zigel_data_index(textData->value, textData->length, i);
        const byte zigel_index = calculate_zigel_index(textData->value, textData->length, i);
        zigel_data.zigel_index = zigel_index;
        zigel_data.position = calculate_zigel3D_position(zigel3D_size, data_index, zigels_count, zigel_data.scale);
        children->value[i] = spawn_zigel3D(world, zigel_data);
    }
    zox_set(e, TextData, { textData->length, textData->value })
    zox_set(e, Children, { children->length, children->value })
    debug_entity_text3D = e;
    return e;
}