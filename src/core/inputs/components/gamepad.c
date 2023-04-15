typedef struct {
    PhysicalButton a;
    PhysicalButton b;
    PhysicalButton x;
    PhysicalButton y;
    PhysicalButton lb;
    PhysicalButton rb;
    PhysicalButton lt;
    PhysicalButton rt;
    PhysicalButton start;
    PhysicalButton select;
    PhysicalButton left_stick_push;
    PhysicalButton right_stick_push;
    PhysicalStick left_stick;
    PhysicalStick right_stick;
} Gamepad;
zoxel_custom_component(Gamepad)

#define gamepad_zero {\
    .a = { 0, 0, 0 },\
    .b = { 0, 0, 0 },\
    .x = { 0, 0, 0 },\
    .y = { 0, 0, 0 },\
    .lb = { 0, 0, 0 },\
    .rb = { 0, 0, 0 },\
    .lt = { 0, 0, 0 },\
    .rt = { 0, 0, 0 },\
    .start = { 0, 0, 0 },\
    .select = { 0, 0, 0 },\
    .left_stick_push = { 0, 0, 0 },\
    .right_stick_push = { 0, 0, 0 },\
    .left_stick = { float2_zero },\
    .right_stick = { float2_zero }\
}

// todo: Add axis data - joysticks