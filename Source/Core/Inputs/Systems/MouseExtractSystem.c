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
    /*if (!mouseEntity || !ecs_is_alive(world, mouseEntity))
    {
        return;
    }
    Mouse *mouse = ecs_get_mut(world, mouseEntity, Mouse);
    ResetKey(&mouse->left);
    ResetKey(&mouse->middle);
    ResetKey(&mouse->right);
    ecs_modified(world, mouseEntity, Mouse);*/
}

//! Converts a bool state to using a few bools, to get starting ending frame states of a key press.
void SetMouseKey(PhysicalButton *key, bool keyDown)
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
}

//! Extract Key Events from SDL and set them on entities keyboad.
void ExtractMouse(ecs_world_t *world)
{
    if (!mouseEntity || !ecs_is_alive(world, mouseEntity))
    {
        return;
    }
    SDL_PumpEvents();  // make sure we have the latest mouse state.
    Mouse *mouse = ecs_get_mut(world, mouseEntity, Mouse);
    int2 oldMousePosition = mouse->position;
    Uint32 buttons = SDL_GetMouseState(&mouse->position.x, &mouse->position.y);
    mouse->delta.x = mouse->position.x - oldMousePosition.x;
    mouse->delta.y = mouse->position.y - oldMousePosition.y;
    SetMouseKey(&mouse->left, (buttons & SDL_BUTTON_LMASK) != 0);
    SetMouseKey(&mouse->middle, (buttons & SDL_BUTTON_MMASK) != 0);
    SetMouseKey(&mouse->right, (buttons & SDL_BUTTON_RMASK) != 0);
    ecs_modified(world, mouseEntity, Mouse);
}