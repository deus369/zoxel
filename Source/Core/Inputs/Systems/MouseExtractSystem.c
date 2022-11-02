//! Grabs mouse data from SDL.

ecs_entity_t mouseEntity;

void SpawnMouseEntity()
{
    mouseEntity = ecs_new_entity(world, "mouse");
    ecs_set(world, mouseEntity, Mouse, { });
    printf("Spawned Mouse [%lu]\n", (long unsigned int) mouseEntity);
    // return mouseEntity;
}

void ResetMouse(ecs_world_t *world)
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
    ecs_modified(world, mouseEntity, Mouse);
}

//! Converts a bool state to using a few bools, to get starting ending frame states of a key press.
/*void SetMouseKey(PhysicalButton *key, bool keyDown)
{
    if (keyDown)
    {
        if (!key->isPressed)
        {
            // printf("Mouse Button is pressed.\n");
            key->wasPressedThisFrame = true;
        }
        else
        {
            key->wasPressedThisFrame = false;
        }
        key->isPressed = true;
    }
    else
    {
        if (key->isPressed)
        {
            key->isPressed = false;
            key->wasReleasedThisFrame = true;
        }
        key->wasPressedThisFrame = false;
    }
}*/

//! Extract mouse positino.
void ExtractMouse(ecs_world_t *world)
{
    if (!mouseEntity || !ecs_is_alive(world, mouseEntity))
    {
        return;
    }
    SDL_PumpEvents();  // make sure we have the latest mouse state.
    Mouse *mouse = ecs_get_mut(world, mouseEntity, Mouse);
    int2 oldMousePosition = mouse->position;
    SDL_GetMouseState(&mouse->position.x, &mouse->position.y);  // Uint32 buttons = 
    mouse->delta.x = mouse->position.x - oldMousePosition.x;
    mouse->delta.y = mouse->position.y - oldMousePosition.y;
    /*SetMouseKey(&mouse->left, (buttons & SDL_BUTTON_LMASK) != 0);
    SetMouseKey(&mouse->middle, (buttons & SDL_BUTTON_MMASK) != 0);
    SetMouseKey(&mouse->right, (buttons & SDL_BUTTON_RMASK) != 0);*/
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

void ExtractMouseEvent(ecs_world_t *world, SDL_Event event)
{
    if (!mouseEntity || !ecs_is_alive(world, mouseEntity))
    {
        return;
    }
    int eventType = event.type;
    if (eventType == SDL_MOUSEBUTTONDOWN || eventType == SDL_MOUSEBUTTONUP || eventType == SDL_MOUSEWHEEL)
    {
        // SDL_Keycode key = event.key.keysym.sym;
        Mouse *mouse = ecs_get_mut(world, mouseEntity, Mouse);
        if (eventType == SDL_MOUSEBUTTONDOWN || eventType == SDL_MOUSEBUTTONUP)
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