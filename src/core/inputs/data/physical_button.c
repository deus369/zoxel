typedef struct {
    unsigned char is_pressed;
    unsigned char pressed_this_frame;
    unsigned char released_this_frame;
} PhysicalButton;

void reset_key(PhysicalButton *key) {
    if (key->pressed_this_frame) key->pressed_this_frame = 0;
    else if (key->released_this_frame) key->released_this_frame = 0;
}