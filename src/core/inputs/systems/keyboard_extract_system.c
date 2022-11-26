//! Grabs keyboard data from SDL.

ecs_entity_t keyboardEntity;
// forward declarations
bool wasPressedThisFrame = false;
void SetKey(PhysicalButton *key, int eventType);
void reset_key(PhysicalButton *key);

#define key_case(sdl_event, key)\
            case sdl_event:\
                SetKey(key, eventType);\
                break;

void spawn_keyboard(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_entity(world, "keyboard");
    // ecs_add(world, keyboardEntity, Keyboard);
    ecs_set(world, e, Keyboard, { });
    // printf("Spawned Keyboard [%lu]\n", (long unsigned int) keyboardEntity);
    // return keyboardEntity;
    keyboardEntity = e;
}

void reset_keyboard(ecs_world_t *world)
{
    if (!keyboardEntity || !ecs_is_alive(world, keyboardEntity))
    {
        return;
    }
    Keyboard *keyboard = ecs_get_mut(world, keyboardEntity, Keyboard);
    reset_key(&keyboard->space);
    reset_key(&keyboard->escape);
    reset_key(&keyboard->enter);
    reset_key(&keyboard->left_alt);
    reset_key(&keyboard->right_alt);
    reset_key(&keyboard->a);
    reset_key(&keyboard->b);
    reset_key(&keyboard->r);
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
    ecs_modified(world, keyboardEntity, Keyboard);
}

//! Extract Key Events from SDL and set them on entities keyboad.
void extract_keyboard(ecs_world_t *world, SDL_Event event)
{
    if (!keyboardEntity || !ecs_is_alive(world, keyboardEntity))
    {
        return;
    }
    int eventType = event.type;
    //! Links touch events to space key press
    if (eventType == SDL_FINGERDOWN || eventType == SDL_FINGERUP)
    {
        Keyboard *keyboard = ecs_get_mut(world, keyboardEntity, Keyboard);
        PhysicalButton *key = &keyboard->space;
        key->wasPressedThisFrame = eventType == SDL_FINGERDOWN;
        key->wasReleasedThisFrame = eventType == SDL_FINGERUP;
        if (key->wasPressedThisFrame)
        {
            key->isPressed = true;
        }
        else if (key->wasReleasedThisFrame)
        {
            key->isPressed = false;
        }
        ecs_modified(world, keyboardEntity, Keyboard);
    }
    else if (eventType == SDL_KEYDOWN || eventType == SDL_KEYUP)
    {
        SDL_Keycode key = event.key.keysym.sym;
        Keyboard *keyboard = ecs_get_mut(world, keyboardEntity, Keyboard);
        switch(key)
        {
            key_case(SDLK_SPACE, &keyboard->space)
            key_case(SDLK_ESCAPE, &keyboard->escape)
            key_case(SDLK_RETURN, &keyboard->enter)
            key_case(SDLK_LALT, &keyboard->left_alt)
            key_case(SDLK_RALT, &keyboard->right_alt)
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
        ecs_modified(world, keyboardEntity, Keyboard);
    }
}

void SetKey(PhysicalButton *key, int eventType)
{
    bool keyDown = eventType == SDL_KEYDOWN;
    bool keyReleased = eventType == SDL_KEYUP;
    if (!key->isPressed && keyDown)
    {
        key->wasPressedThisFrame = true;
    }
    if (key->isPressed && keyReleased)
    {
        key->wasReleasedThisFrame = true;
    }
    key->isPressed = keyDown;
}

void reset_key(PhysicalButton *key)
{
    if (key->wasPressedThisFrame)
    {
        key->wasPressedThisFrame = false;
    }
    if (key->wasReleasedThisFrame)
    {
        key->wasReleasedThisFrame = false;
    }
}

void PrintKey(const PhysicalButton *key, char* name)
{
    printf("    key %s [%s - %s - %s]\n", name,
        (key->wasPressedThisFrame ? "true" : "false"),
        (key->isPressed ? "true" : "false"),
        (key->wasReleasedThisFrame ? "true" : "false"));
}

void PrintKeyboard(ecs_world_t *world)
{
    const Keyboard *keyboard = ecs_get(world, keyboardEntity, Keyboard);
    PrintKey(&keyboard->space, "space");
    PrintKey(&keyboard->p, "p");
    PrintKey(&keyboard->w, "w");
}