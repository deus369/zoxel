typedef struct {
    unsigned char is_pressed;
    unsigned char pressed_this_frame;
    unsigned char released_this_frame;
} PhysicalButton;

// which one to use here??

void set_key(PhysicalButton *key, int event_type) {
    unsigned char key_down = event_type == SDL_KEYDOWN;
    unsigned char key_released = event_type == SDL_KEYUP;
    if (!key->is_pressed && key_down) {
        key->pressed_this_frame = 1;
    }
    if (key->is_pressed && key_released) {
        key->released_this_frame = 1;
    }
    key->is_pressed = key_down;
}

void set_mouse_button(PhysicalButton *key, int event_type) {
    unsigned char keyDown = event_type == SDL_MOUSEBUTTONDOWN;
    unsigned char keyReleased = event_type == SDL_MOUSEBUTTONUP;
    key->pressed_this_frame = keyDown;
    key->released_this_frame = keyReleased;
    if (keyDown) {
        key->is_pressed = 1;
    } else if (keyReleased) {
        key->is_pressed = 0;
    }
}