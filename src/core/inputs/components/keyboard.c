typedef struct {
    PhysicalButton enter;
    PhysicalButton space;
    PhysicalButton escape;
    PhysicalButton backspace;
    PhysicalButton left_control;
    PhysicalButton right_control;
    PhysicalButton left_shift;
    PhysicalButton right_shift;
    PhysicalButton left_alt;
    PhysicalButton right_alt;
    PhysicalButton tab;
    PhysicalButton capslock;
    PhysicalButton a;
    PhysicalButton b;
    PhysicalButton c;
    PhysicalButton d;
    PhysicalButton e;
    PhysicalButton f;
    PhysicalButton g;
    PhysicalButton h;
    PhysicalButton i;
    PhysicalButton j;
    PhysicalButton k;
    PhysicalButton l;
    PhysicalButton m;
    PhysicalButton n;
    PhysicalButton o;
    PhysicalButton p;
    PhysicalButton q;
    PhysicalButton r;
    PhysicalButton s;
    PhysicalButton t;
    PhysicalButton u;
    PhysicalButton v;
    PhysicalButton w;
    PhysicalButton x;
    PhysicalButton y;
    PhysicalButton z;
    PhysicalButton _0;
    PhysicalButton _1;
    PhysicalButton _2;
    PhysicalButton _3;
    PhysicalButton _4;
    PhysicalButton _5;
    PhysicalButton _6;
    PhysicalButton _7;
    PhysicalButton _8;
    PhysicalButton _9;
    PhysicalButton down;
    PhysicalButton up;
    PhysicalButton left;
    PhysicalButton right;
} Keyboard;
zox_custom_component(Keyboard)

unsigned char keyboard_is_any_input(const Keyboard *keyboard) {
    return (keyboard->enter.is_pressed ||
        keyboard->backspace.is_pressed ||
        keyboard->w.is_pressed ||
        keyboard->a.is_pressed ||
        keyboard->s.is_pressed ||
        keyboard->d.is_pressed ||
        keyboard->space.is_pressed);
}

// todo: use a hashmap with keys keyboard->keys['a'] for more dynamic access