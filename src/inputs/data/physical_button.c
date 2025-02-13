typedef struct {
    byte is_pressed;
    byte pressed_this_frame;
    byte released_this_frame;
} PhysicalButton;

void reset_key(PhysicalButton *key) {
    if (key->pressed_this_frame) key->pressed_this_frame = 0;
    else if (key->released_this_frame) key->released_this_frame = 0;
}