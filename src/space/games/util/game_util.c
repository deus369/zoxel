// todo: make this an event i can latch onto
// player hooks
extern void attach_to_character(ecs_world_t *world, ecs_entity_t player, ecs_entity_t camera, ecs_entity_t character);
extern void detatch_from_character(ecs_world_t *world, ecs_entity_t player, ecs_entity_t camera, ecs_entity_t character);
extern void button_event_pause_game(ecs_world_t *world, ecs_entity_t trigger_entity);
extern ecs_entity_t local_character3D;
// do I still need render_camera_matrix? - yes - used to insert matrix in each camera system run
extern const char *game_name;
ecs_entity_t game_ui = 0;
ecs_entity_t game_ui_touch = 0;
ecs_entity_t actionbar_ui = 0;
ecs_entity_t healthbar_2D = 0;
#ifndef zox_disable_player_character3D
    unsigned char game_rule_attach_to_character = 1;
#else
    unsigned char game_rule_attach_to_character = 0;
#endif

void dispose_in_game_ui_touch(ecs_world_t *world) {
    zox_delete_and_set(game_ui_touch)
}

void spawn_in_game_ui_touch(ecs_world_t *world) {
    if (game_ui_touch) return;
    const unsigned char pause_button_size = 80;
    const ClickEvent on_pause_ui = (ClickEvent) { &button_event_pause_game };
    game_ui_touch = spawn_button_on_canvas(world, main_canvas, (int2) { pause_button_size, pause_button_size }, (byte2) { 8, 4 }, (color) { 77, 32, 44, 255 }, "P", pause_button_size, float2_zero, on_pause_ui);
    // zox_log("  > spawning touch ui [%lu]\n", game_ui_touch)
}

void dispose_in_game_ui(ecs_world_t *world, ecs_entity_t player) {
    // todo: get ui links
    dispose_in_game_ui_touch(world);
    zox_delete_and_set(game_ui)
}

void spawn_in_game_ui(ecs_world_t *world, ecs_entity_t player) {    // spawn game uis
    // ecs_entity_t player = main_player;
    const DeviceMode *deviceMode = zox_get(player, DeviceMode)
    unsigned char is_touch = deviceMode->value == zox_device_mode_touchscreen;
#ifdef zoxel_mouse_emulate_touch
    is_touch = 1;
#endif
    ecs_entity_t canvas = main_canvas;
    if (is_touch) spawn_in_game_ui_touch(world);
    // actionbar_ui - spawn actionbar
    game_ui = ecs_new_w_pair(world, EcsIsA, prefab_element);
    zox_prefab_set(game_ui, Children, { 0, NULL })
    Children *game_ui_children = zox_get_mut(game_ui, Children)
    resize_memory_component(Children, game_ui_children, ecs_entity_t, 2)
    int actions_count = 8;
    int padding = 6;
    int icon_size = 64;
    int margins = 16;
    actionbar_ui = spawn_element_on_canvas(world, canvas, (int2) { 0, 24 }, (int2) { padding + (icon_size + padding) * actions_count + margins * 2, icon_size + padding * 2 }, (float2) { 0.5f, 0 });
    zox_prefab_set(actionbar_ui, Children, { 0, NULL })
    Children *children = zox_get_mut(actionbar_ui, Children)
    resize_memory_component(Children, children, ecs_entity_t, actions_count)
    for (int i = 0; i < actions_count; i++) {
        const color action_color = (color) { 99, 11, 66, 255 };
        int position_x = (int) ((i - (actions_count / 2) + 0.5f) * (icon_size + padding));
        children->value[i] = spawn_element(world, actionbar_ui, canvas, (int2) { position_x, 0 }, (int2) { icon_size, icon_size }, float2_half, 1, action_color);
    }
    zox_modified(actionbar_ui, Children)
    // statbar testing
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    float2 elementbar2D_anchor = float2_top_left; // float2_half;
    healthbar_2D = spawn_elementbar2D(world, player, canvas, canvas, int2_zero, (int2) { 12, 8 }, elementbar2D_anchor, "health [5/10]", 18, 0, int2_half(canvas_size), canvas_size, canvas_size, 0);
    if (local_character3D) {
        const UserStatLinks *userStatLinks = zox_get(local_character3D, UserStatLinks)
        zox_prefab_set(healthbar_2D, UserStatLink, { userStatLinks->value[0] })
    }
    game_ui_children->value[0] = actionbar_ui;
    game_ui_children->value[1] = healthbar_2D;
    zox_modified(actionbar_ui, Children)
}

void end_game_on_player(ecs_world_t *world, ecs_entity_t player) {
    dispose_in_game_ui(world, player);
    zox_delete_and_set(pause_ui)
    // spawn/delete on that players canvas
    const float2 main_menu_anchor = float2_half; // { 0.5f, 0.5f };
    const int2 main_menu_position = int2_zero;
    spawn_main_menu(world, game_name, main_menu_position, main_menu_anchor, 0);
    // pause inputs
    disable_inputs_until_release(world, player, zox_device_mode_none);
    // todo: get player linked main camera
    ecs_entity_t main_camera = main_cameras[0]; // get player camera link instead
    ecs_entity_t character = 0;
    if (camera_follow_mode == zox_camera_follow_mode_attach) character = zox_get_value(main_camera, ParentLink)
    else if (camera_follow_mode == zox_camera_follow_mode_follow_xz) character = zox_get_value(main_camera, CameraFollowLink)
    if (character) detatch_from_character(world, player, main_camera, local_character3D);
    float3 camera_position = float3_zero;
    float4 camera_rotation = quaternion_identity;
    get_camera_start_transform(&camera_position, &camera_rotation);
    zox_set(main_camera, Position3D, { camera_position })
    zox_set(main_camera, Rotation3D, { camera_rotation })
    local_character3D = 0;
}

// somewhere below android on samsung crashes...!
// try disabling touch inpput to see if helps
// todo: for each player
void play_game_on_player(ecs_world_t *world, ecs_entity_t player) {
    disable_inputs_until_release(world, player, zox_device_mode_none);
    // ui control
    zox_delete_and_set(main_menu)
    spawn_in_game_ui(world, player);
    // todo: get player camera linked to it
    ecs_entity_t main_camera = main_cameras[0];
    // temp here for now
    if (!zox_has(main_camera, Streamer)) {
        zox_add_only(main_camera, Streamer)
        zox_add_only(main_camera, StreamPoint)
    }
    const Position3D *camera_position3D = zox_get(main_camera, Position3D)
    int3 terrain_position = int3_zero;
    if (camera_position3D) terrain_position = get_chunk_position(camera_position3D->value, default_chunk_size);
    zox_set(main_camera, StreamPoint, { terrain_position })
    // link camera to terrain it's in
    // todo: dynamically set camera in whatever world it is in, multiple links? position space based
    if (local_terrain) zox_set(main_camera, VoxLink, { local_terrain })
    if (game_rule_attach_to_character) {
        float3 spawn_position = zox_get_value(main_camera, Position3D)
        spawn_position.x = 8;
        spawn_position.z = 8;
        float4 spawn_rotation = quaternion_identity;
        const vox_file vox = vox_files[3]; // get mr penguin vox
        local_character3D = spawn_player_character3D_in_world(world, &vox, spawn_position, spawn_rotation, 0);
        zox_add_tag(local_character3D, Aura)
        attach_to_character(world, player, main_camera, local_character3D);
    } else attach_to_character(world, player, main_camera, 0);
}

void play_game(ecs_world_t *world) {
    if (!local_game) return;
    zox_set(local_game, GameState, { zoxel_game_state_playing })
    set_sky_color(world, game_sky_color, game_sky_bottom_color);
#ifdef zox_on_play_spawn_terrain
    int3 terrain_position = int3_zero;
    create_terrain(world, terrain_position);
    zox_set(local_terrain, RealmLink, { local_realm }) // this should be done on spawn
#endif
    // todo: for each player linked to game
    ecs_entity_t player = main_player;
    play_game_on_player(world, player);
    unlock_achievement("test_achievement"); // idk if this can be per player
}

void end_game(ecs_world_t *world) {
    zox_set(local_game, GameState, { zoxel_game_state_main_menu })
    // todo: for each player in game
    ecs_entity_t player = main_player;
    end_game_on_player(world, player);
#ifdef zox_on_play_spawn_terrain
    zox_delete_and_set(local_terrain)
#endif
    set_sky_color(world, menu_sky_color, menu_sky_bottom_color);
}

// const int edge_buffer = 8 * default_ui_scale;
// float2 window_anchor = { 0.0f, 1.0f };
// int2 window_position = { 0 + edge_buffer, 0 - edge_buffer };
