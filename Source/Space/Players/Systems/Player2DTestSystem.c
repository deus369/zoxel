extern ecs_entity_t localPlayer;

//! Called in ecs updates
void Player2DTestSystem(ecs_iter_t *it)
{
    const int particleSpawnCount = 60;
    ecs_world_t *world = it->world;
    const Position2D *bobPosition = ecs_get(world, localPlayer, Position2D);
    const Keyboard *keyboards = ecs_field(it, Keyboard, 1);
    for (int i = 0; i < it->count; i++)
    {
        const Keyboard *keyboard = &keyboards[i];
        if (keyboard->space.isPressed)
        {
            ParticleSpawnSystem(world, bobPosition->value, particleSpawnCount);
        }
        else if (keyboard->c.isPressed)
        {
            Particle2DSpawnSystem(world, bobPosition->value, particleSpawnCount);
        }
        else if (keyboard->p.wasPressedThisFrame)
        {
            printf("[Printing Debug]\n");
            DebugParticlesSpawned(world);
            // PrintKeyboard(world);
        }
    }
}
ECS_SYSTEM_DECLARE(Player2DTestSystem);