//! A gamepad representation. \todo Add axis data.
typedef struct
{
    PhysicalButton a;
    PhysicalButton b;
    PhysicalButton x;
    PhysicalButton y;
    PhysicalButton rb;
    PhysicalButton rs;
    PhysicalButton lb;
    PhysicalButton ls;
    PhysicalButton start;
    PhysicalButton select;
    PhysicalButton left_joystick_push;
    PhysicalButton right_joystick_push;
} Gamepad;
ECS_COMPONENT_DECLARE(Gamepad);