extern ecs_entity_t local_player;
const int particleSpawnCount = 266;

//! Called in ecs updates
void Player2DTestSystem(ecs_iter_t *it)
{
    ecs_world_t *world = it->world;
    const Keyboard *keyboards = ecs_field(it, Keyboard, 1);
    for (int i = 0; i < it->count; i++)
    {
        const Keyboard *keyboard = &keyboards[i];
        // toggle player connected application
        if ((keyboard->left_alt.isPressed || keyboard->right_alt.isPressed) && keyboard->enter.wasPressedThisFrame)
        {
            sdl_toggle_fullscreen(main_window);
        }
        else if (keyboard->space.isPressed || keyboard->f.isPressed)
        {
            if (local_player != 0 && ecs_has(world, local_player, Position2D))
            {
                const Position2D *position2D = ecs_get(world, local_player, Position2D);
                if (keyboard->space.isPressed)
                {
                    Particle3DSpawnSystem(world, (float3) { position2D->value.x, position2D->value.y, 0 }, particleSpawnCount);
                }
                if (keyboard->f.isPressed)
                {
                    Particle2DSpawnSystem(world, position2D->value, particleSpawnCount);
                }
            }
            else if (local_player != 0 && ecs_has(world, local_player, Position))
            {
                const Position *position = ecs_get(world, local_player, Position);
                if (keyboard->space.isPressed)
                {
                    Particle3DSpawnSystem(world, position->value, particleSpawnCount);
                }
                if (keyboard->f.isPressed)
                {
                    Particle2DSpawnSystem(world, (float2) { position->value.x, position->value.y }, particleSpawnCount);
                }
            }
        }
        else if (keyboard->p.wasPressedThisFrame)
        {
            zoxel_log("[Printing Debug]\n");
            DebugParticlesSpawned(world);
            // PrintKeyboard(world);
        }
    }
}
ECS_SYSTEM_DECLARE(Player2DTestSystem);

ecs_entity_t fps_display;

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
        else if (keyboard->x.wasPressedThisFrame)
        {
            if (fps_display == 0)
            {
                zoxel_log("Showing fps display.\n");
                fps_display = spawn_fps_display(it->world, main_canvas, 32);
            }
            else
            {
                zoxel_log("Hiding fps display.\n");
                delete_hierarchy(it->world, fps_display);
                fps_display = 0;
            }
        }
        else if (keyboard->c.wasPressedThisFrame)
        {
            spawn_sound(it->world);
        }
    }
}
ECS_SYSTEM_DECLARE(Player2DTestMainThreadSystem);