#ifndef zoxm_touch
#define zoxm_touch

const int2 virtual_joystick_size = (int2) { 300, 300 };
const int2 virtual_joystick_pointer_size = (int2) { 120, 120 };
const color virtual_joystick_color = (color) { 44, 33, 33, 125 };
const color virtual_joystick_pointer_color = (color) { 88, 22, 22, 200 };
const color virtual_joystick_color2 = (color) { 33, 33, 44, 125 };
const color virtual_joystick_pointer_color2 = (color) { 22, 22, 88, 200 };

zox_declare_tag(JoystickUI);
#include "prefabs/_.c"
#include "spawn/_.c"
#include "systems/_.c"

zox_begin_module(Touch)
    zox_define_tag(JoystickUI);
    define_systems_touch(world);
    spawn_prefabs_touch(world);
zox_end_module(Touch)

#endif