//! Grabs keyboard data from SDL.

#define key_case(sdl_event, key)\
            case sdl_event:\
                set_key(key, eventType);\
                break;

void set_key(PhysicalButton *key, int eventType) {
    unsigned char keyDown = eventType == SDL_KEYDOWN;
    unsigned char keyReleased = eventType == SDL_KEYUP;
    if (!key->is_pressed && keyDown) {
        key->pressed_this_frame = 1;
    }
    if (key->is_pressed && keyReleased) {
        key->released_this_frame = 1;
    }
    key->is_pressed = keyDown;
}

//! Extract Key Events from SDL and set them on entities keyboad.
void extract_keyboard(ecs_world_t *world, SDL_Event event) {
    if (!keyboard_entity || !ecs_is_alive(world, keyboard_entity)) {
        return;
    }
    int eventType = event.type;
    //! Links touch events to space key press
    if (eventType == SDL_FINGERDOWN || eventType == SDL_FINGERUP) {
        Keyboard *keyboard = ecs_get_mut(world, keyboard_entity, Keyboard);
        PhysicalButton *key = &keyboard->space;
        key->pressed_this_frame = eventType == SDL_FINGERDOWN;
        key->released_this_frame = eventType == SDL_FINGERUP;
        if (key->pressed_this_frame) {
            key->is_pressed = 1;
        } else if (key->released_this_frame) {
            key->is_pressed = 0;
        }
        ecs_modified(world, keyboard_entity, Keyboard);
    } else if (eventType == SDL_KEYDOWN || eventType == SDL_KEYUP) {
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

void PrintKey(const PhysicalButton *key, char* name) {
    printf("    key %s [%s - %s - %s]\n", name,
        (key->pressed_this_frame ? "true" : "false"),
        (key->is_pressed ? "true" : "false"),
        (key->released_this_frame ? "true" : "false"));
}

void PrintKeyboard(ecs_world_t *world) {
    const Keyboard *keyboard = ecs_get(world, keyboard_entity, Keyboard);
    PrintKey(&keyboard->space, "space");
    PrintKey(&keyboard->p, "p");
    PrintKey(&keyboard->w, "w");
}