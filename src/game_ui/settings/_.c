// ui
ecs_entity_t local_menu_game;
// more ui
byte game_ui_has_taskbar = 0;// sizes
const int2 virtual_joystick_size = (int2) { 300, 300 };
const int2 virtual_joystick_pointer_size = (int2) { 120, 120 };
// colors
const color virtual_joystick_color = (color) { 44, 33, 33, 125 };
const color virtual_joystick_pointer_color = (color) { 88, 22, 22, 200 };
const color virtual_joystick_color2 = (color) { 33, 33, 44, 125 };
const color virtual_joystick_pointer_color2 = (color) { 22, 22, 88, 200 };

#include "labels.c"
#include "crosshair.c"