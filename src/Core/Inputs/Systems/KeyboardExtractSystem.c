// #include "../../../Imports/Flecs/flecs.h"

ecs_entity_t keyboardEntity;

// forward declarations

ecs_entity_t SpawnKeyboadEntity(ecs_world_t *world)
{
    ECS_COMPONENT(world, Keyboard);
    ecs_entity_t e = ecs_new_entity(world, "");
    ecs_add(world, e, Keyboard);
    keyboardEntity = e;
    return e ;
}

void ResetKey(PhysicalButton *key)
{
    key->wasPressedThisFrame = false;
    key->wasReleasedThisFrame = false;
}

void ResetKeyboard(ecs_world_t *world)
{
    ECS_COMPONENT(world, Keyboard);
    Keyboard *keyboard = ecs_get(world, keyboardEntity, Keyboard);
    ResetKey(&keyboard->space);
    ResetKey(&keyboard->escape);
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

//! Extract Key Events from SDL and set them on entities keyboad.
void ExtractIntoKeyboard(ecs_world_t *world, SDL_Event event)
{
    ECS_COMPONENT(world, Keyboard);
    int eventType = event.type;
    if (eventType == SDL_KEYDOWN || eventType == SDL_KEYDOWN)
    {
        Keyboard *keyboard = ecs_get(world, keyboardEntity, Keyboard);
        SDL_Keycode key = event.key.keysym.sym;
        if (key == SDLK_SPACE) 
        {
            SetKey(&keyboard->space, eventType);
        }
        else if (key == SDLK_ESCAPE)
        {
            SetKey(&keyboard->escape, eventType);
        }
        else if (key == SDLK_a)
        {
            SetKey(&keyboard->a, eventType);
        }
        else if (key == SDLK_d)
        {
            SetKey(&keyboard->d, eventType);
        }
        else if (key == SDLK_s)
        {
            SetKey(&keyboard->s, eventType);
        }
        else if (key == SDLK_w)
        {
            SetKey(&keyboard->w, eventType);
        }
    }
}

void PrintKeyboard(ecs_world_t *world)
{
    ECS_COMPONENT(world, Keyboard);
    const Keyboard *keyboard = ecs_get(world, keyboardEntity, Keyboard);
    printf("keyboard [%s - %s - %s]\n",
        (keyboard->space.wasPressedThisFrame ? "true" : "false"),
        (keyboard->space.isPressed ? "true" : "false"),
        (keyboard->space.wasReleasedThisFrame ? "true" : "false"));
}