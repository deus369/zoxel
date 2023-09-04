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

void device_reset_keyboard(ecs_world_t *world, ecs_entity_t keyboard_entity) {
    if (!keyboard_entity || !ecs_is_alive(world, keyboard_entity)) return;
    Keyboard *keyboard = ecs_get_mut(world, keyboard_entity, Keyboard);
    reset_key(&keyboard->space);
    reset_key(&keyboard->escape);
    reset_key(&keyboard->enter);
    reset_key(&keyboard->left_alt);
    reset_key(&keyboard->right_alt);
    reset_key(&keyboard->left_shift);
    reset_key(&keyboard->right_shift);
    reset_key(&keyboard->a);
    reset_key(&keyboard->b);
    reset_key(&keyboard->c);
    reset_key(&keyboard->d);
    reset_key(&keyboard->e);
    reset_key(&keyboard->f);
    reset_key(&keyboard->g);
    reset_key(&keyboard->h);
    reset_key(&keyboard->i);
    reset_key(&keyboard->j);
    reset_key(&keyboard->k);
    reset_key(&keyboard->l);
    reset_key(&keyboard->m);
    reset_key(&keyboard->n);
    reset_key(&keyboard->o);
    reset_key(&keyboard->p);
    reset_key(&keyboard->q);
    reset_key(&keyboard->r);
    reset_key(&keyboard->s);
    reset_key(&keyboard->t);
    reset_key(&keyboard->u);
    reset_key(&keyboard->v);
    reset_key(&keyboard->w);
    reset_key(&keyboard->x);
    reset_key(&keyboard->y);
    reset_key(&keyboard->z);
    reset_key(&keyboard->down);
    reset_key(&keyboard->up);
    reset_key(&keyboard->left);
    reset_key(&keyboard->right);
    ecs_modified(world, keyboard_entity, Keyboard);
}

void print_keyboard_key(const PhysicalButton *key, char* name) {
    zoxel_log("    key %s [%s - %s - %s]\n", name, (key->pressed_this_frame ? "true" : "false"), (key->is_pressed ? "true" : "false"), (key->released_this_frame ? "true" : "false"));
}

void print_keyboard(ecs_world_t *world, ecs_entity_t keyboard_entity) {
    const Keyboard *keyboard = ecs_get(world, keyboard_entity, Keyboard);
    print_keyboard_key(&keyboard->space, "space");
    print_keyboard_key(&keyboard->p, "p");
    print_keyboard_key(&keyboard->w, "w");
}

// todo: use a hashmap with keys keyboard->keys['a'] for more dynamic access