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
    PhysicalButton f1;
    PhysicalButton f2;
    PhysicalButton f3;
    PhysicalButton f4;
    PhysicalButton f5;
    PhysicalButton f6;
    PhysicalButton f7;
    PhysicalButton f8;
    PhysicalButton f9;
    PhysicalButton f10;
    PhysicalButton f11;
    PhysicalButton f12;
} Keyboard;
zoxc_custom(Keyboard);

byte keyboard_is_any_input(const Keyboard *keyboard) {
    return (keyboard->enter.is_pressed || keyboard->backspace.is_pressed || keyboard->space.is_pressed ||
        keyboard->w.is_pressed || keyboard->a.is_pressed || keyboard->s.is_pressed || keyboard->d.is_pressed);
}

void print_keyboard_key(const PhysicalButton *key, char* name) {
    zox_log("    key %s [%s - %s - %s]\n", name, (key->pressed_this_frame ? "true" : "false"), (key->is_pressed ? "true" : "false"), (key->released_this_frame ? "true" : "false"))
}

void print_keyboard(ecs *world, entity local_keyboard) {
    const Keyboard *keyboard = zox_get(local_keyboard, Keyboard)
    print_keyboard_key(&keyboard->space, "space");
    print_keyboard_key(&keyboard->p, "p");
    print_keyboard_key(&keyboard->w, "w");
}
