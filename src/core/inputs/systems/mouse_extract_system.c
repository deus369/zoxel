//! Grabs mouse data from SDL.

ecs_entity_t mouseEntity;

void spawn_mouse_entity(ecs_world_t *world)
{
    mouseEntity = ecs_new_entity(world, "mouse");
    ecs_set(world, mouseEntity, Mouse, { });
    printf("Spawned Mouse [%lu]\n", (long unsigned int) mouseEntity);
    // return mouseEntity;
}

void reset_mouse(ecs_world_t *world)
{
    if (!mouseEntity || !ecs_is_alive(world, mouseEntity))
    {
        return;
    }
    Mouse *mouse = ecs_get_mut(world, mouseEntity, Mouse);
    ResetKey(&mouse->left);
    ResetKey(&mouse->middle);
    ResetKey(&mouse->right);
    mouse->wheel = (int2) { 0, 0 };
    mouse->delta = (int2) { 0, 0 };
    ecs_modified(world, mouseEntity, Mouse);
}

void SetMouseKey(PhysicalButton *key, int eventType)
{
    bool keyDown = eventType == SDL_MOUSEBUTTONDOWN;
    bool keyReleased = eventType == SDL_MOUSEBUTTONUP;
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

void extract_mouse(ecs_world_t *world, SDL_Event event)
{
    if (!mouseEntity || !ecs_is_alive(world, mouseEntity))
    {
        return;
    }
    int eventType = event.type;
    if (eventType == SDL_MOUSEBUTTONDOWN || eventType == SDL_MOUSEBUTTONUP || eventType == SDL_MOUSEWHEEL || eventType == SDL_MOUSEMOTION)
    {
        // SDL_Keycode key = event.key.keysym.sym;
        Mouse *mouse = ecs_get_mut(world, mouseEntity, Mouse);
        if (eventType == SDL_MOUSEMOTION)
        {
            mouse->position = (int2) { event.motion.x, event.motion.y };
            mouse->delta = (int2) { event.motion.xrel, event.motion.yrel };
        }
        else if (eventType == SDL_MOUSEBUTTONDOWN || eventType == SDL_MOUSEBUTTONUP)
        {
            SDL_MouseButtonEvent *mouseEvent = &event.button;
            Uint8 button = mouseEvent->button;
            if (button == SDL_BUTTON_LEFT)
            {
                SetMouseKey(&mouse->left, eventType);
            }
            else if (button == SDL_BUTTON_MIDDLE)
            {
                SetMouseKey(&mouse->middle, eventType);
            }
            else if (button == SDL_BUTTON_RIGHT)
            {
                SetMouseKey(&mouse->right, eventType);
            }
        }
        else if (eventType == SDL_MOUSEWHEEL)
        {
            mouse->wheel = (int2) { event.wheel.x, event.wheel.y };
        }
        ecs_modified(world, mouseEntity, Mouse);
    }
}