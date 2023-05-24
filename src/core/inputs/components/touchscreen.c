typedef struct {
    Finger primary_touch;
    Finger secondary_touch;
} Touchscreen;
zox_custom_component(Touchscreen)

#define touchscreen_zero {\
    .primary_touch = finger_zero,\
    .secondary_touch = finger_zero\
}

unsigned char touchscreen_is_any_input(const Touchscreen *touchscreen) {
    return finger_is_any_input(&touchscreen->primary_touch) ||
        finger_is_any_input(&touchscreen->secondary_touch);
}