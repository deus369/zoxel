const int particleSpawnCount = 266;
const float debug_rotation_speed = 12;
const float debug_rotation_addition = 5;
extern ecs_entity_t local_character3D; // change to devicece links and use e!

// quality of life
void QolShortcutsSystem(ecs_iter_t *it) {
    unsigned char is_toggle_fullscreen = 0;
    zox_iter_world()
    zox_field_in(Keyboard, keyboards, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Keyboard, keyboards, keyboard)
        // toggle player connected application
        if ((keyboard->left_alt.is_pressed || keyboard->right_alt.is_pressed) && keyboard->enter.pressed_this_frame) is_toggle_fullscreen = 1;
        else if (keyboard->f11.pressed_this_frame) is_toggle_fullscreen = 1;
    }
    if (is_toggle_fullscreen) sdl_toggle_fullscreen(world, main_app);
} zox_declare_system(QolShortcutsSystem)
