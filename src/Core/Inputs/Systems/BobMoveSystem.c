#include "../../../Core/Inputs/Inputs.h"
#include "../../../Core/Core/Core.h"
#include "../../../Core/Transforms2D/Transforms2D.h"
#include "../../../Core/Rendering/Rendering.h"
#include "../../../Space/Physics2D/Physics2D.h"

//! Called in ecs updates
void BobMoveSystem(ecs_iter_t *it)
{
    Keyboard *keyboards = ecs_field(it, Keyboard, 1);
    // Acceleration2D *acceleration2Ds = ecs_field(it, Acceleration2D, 1);
    for (int i = 0; i < it->count; i++)
    {
        const Keyboard *keyboard = &keyboards[i];
        if (keyboard->w.wasPressedThisFrame)
        {
            // Move Bob Up!
        }
    }
}