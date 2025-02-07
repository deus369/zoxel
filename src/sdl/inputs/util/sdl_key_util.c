void set_sdl_key(PhysicalButton *key, SDL_EventType event_type) {
    unsigned char key_down = event_type == SDL_KEYDOWN;
    unsigned char key_released = event_type == SDL_KEYUP;
    if (!key->is_pressed && key_down) key->pressed_this_frame = 1;
    if (key->is_pressed && key_released) key->released_this_frame = 1;
    key->is_pressed = key_down;
}

void set_sdl_mouse_button(PhysicalButton *key, SDL_EventType event_type) {
    unsigned char keyDown = event_type == SDL_MOUSEBUTTONDOWN;
    unsigned char keyReleased = event_type == SDL_MOUSEBUTTONUP;
    key->pressed_this_frame = keyDown;
    key->released_this_frame = keyReleased;
    if (keyDown) key->is_pressed = 1;
    else if (keyReleased) key->is_pressed = 0;
}