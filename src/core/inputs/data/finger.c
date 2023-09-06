/*typedef struct {
    PhysicalButton value;
    int2 position;
    int2 delta;
} Finger;

#define finger_zero (Finger) {\
    .value = (PhysicalButton) { 0, 0, 0 },\
    .position = int2_zero,\
    .delta = int2_zero\
}

unsigned char finger_is_any_input(const Finger *finger) {
    return finger->value.is_pressed;
}*/