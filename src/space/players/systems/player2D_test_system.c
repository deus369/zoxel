extern ecs_entity_t localPlayer;
const int particleSpawnCount = 266;

//! Called in ecs updates
void Player2DTestSystem(ecs_iter_t *it)
{
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
        else if (keyboard->f.isPressed)
        {
            Particle2DSpawnSystem(world, bobPosition->value, particleSpawnCount);
        }
        else if ((keyboard->left_alt.isPressed || keyboard->right_alt.isPressed) && keyboard->enter.wasPressedThisFrame)
        {
            sdl_toggle_fullscreen(main_window);
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

void Player2DTestMainThreadSystem(ecs_iter_t *it)
{
    const Keyboard *keyboards = ecs_field(it, Keyboard, 1);
    for (int i = 0; i < it->count; i++)
    {
        const Keyboard *keyboard = &keyboards[i];
        if (keyboard->z.wasPressedThisFrame)
        {
            spawn_zoxel_window(it->world);
        }
    }
}
ECS_SYSTEM_DECLARE(Player2DTestMainThreadSystem);