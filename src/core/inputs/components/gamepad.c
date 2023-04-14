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

// todo: Add axis data - joysticks