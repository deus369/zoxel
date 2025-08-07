#ifndef zoxm_game
#define zoxm_game

zox_begin_module(ZoxGame)
    game_name = "zixel";
    zox_game_type = zox_game_mode_2D;
    headless = 0;
    menu_sky_color = (color_rgb) { 33, 33, 166 };
    menu_sky_bottom_color = (color_rgb) { 33, 33, 166 };
    game_sky_color = (color_rgb) { 22, 177, 33 };
    game_sky_bottom_color = (color_rgb) { 22, 177, 33 };
    set_prefab_debug_label(world, &get_label_character2_player);
    zox_game_camera_mode = zox_camera_mode_2D;
zox_end_module(ZoxGame)

#endif
