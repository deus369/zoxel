// #include "../../../Imports/Flecs/flecs.h"

ecs_entity_t keyboardEntity;
// forward declarations
bool wasPressedThisFrame = false;
void SetKey(PhysicalButton *key, int eventType);
void ResetKey(PhysicalButton *key);

void InitializeKeyboardExtractSystem(ecs_world_t *world)
{
    keyboardEntity = ecs_new_entity(world, "keyboard");
    ecs_add(world, keyboardEntity, Keyboard);
    printf("Keyboard is ALIVE: %lu \n", keyboardEntity);
}

void ResetKeyboard(ecs_world_t *world)
{
    Keyboard *keyboard = ecs_get_mut(world, keyboardEntity, Keyboard);
    ResetKey(&keyboard->space);
    ResetKey(&keyboard->escape);
    ResetKey(&keyboard->a);
    ResetKey(&keyboard->d);
    ResetKey(&keyboard->s);
    ResetKey(&keyboard->p);
    ResetKey(&keyboard->w);
    ecs_modified(world, keyboardEntity, Keyboard);
}

//! Extract Key Events from SDL and set them on entities keyboad.
void ExtractIntoKeyboard(ecs_world_t *world, SDL_Event event)
{
    int eventType = event.type;
    if (eventType == SDL_KEYDOWN || eventType == SDL_KEYUP)
    {
        SDL_Keycode key = event.key.keysym.sym;
        Keyboard *keyboard = ecs_get_mut(world, keyboardEntity, Keyboard);
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
        else if (key == SDLK_p)
        {
            SetKey(&keyboard->p, eventType);
        }
        else if (key == SDLK_s)
        {
            SetKey(&keyboard->s, eventType);
        }
        else if (key == SDLK_w)
        {
            SetKey(&keyboard->w, eventType);
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