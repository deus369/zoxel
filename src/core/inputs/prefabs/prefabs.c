#include "zevice_button.c"
#include "zevice_stick.c"
#include "zevice_pointer.c"
#include "mouse.c"
#include "keyboard.c"
#include "gamepad.c"
#include "touchscreen.c"

void spawn_prefabs_inputs(ecs_world_t *world) {
    spawn_prefab_device_button(world);
    spawn_prefab_device_stick(world);
    spawn_prefab_zevice_pointer(world);
    spawn_prefab_keyboard(world);
    spawn_prefab_mouse(world);
    spawn_prefab_gamepad(world);
    spawn_prefab_touchscreen(world);
    // test_device_button_flags();
}
