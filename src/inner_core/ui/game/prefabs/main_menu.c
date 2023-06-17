ecs_entity_t prefab_main_menu;
ecs_entity_t main_menu;

ecs_entity_t spawn_prefab_main_menu(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab_child(prefab_ui_list)
    // zox_prefab_child(window_prefab)
    zox_name("prefab_main_menu")
    zox_add_tag(e, MainMenu)
    ecs_defer_end(world);
    prefab_main_menu = e;
    return e;
}

ecs_entity_t spawn_main_menu(ecs_world_t *world, const char *header_label, int2 position, float2 anchor, unsigned char is_close_button) {
    /*int labels_count = 3;
    const text_group labels[] = { { "play" }, { "options" }, { "exit" } };
    ClickEvent events[] = { { &button_event_play_game }, { NULL }, { &button_event_exit_game } };*/
    int labels_count = 2;
    const text_group labels[] = { { "play" }, { "exit" } };
    ClickEvent events[] = { { &button_event_play_game }, { &button_event_exit_game } };
    ecs_entity_t e = spawn_ui_list(world, prefab_main_menu, "zoxel", labels_count, labels, events, position, anchor, is_close_button);
    main_menu = e;
    return e;
}

/*int2 canvas_size = ecs_get(world, main_canvas, PixelSize)->value;

const char *button_label_1 = "play";
const char *button_label_2 = "options";
const char *button_label_3 = "exit";

float ui_scale = default_ui_scale;
int font_size = 28;
int header_margins = 12;
// scale the ui!
int2 window_size = { 260, 220 };
window_size.x *= ui_scale;
window_size.y *= ui_scale;
font_size *= ui_scale;
header_margins *= ui_scale;
int2 button_padding = (int2) { (int) (font_size * 0.6f), (int) (font_size * 0.3f) };
int header_height = (font_size + header_margins - 1); //  * 2;
anchor_position2D(&position, window_size, anchor, header_height);
// positions
int2 play_button_position = (int2) { 0, font_size * 2 };
int2 options_button_position = int2_zero; // (int2) { 0, 0 };
int2 header_position = (int2) { 0, header_height / 2 };
#ifdef zoxel_on_android
    play_button_position.y = font_size;
    options_button_position.y = -font_size;
#endif
ecs_defer_begin(world);
zox_instance(prefab_main_menu)
zox_name("main_menu")
float2 position2D = initialize_ui_components(world, e, main_canvas, position, window_size, anchor, 0, canvas_size);
Children children = { };
int children_count = 4;
#ifdef zoxel_on_android
    children_count = 3;
#endif
initialize_memory_component_non_pointer(children, ecs_entity_t, children_count);
// header
children.value[0] = spawn_header(world, e, header_position, (int2) { window_size.x, font_size + header_margins },
    (float2) { 0.5f, 1.0f }, header_label, font_size, header_margins, 1, position2D, window_size, is_close_button, canvas_size);
// buttons
children.value[1] = spawn_button(world, e, play_button_position, button_padding,
    (float2) { 0.5f, 0.5f }, button_label_1, font_size, 1, position2D, window_size, canvas_size);
zox_set(children.value[1], ClickEvent, { &button_event_play_game });
children.value[2] = spawn_button(world, e, options_button_position, button_padding,
    (float2) { 0.5f, 0.5f }, button_label_2, font_size, 1, position2D, window_size, canvas_size);
#ifndef zoxel_on_android
    children.value[3] = spawn_button(world, e, (int2) { 0, - font_size * 2 }, button_padding,
        (float2) { 0.5f, 0.5f }, button_label_3, font_size, 1, position2D, window_size, canvas_size);
    zox_set(children.value[3], ClickEvent, { &button_event_exit_game });
#endif
ecs_set(world, e, Children, { children.length, children.value });
ecs_defer_end(world);
main_menu = e;
#ifdef zoxel_debug_spawns
    zoxel_log("Spawned main menu [%lu]\n", (long int) e);
#endif
select_first_button(world, children.value[1]);*/