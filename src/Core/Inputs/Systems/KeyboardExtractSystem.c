// #include "../../../Imports/Flecs/flecs.h"

ecs_entity_t keyboardEntity;
// forward declarations
bool wasPressedThisFrame = false;
void SetKey(PhysicalButton *key, int eventType);
void ResetKey(PhysicalButton *key);

void InitializeKeyboardExtractSystem(ecs_world_t *world)
{
    keyboardEntity = ecs_new_entity(world, "keyboard");
    // ecs_add(world, keyboardEntity, Keyboard);
    ecs_set(world, keyboardEntity, Keyboard, { });
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
    ResetKey(&keyboard->z);
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
            case SDLK_d:
                SetKey(&keyboard->d, eventType);
                break;
            case SDLK_p:
                SetKey(&keyboard->p, eventType);
                break;
            case SDLK_s:
                SetKey(&keyboard->s, eventType);
                break;
            case SDLK_w:
                SetKey(&keyboard->w, eventType);
                break;
            case SDLK_z:
                SetKey(&keyboard->z, eventType);
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