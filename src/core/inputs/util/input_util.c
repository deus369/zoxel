void reset_input_devices(ecs_world_t *world) {
    device_reset_gamepad(world, gamepad_entity);
    device_reset_keyboard(world, keyboard_entity);
    device_reset_mouse(world, mouse_entity);
    device_reset_touchscreen(world, touchscreen_entity);
}