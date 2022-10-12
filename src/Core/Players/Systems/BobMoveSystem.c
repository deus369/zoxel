#include "../../../Core/Inputs/Inputs.h"
#include "../../../Core/Core/Core.h"
#include "../../../Core/Transforms2D/Transforms2D.h"
#include "../../../Core/Rendering/Rendering.h"
#include "../../../Space/Physics2D/Physics2D.h"

//! Called in ecs updates
void BobMoveSystem(ecs_iter_t *it)
{
    const float movementPower = 30.0f;
    double deltaTime = (double) it->delta_time;
    Keyboard *keyboards = ecs_field(it, Keyboard, 1);
    ecs_entity_t bobEntity = ecs_field_id(it, 2);
    // Acceleration2D *acceleration2Ds = ecs_field(it, Acceleration2D, 1);
    for (int i = 0; i < it->count; i++)
    {
        const Keyboard *keyboard = &keyboards[i];
        float2 movement = { 0, 0 };
        // Move Bob Up!
        if (keyboard->w.isPressed)
        {
            movement.y = 1;
        }
        if (keyboard->s.isPressed)
        {
            movement.y = -1;
        }
        if (keyboard->a.isPressed)
        {
            movement.x = -1;
        }
        if (keyboard->d.isPressed)
        {
            movement.x = 1;
        }
        if (!(movement.x == 0 && movement.y == 0))
        {
            printf("Bob is moving: %fx%f %lu \n", movement.x, movement.y, bobEntity);
            // Velocity2D *velocity2D = ecs_get_mut(it->world, bobEntity, Velocity2D);
            // velocity2D->value.x = movement.x * deltaTime * movementPower;
            // velocity2D->value.y = movement.y * deltaTime * movementPower;
            // ecs_modified(it->world, bobEntity, Velocity2D);
        }
    }
}