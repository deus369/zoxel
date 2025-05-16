#define statbar_float_position 0.32f
#define statbar_float_height + 0.048f

void spawn_character_name_label(ecs_world_t *world, spawned_character3D_data data) {
    //const ecs_entity_t e, ElementLinks *elementLinks, const ecs_entity_t player, const char *name) {
    float ui_position = statbar_float_position + statbar_float_height;
    const SpawnDataElement3D label3D_spawn_data = {
        .prefab = prefab_label3D,
        .ui_holder = data.e,
        .position_y = ui_position,
        .base_color = (color) { 5, 5, 5, 88 }, // background color
    };
    Text3DData label3D_text_data = {
        .prefab = prefab_text3D,
        .text = data.name, // "Dave Lvl 3"
    };
    Zigel3DData label3D_zigel_data = {
        .prefab = prefab_zigel3D,
        .font_thickness = 10,
        .resolution = 64,
        .fill_color = (color) { 255, 255, 255, 255 },
        .outline_color = (color) { 5, 15, 5, 122 }
    };
    const ecs_entity_t label3D = spawn_label3D(world, label3D_spawn_data, label3D_text_data, label3D_zigel_data);
    add_to_ElementLinks(data.elementLinks, label3D);
}