#define reset_keyboard_key(key) reset_key(&keyboard->key);

void reset_keyboard(Keyboard *keyboard) {
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
    reset_keyboard_key(f1)
    reset_keyboard_key(f2)
    reset_keyboard_key(f3)
    reset_keyboard_key(f4)
    reset_keyboard_key(f5)
    reset_keyboard_key(f7)
    reset_keyboard_key(f8)
    reset_keyboard_key(f9)
    reset_keyboard_key(f10)
    reset_keyboard_key(f11)
    reset_keyboard_key(f12)
    reset_keyboard_key(_1)
    reset_keyboard_key(_2)
    reset_keyboard_key(_3)
    reset_keyboard_key(_4)
    reset_keyboard_key(_5)
    reset_keyboard_key(_6)
    reset_keyboard_key(_7)
    reset_keyboard_key(_8)
    reset_keyboard_key(_9)
    reset_keyboard_key(_0)
}

void KeyboardResetSystem(iter *it) {
    zox_sys_begin()
    zox_sys_out(Keyboard)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(Keyboard, keyboard)
        reset_keyboard(keyboard);
    }
} zox_declare_system(KeyboardResetSystem)