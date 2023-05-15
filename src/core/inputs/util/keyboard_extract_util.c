#define key_case(sdl_event, key)\
    case sdl_event:\
        set_key(key, event.type);\
        break;

void extract_keyboard(ecs_world_t *world, SDL_Event event) {
    if (!keyboard_entity || !ecs_is_alive(world, keyboard_entity)) return;
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        SDL_Keycode key = event.key.keysym.sym;
        Keyboard *keyboard = ecs_get_mut(world, keyboard_entity, Keyboard);
        switch(key) {
            key_case(SDLK_SPACE, &keyboard->space)
            key_case(SDLK_ESCAPE, &keyboard->escape)
            key_case(SDLK_RETURN, &keyboard->enter)
            key_case(SDLK_LALT, &keyboard->left_alt)
            key_case(SDLK_RALT, &keyboard->right_alt)
            key_case(SDLK_LSHIFT, &keyboard->left_shift)
            key_case(SDLK_RSHIFT, &keyboard->right_shift)
            key_case(SDLK_DOWN, &keyboard->down)
            key_case(SDLK_UP, &keyboard->up)
            key_case(SDLK_LEFT, &keyboard->left)
            key_case(SDLK_RIGHT, &keyboard->right)
            key_case(SDLK_a, &keyboard->a)
            key_case(SDLK_b, &keyboard->b)
            key_case(SDLK_c, &keyboard->c)
            key_case(SDLK_d, &keyboard->d)
            key_case(SDLK_e, &keyboard->e)
            key_case(SDLK_f, &keyboard->f)
            key_case(SDLK_g, &keyboard->g)
            key_case(SDLK_h, &keyboard->h)
            key_case(SDLK_i, &keyboard->i)
            key_case(SDLK_j, &keyboard->j)
            key_case(SDLK_k, &keyboard->k)
            key_case(SDLK_l, &keyboard->l)
            key_case(SDLK_m, &keyboard->m)
            key_case(SDLK_n, &keyboard->n)
            key_case(SDLK_o, &keyboard->o)
            key_case(SDLK_p, &keyboard->p)
            key_case(SDLK_q, &keyboard->q)
            key_case(SDLK_r, &keyboard->r)
            key_case(SDLK_s, &keyboard->s)
            key_case(SDLK_t, &keyboard->t)
            key_case(SDLK_u, &keyboard->u)
            key_case(SDLK_v, &keyboard->v)
            key_case(SDLK_w, &keyboard->w)
            key_case(SDLK_x, &keyboard->x)
            key_case(SDLK_y, &keyboard->y)
            key_case(SDLK_z, &keyboard->z)
            default:
                return;
        }
        ecs_modified(world, keyboard_entity, Keyboard);
    }
}

void print_keyboard_key(const PhysicalButton *key, char* name) {
    zoxel_log("    key %s [%s - %s - %s]\n", name, (key->pressed_this_frame ? "true" : "false"),
        (key->is_pressed ? "true" : "false"), (key->released_this_frame ? "true" : "false"));
}

void print_keyboard(ecs_world_t *world) {
    const Keyboard *keyboard = ecs_get(world, keyboard_entity, Keyboard);
    print_keyboard_key(&keyboard->space, "space");
    print_keyboard_key(&keyboard->p, "p");
    print_keyboard_key(&keyboard->w, "w");
}

void device_reset_keyboard(ecs_world_t *world, ecs_entity_t keyboard_entity) {
    if (!keyboard_entity || !ecs_is_alive(world, keyboard_entity)) return;
    ecs_defer_begin(world);
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
    ecs_defer_end(world);
}

/* else if (event.type == SDL_FINGERDOWN || event.type == SDL_FINGERUP) {
    //! Links touch events to space key press
    // todo: remove this part and create a touchscreen device
    Keyboard *keyboard = ecs_get_mut(world, keyboard_entity, Keyboard);
    PhysicalButton *key = &keyboard->space;
    key->pressed_this_frame = event.type == SDL_FINGERDOWN;
    key->released_this_frame = event.type == SDL_FINGERUP;
    if (key->pressed_this_frame) {
        key->is_pressed = 1;
    } else if (key->released_this_frame) {
        key->is_pressed = 0;
    }
    ecs_modified(world, keyboard_entity, Keyboard);
}*/