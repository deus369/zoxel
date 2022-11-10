//! Grabs keyboard data from SDL.

ecs_entity_t keyboardEntity;
// forward declarations
bool wasPressedThisFrame = false;
void SetKey(PhysicalButton *key, int eventType);
void ResetKey(PhysicalButton *key);

void spawn_keyboard_entity(ecs_world_t *world)
{
    keyboardEntity = ecs_new_entity(world, "keyboard");
    // ecs_add(world, keyboardEntity, Keyboard);
    ecs_set(world, keyboardEntity, Keyboard, { });
    printf("Spawned Keyboard [%lu]\n", (long unsigned int) keyboardEntity);
    // return keyboardEntity;
}

void reset_keyboard(ecs_world_t *world)
{
    if (!keyboardEntity || !ecs_is_alive(world, keyboardEntity))
    {
        return;
    }
    Keyboard *keyboard = ecs_get_mut(world, keyboardEntity, Keyboard);
    ResetKey(&keyboard->space);
    ResetKey(&keyboard->escape);
    ResetKey(&keyboard->a);
    ResetKey(&keyboard->b);
    ResetKey(&keyboard->r);
    ResetKey(&keyboard->d);
    ResetKey(&keyboard->e);
    ResetKey(&keyboard->f);
    ResetKey(&keyboard->g);
    ResetKey(&keyboard->h);
    ResetKey(&keyboard->i);
    ResetKey(&keyboard->j);
    ResetKey(&keyboard->k);
    ResetKey(&keyboard->l);
    ResetKey(&keyboard->m);
    ResetKey(&keyboard->n);
    ResetKey(&keyboard->o);
    ResetKey(&keyboard->p);
    ResetKey(&keyboard->q);
    ResetKey(&keyboard->r);
    ResetKey(&keyboard->s);
    ResetKey(&keyboard->t);
    ResetKey(&keyboard->u);
    ResetKey(&keyboard->v);
    ResetKey(&keyboard->w);
    ResetKey(&keyboard->x);
    ResetKey(&keyboard->y);
    ResetKey(&keyboard->z);
    ResetKey(&keyboard->down);
    ResetKey(&keyboard->up);
    ResetKey(&keyboard->left);
    ResetKey(&keyboard->right);
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
            case SDLK_SPACE:
                SetKey(&keyboard->space, eventType);
                break;
            case SDLK_ESCAPE:
                SetKey(&keyboard->escape, eventType);
                break;
            case SDLK_a:
                SetKey(&keyboard->a, eventType);
                break;
            case SDLK_b:
                SetKey(&keyboard->b, eventType);
                break;
            case SDLK_c:
                SetKey(&keyboard->c, eventType);
                break;
            case SDLK_d:
                SetKey(&keyboard->d, eventType);
                break;
            case SDLK_e:
                SetKey(&keyboard->e, eventType);
                break;
            case SDLK_f:
                SetKey(&keyboard->f, eventType);
                break;
            case SDLK_g:
                SetKey(&keyboard->g, eventType);
                break;
            case SDLK_h:
                SetKey(&keyboard->h, eventType);
                break;
            case SDLK_i:
                SetKey(&keyboard->i, eventType);
                break;
            case SDLK_j:
                SetKey(&keyboard->j, eventType);
                break;
            case SDLK_k:
                SetKey(&keyboard->k, eventType);
                break;
            case SDLK_l:
                SetKey(&keyboard->l, eventType);
                break;
            case SDLK_m:
                SetKey(&keyboard->m, eventType);
                break;
            case SDLK_n:
                SetKey(&keyboard->n, eventType);
                break;
            case SDLK_o:
                SetKey(&keyboard->o, eventType);
                break;
            case SDLK_p:
                SetKey(&keyboard->p, eventType);
                break;
            case SDLK_q:
                SetKey(&keyboard->q, eventType);
                break;
            case SDLK_r:
                SetKey(&keyboard->r, eventType);
                break;
            case SDLK_s:
                SetKey(&keyboard->s, eventType);
                break;
            case SDLK_t:
                SetKey(&keyboard->t, eventType);
                break;
            case SDLK_u:
                SetKey(&keyboard->u, eventType);
                break;
            case SDLK_v:
                SetKey(&keyboard->v, eventType);
                break;
            case SDLK_w:
                SetKey(&keyboard->w, eventType);
                break;
            case SDLK_x:
                SetKey(&keyboard->x, eventType);
                break;
            case SDLK_y:
                SetKey(&keyboard->y, eventType);
                break;
            case SDLK_z:
                SetKey(&keyboard->z, eventType);
                break;
            case SDLK_DOWN:
                SetKey(&keyboard->down, eventType);
                break;
            case SDLK_UP:
                SetKey(&keyboard->up, eventType);
                break;
            case SDLK_LEFT:
                SetKey(&keyboard->left, eventType);
                break;
            case SDLK_RIGHT:
                SetKey(&keyboard->right, eventType);
                break;
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
    key->wasPressedThisFrame = keyDown;
    key->wasReleasedThisFrame = keyReleased;
    if (keyDown)
    {
        key->isPressed = true;
    }
    else if (keyReleased)
    {
        key->isPressed = false;
    }
}

void ResetKey(PhysicalButton *key)
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