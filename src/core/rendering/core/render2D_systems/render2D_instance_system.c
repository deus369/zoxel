// Spawn a queue

extern void render_instance2D(float2 position, float angle, float scale, float brightness);

//! Render 2D entities.
void InstanceRender2DSystem(ecs_iter_t *it)
{
    Position2D *position2Ds = ecs_field(it, Position2D, 1);
    Rotation2D *rotation2Ds = ecs_field(it, Rotation2D, 2);
    Scale1D *scale1Ds = ecs_field(it, Scale1D, 3);
    Brightness *brightnesses = ecs_field(it, Brightness, 4);
    for (int i = 0; i < it->count; i++)
    {
        const Position2D *position = &position2Ds[i];
        const Rotation2D *rotation2D = &rotation2Ds[i];
        const Scale1D *scale1D = &scale1Ds[i];
        const Brightness *brightness = &brightnesses[i];
        // Add to Render Queue
        // printf("    Bob's Position2D is {%f, %f}\n", position.value.x, position.value.y);
        render_instance2D(position->value, rotation2D->value, scale1D->value, brightness->value);
    }
}
ECS_SYSTEM_DECLARE(InstanceRender2DSystem);