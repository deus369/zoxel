void set_sdl_mouse_button(PhysicalButton *key, SDL_EventType event_type) {
    byte keyDown = event_type == SDL_MOUSEBUTTONDOWN;
    byte keyReleased = event_type == SDL_MOUSEBUTTONUP;
    key->pressed_this_frame = keyDown;
    key->released_this_frame = keyReleased;
    if (keyDown) key->is_pressed = 1;
    else if (keyReleased) key->is_pressed = 0;
}