ecs_entity_t spawn_popup3D_easy(ecs_world_t *world, const char *text, const color text_color, const float3 position) {
    const SpawnDataElement3D popup_spawn_data = {
        .prefab = prefab_popup3D,
        .base_color = (color) { 5, 5, 5, 0 }, // background color
    };
    Text3DData popup_text_data = {
        .prefab = prefab_popup3D,
        .text = text,
    };
    Zigel3DData popup_zigel_data = {
        .prefab = prefab_zigel3D,
        .font_thickness = 16,
        .resolution = 128,
        .fill_color = text_color,
        .outline_color = (color) { 15, 15, 15, 255 }
    };
    const ecs_entity_t e = spawn_popup3D(world, popup_spawn_data, popup_text_data, popup_zigel_data);
    if (e) {
        zox_set(e, Position3D, { position })
    }
    return e;
}