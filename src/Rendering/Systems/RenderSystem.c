#include "../../Flecs/flecs.h"

void RenderSystem(ecs_iter_t *it)
{
    Position2D *position2Ds = ecs_field(it, Position2D, 1);
    Rotation2D *rotation2Ds = ecs_field(it, Rotation2D, 2);
    Scale2D *scale2Ds = ecs_field(it, Scale2D, 3);
    Brightness *brightnesses = ecs_field(it, Brightness, 4);
    for (int i = 0; i < it->count; i++)
    {
        const Position2D *position = &position2Ds[i];
        const Rotation2D *rotation2D = &rotation2Ds[i];
        const Scale2D *scale2D = &scale2Ds[i];
        const Brightness *brightness = &brightnesses[i];
        // printf("    Bob's Position2D is {%f, %f}\n", position.value.x, position.value.y);
        OpenGLRender(position->value.x, position->value.y, rotation2D->value, scale2D->value, brightness->value);
    }
}