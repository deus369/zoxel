ecs_entity_t prefab_menu_actions;
ecs_entity_t prefab_icon_frame_action;
ecs_entity_t prefab_icon_action;
#include "icon_frame_action.c"
#include "icon_action.c"
zox_user_menu_functions_minimal(Actions, Action, actions, action)

ecs_entity_t spawn_player_menu_actions(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    SpawnWindowUsers data = get_default_spawn_window_users_data(world, prefab_menu_actions, character, canvas, canvas_size);
    data.header_zext.text = "";
    data.element.prefab = prefab_menu_actions;
    data.icon.prefab = prefab_icon_action;
    data.window.user_links_id = zox_id(ActionLinks);
    data.header_zext.font_size = 8;
    data.window.grid_size = (byte2) { 8, 1 };
    int header_height = data.header_zext.font_size + data.header.margins * 2;
    data.element.size = (int2) {
        data.window.grid_padding + (data.window.icon_size + data.window.grid_padding) * data.window.grid_size.x + data.window.grid_margins * 2,
        data.window.grid_padding + (data.window.icon_size + data.window.grid_padding) * data.window.grid_size.y + data.window.grid_margins * 2 + header_height
    };
    data.icon_frame.prefab = prefab_icon_frame_action;
    data.element.anchor = (float2) { 0.5f, 0 };
    data.element.position = (int2) { 0, 24 };
    data.icon_frame.texture.fill_color = default_fill_color_frame_action;
    return spawn_window_users(world, &data);
}

void spawn_prefabs_actions_ui(ecs_world_t *world) {
    prefab_icon_frame_action = spawn_prefab_icon_frame_action(world, prefab_icon_frame_user);
    prefab_icon_action = spawn_prefab_icon_action(world, prefab_icon_user);
    prefab_menu_actions = spawn_prefab_menu_actions(world, prefab_window_users);
    zox_set(prefab_menu_actions, IconFramePrefabLink, { prefab_icon_frame_action })
}
