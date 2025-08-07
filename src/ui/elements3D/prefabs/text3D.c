typedef struct {
    entity prefab;
    entity parent;
    float3 position;
    byte alignment;         // mesh_alignment
    byte2 padding;          // around zigels
    const char* text;
} Text3DData;

entity spawn_prefab_text3D(ecs *world, const entity prefab) {
    zox_prefab_child(prefab);
    zox_prefab_name("text3D");
    zox_add_tag(e, Zext);
    zox_add_tag(e, Text3D);
    zox_prefab_set(e, MeshAlignment, { 0 });
    zox_prefab_set(e, TextSize, { 0 });
    zox_prefab_set(e, TextResolution, { 0 });
    zox_prefab_set(e, TextPadding, { byte2_zero });
    zox_prefab_set(e, ZextDirty, { 0 });
    zox_prefab_set(e, ParentLink, { 0 });
    zox_prefab_set(e, FontOutlineColor, { { 255, 0, 0, 255 }});
    zox_prefab_set(e, FontFillColor, { { 0, 255, 0, 255 }});
    zox_prefab_set(e, FontThickness, { 1 });
    zox_prefab_set(e, FontOutlineThickness, { 1 });
    zox_prefab_set(e, TextData, { 0, NULL });
    zox_prefab_set(e, Children, { 0, NULL });
    zox_prefab_set(e, RenderDisabled, { 0 });
    zox_prefab_set(e, Text3DScale, { 1 });
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

entity spawn_text3D(ecs *world,
    const Text3DData data,
    Zigel3DData zigel_data)
{
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
    // text
    const int length = data.text != NULL ? strlen(data.text) : 0;
    TextData text = (TextData) { 0, NULL };
    initialize_TextData(&text, length);
    for (int i = 0; i < text.length; i++) {
        text.value[i] = convert_ascii(data.text[i]);
    }
    zox_set_ptr(e, TextData, text);
    // children
    zigel_data.parent = e;
    const int zigels_count = calculate_total_zigels(text.value, text.length);
    Children children = (Children) { 0, NULL };
    initialize_Children(&children, zigels_count);
    for (int i = 0; i < children.length; i++) {
        const int data_index = calculate_zigel_data_index(
            text.value,
            text.length,
            i);
        const byte zigel_index = calculate_zigel_index(
            text.value,
            text.length,
            i);
        zigel_data.zigel_index = zigel_index;
        zigel_data.position = calculate_zigel3D_position(
            zigel3D_size,
            data_index,
            zigels_count,
            zigel_data.scale);
        const entity zigel3 = spawn_zigel3(world, zigel_data);
        children.value[i] = zigel3;
    }
    zox_set_ptr(e, Children, children);

    return e;
}