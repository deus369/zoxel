#if defined(zox_test_game_keys)
    extern void button_event_play_game(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element);
    extern void button_event_end_game(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element);
    extern void button_event_exit_app(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element);
    extern void (ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element);
#endif

void set_sdl_key(ecs_world_t *world, PhysicalButton *key, SDL_Keycode keycode, SDL_EventType event_type) {
    byte key_down = event_type == SDL_KEYDOWN;
    byte key_released = event_type == SDL_KEYUP;
    if (!key->is_pressed && key_down) {
        key->pressed_this_frame = 1;
        run_hook_key_down(world, (int32_t) keycode);
    }
    if (key->is_pressed && key_released) {
        key->released_this_frame = 1;
    }
    key->is_pressed = key_down;
}

#define sdl_key_case(sdl_event, key)\
    case sdl_event:\
        set_sdl_key(world, key, sdl_event, event.type);\
        break;

void sdl_extract_keyboard(ecs_world_t *world, SDL_Event event) {
    if (!keyboard_entity || !ecs_is_alive(world, keyboard_entity)) return;
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        SDL_Keycode key = event.key.keysym.sym;
        Keyboard *keyboard = zox_get_mut(keyboard_entity, Keyboard)
        switch(key) {
            sdl_key_case(SDLK_SPACE, &keyboard->space)
            sdl_key_case(SDLK_ESCAPE, &keyboard->escape)
            sdl_key_case(SDLK_RETURN, &keyboard->enter)
            sdl_key_case(SDLK_LALT, &keyboard->left_alt)
            sdl_key_case(SDLK_RALT, &keyboard->right_alt)
            sdl_key_case(SDLK_LSHIFT, &keyboard->left_shift)
            sdl_key_case(SDLK_RSHIFT, &keyboard->right_shift)
            sdl_key_case(SDLK_DOWN, &keyboard->down)
            sdl_key_case(SDLK_UP, &keyboard->up)
            sdl_key_case(SDLK_LEFT, &keyboard->left)
            sdl_key_case(SDLK_RIGHT, &keyboard->right)
            sdl_key_case(SDLK_a, &keyboard->a)
            sdl_key_case(SDLK_b, &keyboard->b)
            sdl_key_case(SDLK_c, &keyboard->c)
            sdl_key_case(SDLK_d, &keyboard->d)
            sdl_key_case(SDLK_e, &keyboard->e)
            sdl_key_case(SDLK_f, &keyboard->f)
            sdl_key_case(SDLK_g, &keyboard->g)
            sdl_key_case(SDLK_h, &keyboard->h)
            sdl_key_case(SDLK_i, &keyboard->i)
            sdl_key_case(SDLK_j, &keyboard->j)
            sdl_key_case(SDLK_k, &keyboard->k)
            sdl_key_case(SDLK_l, &keyboard->l)
            sdl_key_case(SDLK_m, &keyboard->m)
            sdl_key_case(SDLK_n, &keyboard->n)
            sdl_key_case(SDLK_o, &keyboard->o)
            sdl_key_case(SDLK_p, &keyboard->p)
            sdl_key_case(SDLK_q, &keyboard->q)
            sdl_key_case(SDLK_r, &keyboard->r)
            sdl_key_case(SDLK_s, &keyboard->s)
            sdl_key_case(SDLK_t, &keyboard->t)
            sdl_key_case(SDLK_u, &keyboard->u)
            sdl_key_case(SDLK_v, &keyboard->v)
            sdl_key_case(SDLK_w, &keyboard->w)
            sdl_key_case(SDLK_x, &keyboard->x)
            sdl_key_case(SDLK_y, &keyboard->y)
            sdl_key_case(SDLK_z, &keyboard->z)
            sdl_key_case(SDLK_F1, &keyboard->f1)
            sdl_key_case(SDLK_F2, &keyboard->f2)
            sdl_key_case(SDLK_F3, &keyboard->f3)
            sdl_key_case(SDLK_F4, &keyboard->f4)
            sdl_key_case(SDLK_F5, &keyboard->f5)
            sdl_key_case(SDLK_F6, &keyboard->f6)
            sdl_key_case(SDLK_F7, &keyboard->f7)
            sdl_key_case(SDLK_F8, &keyboard->f8)
            sdl_key_case(SDLK_F9, &keyboard->f9)
            sdl_key_case(SDLK_F10, &keyboard->f10)
            sdl_key_case(SDLK_F11, &keyboard->f11)
            sdl_key_case(SDLK_F12, &keyboard->f12)
            sdl_key_case(SDLK_1, &keyboard->_1)
            sdl_key_case(SDLK_2, &keyboard->_2)
            sdl_key_case(SDLK_3, &keyboard->_3)
            sdl_key_case(SDLK_4, &keyboard->_4)
            sdl_key_case(SDLK_5, &keyboard->_5)
            sdl_key_case(SDLK_6, &keyboard->_6)
            sdl_key_case(SDLK_7, &keyboard->_7)
            sdl_key_case(SDLK_8, &keyboard->_8)
            sdl_key_case(SDLK_9, &keyboard->_9)
            sdl_key_case(SDLK_0, &keyboard->_0)
            default:
                return;
        }
        zox_modified(keyboard_entity, Keyboard)
#if defined(zox_test_game_keys)
        if (keyboard->t.pressed_this_frame) button_event_play_game(world, 0);
        if (keyboard->y.pressed_this_frame) (world, main_player);
        if (keyboard->u.pressed_this_frame) button_event_end_game(world, 0);
        if (keyboard->i.pressed_this_frame) button_event_exit_app(world, 0);
#endif
    }
}
