ecs_entity_t prefab_virtual_joystick_pointer;
ecs_entity_t prefab_virtual_joystick;
#include "joystick_handle.c"
#include "joystick.c"

void spawn_prefabs_touch(ecs_world_t* world) {
    prefab_virtual_joystick_pointer = spawn_prefab_virtual_joystick_pointer(world);
    prefab_virtual_joystick = spawn_prefab_virtual_joystick(world);
}