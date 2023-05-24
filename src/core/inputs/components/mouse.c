typedef struct {
    PhysicalButton left;
    PhysicalButton middle;
    PhysicalButton right;
    int2 position;
    int2 delta;
    int2 wheel;
} Mouse;
zox_custom_component(Mouse)

#define mouse_zero {\
    .left = (PhysicalButton) { 0, 0, 0 },\
    .middle = (PhysicalButton) { 0, 0, 0 },\
    .right = (PhysicalButton) { 0, 0, 0 },\
    .position = (int2) { 0, 0 },\
    .delta = (int2) { 0, 0 },\
    .wheel = (int2) { 0, 0 }\
}

unsigned char mouse_is_any_input(const Mouse *mouse) {
    return (mouse->left.is_pressed ||
        mouse->middle.is_pressed ||
        mouse->right.is_pressed ||
        mouse->delta.x != 0 ||
        mouse->delta.y != 0 ||
        mouse->wheel.x != 0 ||
        mouse->wheel.y != 0);
}