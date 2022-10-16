const int bobSpawnCount = 500;
extern ecs_entity_t localPlayer;

int GetParticles2DCount(ecs_world_t *world)
{
    return ecs_count(world, Particle2D);
}

void DebugParticlesSpawned(ecs_world_t *world)
{
    printf("    Bobs Spawned [%i]\n", GetParticles2DCount(world));
}

//! Called in ecs updates
void Player2DTestSystem(ecs_iter_t *it)
{
    ecs_world_t *world = it->world;
    const Position2D *bobPosition = ecs_get(world, localPlayer, Position2D);
    const Keyboard *keyboards = ecs_field(it, Keyboard, 1);
    for (int i = 0; i < it->count; i++)
    {
        const Keyboard *keyboard = &keyboards[i];
        if (keyboard->space.isPressed) // wasPressedThisFrame)
        {
            // printf("Firing the Bob Army.\n");
            Particles2DSpawnSystem(world, bobPosition->value, bobSpawnCount);
        }
        else if (keyboard->p.wasPressedThisFrame)
        {
            printf("[Printing Debug]\n");
            DebugParticlesSpawned(world);
            PrintKeyboard(world);
        }
        else if (keyboard->z.wasPressedThisFrame)
        {
            printf("Spawning new Player.\n");
            SpawnPlayerCharacter2D(world);
        }
    }
}
ECS_SYSTEM_DECLARE(Player2DTestSystem);