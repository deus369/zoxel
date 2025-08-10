void on_confirmed_new_realm(
    ecs_world_t *world,
    const ClickEventData *event
) {
    ecs_entity_t player = event->clicker;
    zox_geter(player, ElementLinks, elements);
    find_array_element_with_tag(elements, MenuNewRealm, menu);
    if (menu) {
        zox_delete(menu);
    }

    zox_geter_value(player, GameLink, ecs_entity_t, game);
    zox_geter_value(game, RealmLink, ecs_entity_t, realm);
    zox_geter_value(realm, Seed, long int, seed);
    zox_log("confirm new realm [%s] [%lu]", game_name, seed);
    realm_save.seed = seed;
    delete_save_directory(game_name);
    create_new_save_directory(game_name);
    save_realm(game_name, "seed.dat", &realm_save);
    zox_set(game, GameStateTarget, { zox_game_load });
    // todo: load realm list
}

void on_cancelled_new_realm(
    ecs_world_t *world,
    const ClickEventData *event
) {
    ecs_entity_t player = event->clicker;
    zox_geter(player, ElementLinks, elements);
    find_array_element_with_tag(elements, MenuNewRealm, menu);
    if (menu) {
        zox_delete(menu);
    }
    zox_log("canceled new realm");
    zox_geter_value(player, CanvasLink, ecs_entity_t, canvas);
    spawn_main_menu(world, player, canvas, game_name);
}

ecs_entity_t spawn_menu_new_realm(
    ecs_world_t *world,
    const ecs_entity_t player,
    lint seed
) {
    zox_geter_value(player, CanvasLink, ecs_entity_t, canvas);

    // more data
    const char* header_label = "New Realm";
    const int max_labels = max_settings;
    const byte layer = 1;
    const byte font_size = 32;

    // # Window #
    CanvasSpawnData canvas_data = {
        .e = canvas,
        .size = zox_gett_value(canvas, PixelSize),
    };
    ElementSpawnData window_element_data = {
        .prefab = prefab_window,
        .position = (int2) { 0, 0 },
        .size = (int2) { 520, 580 },
        .anchor = float2_half,
        .layer = layer,
    };
    ParentSpawnData window_parent_data = {
        .e = canvas_data.e,
        .size = canvas_data.size,
        .position = int2_half(canvas_data.size),
    };
    SpawnWindow2 window_data = {
        .header_text = header_label,
        .header_font_size = 32,
        .header_padding = (byte2) { 8, 4 },
        .is_scrollbar = 0,
    };

    Children children = (Children) { 0 };
    window_data.children = &children;
    const ecs_entity_t e = spawn_window2(world,
        canvas_data,
        window_parent_data,
        &window_element_data,
        &window_data);
    zox_add_tag(e, MenuNewRealm);

    // # List #
    SpawnListElement elements[max_labels];
    int elements_count = 0;

    elements[elements_count++] = (SpawnListElement) {
        .text = "Enter",
        .on_click = { &on_confirmed_new_realm },
    };

    elements[elements_count++] = (SpawnListElement) {
        .type = 0,  // 0 is button or label for now
        .text = "Seed",
    };

    char seed_label[32];
    sprintf(seed_label, "[%lu]", seed);
    elements[elements_count++] = (SpawnListElement) {
        .type = 0,  // 0 is button or label for now
        .text = seed_label,
    };

    elements[elements_count++] = (SpawnListElement) {
        .text = "Exit",
        .on_click = { &on_cancelled_new_realm },
    };
    const byte visible_count = elements_count;

    ParentSpawnData list_parent_data = {
        .e = e,
        .size = window_element_data.size,
        .position = window_element_data.position_in_canvas,
    };
    ElementSpawnData list_element_data = {
        .prefab = prefab_list,
        .position = (int2) { 0, -25 },
        .size = (int2) { window_element_data.size.x, window_element_data.size.y - 50 },
        .anchor = float2_half,
        .layer = layer + 1,
    };
    SpawnList ui_list_data = (SpawnList) {
        .elements = elements,
        .count = elements_count,
        .visible_count = visible_count,
        .font_size = font_size,
        .fill = (color) { 0, 0, 0, 0 },
        .outline = (color) { 0, 255, 255, 55 },
        .padding = byte2_single(8),
        .spacing = 24,
        .slider_height = 64,
        .slider_padding = 64,
    };
    const ecs_entity_t list = spawn_list(world,
        canvas_data,
        list_parent_data,
        list_element_data,
        ui_list_data);
    add_to_Children(window_data.children, list);
    zox_set_ptr(e, Children, children);

    zox_muter(player, ElementLinks, pelements);
    add_to_ElementLinks(pelements, e);
    zox_set(e, ElementHolder, { player });

    // return our window
    return e;
}

void button_event_new_game(
    ecs_world_t *world,
    const ClickEventData *event
) {
    ecs_entity_t player = event->clicker;
    zox_geter(player, ElementLinks, elements);
    find_array_element_with_tag(elements, MenuMain, menu);
    if (menu) {
        zox_delete(menu);
    } else {
        zox_log_error("Could not find main menu.");
    }
    zox_geter_value(player, GameLink, ecs_entity_t, game);
    zox_geter_value(game, RealmLink, ecs_entity_t, realm);
    lint seed = get_unique_time_seed();
    set_noise_seed(seed);
    zox_set(realm, Seed, { seed });
    spawn_menu_new_realm(world, player, seed);
}