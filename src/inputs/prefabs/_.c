// more settings
#define zox_gamepad_layout_type_normal 0
#define zox_gamepad_layout_type_xbox 1
#define zox_gamepad_layout_type_steamdeck 2
#define zox_device_stick_left 0
#define zox_device_stick_right 1
const byte fingers_count = 2;
// prefeabs
entity prefab_zevice_button;
entity prefab_zevice_stick;
entity prefab_zevice_pointer;
entity prefab_device;
entity prefab_touchscreen;
entity prefab_keyboard;
entity prefab_mouse;
entity prefab_gamepad;

entity local_touchscreen;
entity local_keyboard;
entity gamepad_entity;
entity local_mouse;

#include "zevice_button.c"
#include "zevice_stick.c"
#include "zevice_pointer.c"
#include "mouse.c"
#include "device.c"
#include "keyboard.c"
#include "gamepad.c"
#include "touchscreen.c"

int prefabs_count_devices = 0;
entity prefabs_devices[32];

// setters for higher modules to add to characters
#define zox_prefab_set_device(T, ...) {\
    for (int i = 0; i < prefabs_count_devices; i++) {\
        zox_prefab_set(prefabs_devices[i], T, __VA_ARGS__)\
    }\
}

void spawn_prefabs_inputs(ecs *world) {
    prefab_zevice_button = spawn_prefab_device_button(world);
    prefab_zevice_stick = spawn_prefab_device_stick(world);
    prefab_zevice_pointer = spawn_prefab_zevice_pointer(world);
    prefab_device = spawn_prefab_device(world);
    prefab_keyboard = spawn_prefab_keyboard(world, prefab_device);
    prefab_mouse = spawn_prefab_mouse(world, prefab_device);
    prefab_gamepad = spawn_prefab_gamepad(world, prefab_device);
    prefab_touchscreen = spawn_prefab_touchscreen(world, prefab_device);
    prefabs_devices[prefabs_count_devices++] = prefab_device;
    prefabs_devices[prefabs_count_devices++] = prefab_keyboard;
    prefabs_devices[prefabs_count_devices++] = prefab_mouse;
    prefabs_devices[prefabs_count_devices++] = prefab_gamepad;
    prefabs_devices[prefabs_count_devices++] = prefab_touchscreen;
}
