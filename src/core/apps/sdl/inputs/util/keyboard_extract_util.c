#if defined(zox_test_game_keys)
    extern void button_event_play_game(ecs_world_t *world, ecs_entity_t trigger_entity);
    extern void button_event_end_game(ecs_world_t *world, ecs_entity_t trigger_entity);
    extern void button_event_exit_app(ecs_world_t *world, ecs_entity_t trigger_entity);
    extern void toggle_pause_ui(ecs_world_t *world, ecs_entity_t player);
#endif

#define sdl_key_case(sdl_event, key)\
    case sdl_event:\
        set_sdl_key(key, event.type);\
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
            default:
                return;
        }
        zox_modified(keyboard_entity, Keyboard)
        #if defined(zox_test_game_keys)
            if (keyboard->t.pressed_this_frame) button_event_play_game(world, 0);
            if (keyboard->y.pressed_this_frame) toggle_pause_ui(world, main_player);
            if (keyboard->u.pressed_this_frame) button_event_end_game(world, 0);
            if (keyboard->i.pressed_this_frame) button_event_exit_app(world, 0);
        #endif
    }
}
