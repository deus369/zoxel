// Spawn a queue

// extern void RenderEntity2D(float3 position, float4 rotation, float scale, float brightness);

//! Render 2D entities.
void ParticleRenderSystem(ecs_iter_t *it)
{
    /*Position *positions = ecs_field(it, Position, 1);
    Rotation *rotations = ecs_field(it, Rotation, 2);
    Scale1D *scale1Ds = ecs_field(it, Scale1D, 3);
    Brightness *brightnesses = ecs_field(it, Brightness, 4);
    for (int i = 0; i < it->count; i++)
    {
        const Position *position = &positions[i];
        const Rotation *rotation2D = &rotations[i];
        const Scale1D *scale1D = &scale1Ds[i];
        const Brightness *brightness = &brightnesses[i];
        // Add to Render Queue
        // printf("    Bob's Position2D is {%f, %f}\n", position.value.x, position.value.y);
        RenderParticle(position->value, rotation2D->value, scale1D->value, brightness->value);
    }*/
}
ECS_SYSTEM_DECLARE(ParticleRenderSystem);