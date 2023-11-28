// player hooks
extern void attach_to_character(ecs_world_t *world, ecs_entity_t player, ecs_entity_t camera, ecs_entity_t character);
extern void detatch_from_character(ecs_world_t *world, ecs_entity_t player, ecs_entity_t camera, ecs_entity_t character);
extern void button_event_pause_game(ecs_world_t *world, ecs_entity_t trigger_entity);
extern ecs_entity_t local_character3D;
unsigned char game_rule_attach_to_character = 1;
// do I still need render_camera_matrix? - yes - used to insert matrix in each camera system run
ecs_entity_t game_ui = 0;
ecs_entity_t actionbar_ui = 0;
// const char *game_name = "zoxel";
extern const char *game_name;

void dispose_in_game_ui_touch(ecs_world_t *world) {
    if (game_ui) {
        // zox_log("  > disposing touch ui [%lu]\n", game_ui)
        zox_delete(game_ui)
        game_ui = 0;
    }
}

void spawn_in_game_ui_touch(ecs_world_t *world) {
    if (game_ui) return;
    const unsigned char pause_button_size = 80;
    const ClickEvent on_pause_ui = (ClickEvent) { &button_event_pause_game };
    game_ui = spawn_button_on_canvas(world, main_canvas, (int2) { pause_button_size, pause_button_size }, (byte2) { 8, 4 }, (color) { 77, 32, 44, 255 }, "P", pause_button_size, float2_zero, on_pause_ui);
    // zox_log("  > spawning touch ui [%lu]\n", game_ui)
}

void dispose_in_game_ui(ecs_world_t *world) {
    dispose_in_game_ui_touch(world);
    // zox_logg("  > disposing actionbar\n")
    if (actionbar_ui) {
        zox_delete(actionbar_ui)
        actionbar_ui = 0;
    }
}

void spawn_in_game_ui(ecs_world_t *world) {    // spawn game uis
    const DeviceMode *deviceMode = zox_get(main_player, DeviceMode)
    unsigned char is_touch = deviceMode->value == zox_device_mode_touchscreen;
#ifdef zoxel_mouse_emulate_touch
    is_touch = 1;
#endif
    if (is_touch) spawn_in_game_ui_touch(world);
    // actionbar_ui - spawn actionbar
    int actions_count = 8;
    int padding = 6;
    int icon_size = 64;
    int margins = 16;
    actionbar_ui = spawn_element_on_canvas(world, main_canvas, (int2) { 0, 24 }, (int2) { padding + (icon_size + padding) * actions_count + margins * 2, icon_size + padding * 2 }, (float2) { 0.5f, 0 });
    zox_prefab_set(actionbar_ui, Children, { 0, NULL })
    Children *children = zox_get_mut(actionbar_ui, Children)
    resize_memory_component(Children, children, ecs_entity_t, actions_count)
    for (int i = 0; i < actions_count; i++) {
        const color action_color = (color) { 99, 11, 66, 255 };
        int position_x = (int) ((i - (actions_count / 2) + 0.5f) * (icon_size + padding));
        children->value[i] = spawn_element(world, actionbar_ui, main_canvas, (int2) { position_x, 0 }, (int2) { icon_size, icon_size }, (float2) { 0.5f, 0.5f }, 1, action_color);
    }
    zox_modified(actionbar_ui, Children)
}

void end_game(ecs_world_t *world) {
    // zox_logg("  > ending game\n")
    zox_delete(pause_ui)
    pause_ui = 0;
    dispose_in_game_ui(world);
    zox_set(local_game, GameState, { zoxel_game_state_main_menu })
    disable_inputs_until_release(world, main_player);
    float2 main_menu_anchor = { 0.5f, 0.5f };
    int2 main_menu_position = int2_zero;
    spawn_main_menu(world, game_name, main_menu_position, main_menu_anchor, 0);
    ecs_entity_t main_camera = main_cameras[0]; // get player camera link instead
    ecs_entity_t character = 0;
    if (camera_follow_mode == zox_camera_follow_mode_attach) character = zox_get_value(main_camera, ParentLink)
    else if (camera_follow_mode == zox_camera_follow_mode_follow_xz) character = zox_get_value(main_camera, CameraFollowLink)
    if (character) detatch_from_character(world, main_player, main_camera, local_character3D);
    set_sky_color(world, menu_sky_color, menu_sky_bottom_color);
    float3 camera_position = float3_zero;
    float4 camera_rotation = quaternion_identity;
    get_camera_start_transform(&camera_position, &camera_rotation);
    zox_set(main_camera, Position3D, { camera_position })
    zox_set(main_camera, Rotation3D, { camera_rotation })
    local_character3D = 0;
#ifdef zox_on_play_spawn_terrain
    if (local_terrain) {
        zox_delete(local_terrain)
        local_terrain = 0;
    }
#endif
    // zox_logg("  > ending setting game to [main_menu]\n")
}

void play_game(ecs_world_t *world) {
    // zox_logg("  > playing game\n")
    if (!local_game) return;
    if (!main_menu) return;
    ecs_entity_t main_camera = main_cameras[0]; // get player camera link insteaderas
    if (main_camera == 0) return;
    zox_set(local_game, GameState, { zoxel_game_state_playing })
    zox_delete(main_menu)   // close main menu
    main_menu = 0;
    spawn_in_game_ui(world);
    disable_inputs_until_release(world, main_player);
    int3 center_position = int3_zero;
    const Position3D *camera_position3D = zox_get(main_camera, Position3D)
    if (camera_position3D) center_position = get_chunk_position(camera_position3D->value, default_chunk_size);
    zox_set(main_camera, StreamPoint, { center_position })
    // temp here for now
    if (!zox_has(main_camera, Streamer)) {
        zox_add_only(main_camera, Streamer)
        zox_add_only(main_camera, StreamPoint)
    }
    set_sky_color(world, game_sky_color, game_sky_bottom_color);
    // somewhere below android on samsung crashes...!
    // try disabling touch inpput to see if helps
#ifdef zox_on_play_spawn_terrain
    create_terrain(world, center_position);
#endif
    if (local_terrain) {
        zox_set(main_camera, VoxLink, { local_terrain })
        zox_set(local_terrain, RealmLink, { local_realm })
    }
#ifdef zox_disable_player_character3D
    attach_to_character(world, main_player, main_camera, 0);
#else
    if (game_rule_attach_to_character) {
        float3 spawn_position = zox_get_value(main_camera, Position3D)
        spawn_position.x = 8;
        spawn_position.z = 8;
        float4 spawn_rotation = quaternion_identity;
        const vox_file vox = vox_files[3]; // get mr penguin vox
        local_character3D = spawn_player_character3D_in_world(world, &vox, spawn_position, spawn_rotation, 0);
        zox_add_tag(local_character3D, Aura)
        attach_to_character(world, main_player, main_camera, local_character3D);
    } else attach_to_character(world, main_player, main_camera, 0);
#endif
    // zox_logg("  > ending setting game to [playing]\n")
    zox_logg("  > achievement unlocked [test_achievement]\n")
    unlock_achievement("test_achievement");
}

// const int edge_buffer = 8 * default_ui_scale;
// float2 window_anchor = { 0.0f, 1.0f };
// int2 window_position = { 0 + edge_buffer, 0 - edge_buffer };
