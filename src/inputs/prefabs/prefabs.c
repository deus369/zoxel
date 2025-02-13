// more settings
#define zox_gamepad_layout_type_normal 0
#define zox_gamepad_layout_type_xbox 1
#define zox_gamepad_layout_type_steamdeck 2
#define zox_device_stick_left 0
#define zox_device_stick_right 1
const byte fingers_count = 2;
// prefeabs
ecs_entity_t prefab_zevice_button;
ecs_entity_t prefab_zevice_stick;
ecs_entity_t prefab_zevice_pointer;
ecs_entity_t prefab_device;
ecs_entity_t prefab_touchscreen;
ecs_entity_t prefab_keyboard;
ecs_entity_t prefab_mouse;
ecs_entity_t prefab_gamepad;

ecs_entity_t touchscreen_entity;
ecs_entity_t keyboard_entity;
ecs_entity_t gamepad_entity;
ecs_entity_t mouse_entity;

#include "zevice_button.c"
#include "zevice_stick.c"
#include "zevice_pointer.c"
#include "mouse.c"
#include "device.c"
#include "keyboard.c"
#include "gamepad.c"
#include "touchscreen.c"

void spawn_prefabs_inputs(ecs_world_t *world) {
    prefab_zevice_button = spawn_prefab_device_button(world);
    prefab_zevice_stick = spawn_prefab_device_stick(world);
    prefab_zevice_pointer = spawn_prefab_zevice_pointer(world);
    prefab_device = spawn_prefab_device(world);
    prefab_keyboard = spawn_prefab_keyboard(world, prefab_device);
    prefab_mouse = spawn_prefab_mouse(world, prefab_device);
    prefab_gamepad = spawn_prefab_gamepad(world, prefab_device);
    prefab_touchscreen = spawn_prefab_touchscreen(world, prefab_device);
}
