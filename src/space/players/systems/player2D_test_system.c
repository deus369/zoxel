extern ecs_entity_t local_player;
const int particleSpawnCount = 266;
ecs_entity_t fps_display;

//! Called in ecs updates
void Player2DTestSystem(ecs_iter_t *it)
{
    ecs_world_t *world = it->world;
    const Keyboard *keyboards = ecs_field(it, Keyboard, 1);
    for (int i = 0; i < it->count; i++)
    {
        const Keyboard *keyboard = &keyboards[i];
        // toggle player connected application
        if ((keyboard->left_alt.is_pressed || keyboard->right_alt.is_pressed) && keyboard->enter.pressed_this_frame)
        {
            sdl_toggle_fullscreen(main_window);
        }
        else if (keyboard->space.is_pressed || keyboard->f.is_pressed)
        {
            if (local_player != 0 && ecs_has(world, local_player, Position2D))
            {
                const Position2D *position2D = ecs_get(world, local_player, Position2D);
                if (keyboard->space.is_pressed)
                {
                    Particle3DSpawnSystem(world, (float3) { position2D->value.x, position2D->value.y, 0 }, particleSpawnCount);
                }
                if (keyboard->f.is_pressed)
                {
                    Particle2DSpawnSystem(world, position2D->value, particleSpawnCount);
                }
            }
            else if (local_player != 0 && ecs_has(world, local_player, Position3D))
            {
                const Position3D *position = ecs_get(world, local_player, Position3D);
                if (keyboard->space.is_pressed)
                {
                    Particle3DSpawnSystem(world, position->value, particleSpawnCount);
                }
                if (keyboard->f.is_pressed)
                {
                    Particle2DSpawnSystem(world, (float2) { position->value.x, position->value.y }, particleSpawnCount);
                }
            }
        }
        else if (keyboard->m.pressed_this_frame)
        {
            double music_speed = 0.2 + (rand() % 100) * 0.008;
            ecs_set(world, main_music, MusicSpeed, { music_speed });
            ecs_set(world, main_music, GenerateMusic, { 1 });
            printf("Generating new music with speed [%f].\n", music_speed);
        }
        /*else if (keyboard->p.pressed_this_frame)
        {
            zoxel_log("[Printing Debug]\n");
            DebugParticlesSpawned(world);
            // PrintKeyboard(world);
        }*/
    }
}
zoxel_declare_system(Player2DTestSystem);

extern bool disable_chunk_systems;

void Player2DTestMainThreadSystem(ecs_iter_t *it)
{
    ecs_world_t *world = it->world;
    const Keyboard *keyboards = ecs_field(it, Keyboard, 1);
    for (int i = 0; i < it->count; i++)
    {
        const Keyboard *keyboard = &keyboards[i];
        if (keyboard->z.pressed_this_frame)
        {
            spawn_zoxel_window(world);
        }
        else if (keyboard->x.pressed_this_frame)
        {
            if (fps_display == 0)
            {
                zoxel_log("Showing fps display.\n");
                fps_display = spawn_fps_display(world, main_canvas, 32);
            }
            else
            {
                zoxel_log("Hiding fps display.\n");
                delete_hierarchy(world, fps_display);
                fps_display = 0;
            }
        }
        else if (keyboard->p.pressed_this_frame)
        {
            if (quads_label == 0)
            {
                zoxel_log("Showing quads_label.\n");
                quads_label = spawn_quad_count_label(world, main_canvas, 32);
            }
            else
            {
                zoxel_log("Hiding quads_label.\n");
                delete_hierarchy(world, quads_label);
                quads_label = 0;
            }
        }
        else if (keyboard->c.pressed_this_frame)
        {
            // spawn_sound(it->world);
            spawn_generated_sound(world,
                note_frequencies[rand() % 42], 0.8 + 0.4 * (rand() % 101) / 100.0,
                instrument_violin);
        }
        else if (keyboard->v.pressed_this_frame)
        {
            printf("Total Tris [%i]\n", tri_count);
        }
        else if (keyboard->m.pressed_this_frame)
        {
            ecs_set(world, main_music, GenerateMusic, { 1 });
        }
        else if (keyboard->b.pressed_this_frame)
        {
            spawn_many_characters3D(world);
        }
        else if (keyboard->h.pressed_this_frame)
        {
            // print positions
            const Children *children = ecs_get(world, quads_label, Children);
            for (int i = 0; i < children->length; i++)
            {
                const Position2D *position2D = ecs_get(world, children->value[i], Position2D);
                const ZigelIndex *zigelIndex = ecs_get(world, children->value[i], ZigelIndex);
                const CanvasPixelPosition *canvasPixelPosition = ecs_get(world, children->value[i], CanvasPixelPosition);
                const ParentLink *parentLink = ecs_get(world, children->value[i], ParentLink);
                const TextureSize *textureSize = ecs_get(world, children->value[i], TextureSize);
                const Texture *texture = ecs_get(world, children->value[i], Texture);
                
                printf("    [%i] is %fx%f - zigelIndex %i - canvasPixelPosition %ix%i - parentLink %lu - texture %ix%i:%i\n",
                    i, position2D->value.x, position2D->value.y, zigelIndex->value,
                    canvasPixelPosition->value.x, canvasPixelPosition->value.y,
                    parentLink->value,
                    textureSize->value.x, textureSize->value.y, texture->length);
                ecs_set(world, children->value[i], GenerateTexture, { 1 });
                ecs_set(world, children->value[i], MeshDirty, { 1 });
                ecs_set(world, children->value[i], TextureDirty, { 1 });
            }
        }
        else if (keyboard->n.pressed_this_frame)
        {
            const Position3D *position3D = ecs_get(world, latest_character3D, Position3D);
            const Rotation3D *rotation = ecs_get(world, latest_character3D, Rotation3D);
            const Scale1D *scale1D = ecs_get(world, latest_character3D, Scale1D);
            printf("Character stats: pos [%fx%fx%f] rot [%fx%fx%fx%f] sca [%f]\n",
                position3D->value.x, position3D->value.y, position3D->value.z,
                rotation->value.x, rotation->value.y, rotation->value.z, rotation->value.w,
                scale1D->value);
            // ecs_set(it->world, latest_character3D, Rotation3D, { { 0, 0, 0, 0 } });
            // ecs_set(it->world, latest_character3D, Rotation3D, { float4_identity() });
            ecs_set(world, latest_character3D, Rotation3D, { { 0.01f, 0, 0, 0 } });
        }
        else if (keyboard->j.pressed_this_frame)
        {
            disable_chunk_systems = true;
            if (disable_chunk_systems)
            {
                printf("Disabled chunk systems.\n");
            }
            else
            {
                printf("Enabled chunk systems.\n");
            }
        }
        /*else if (keyboard->y.pressed_this_frame)
        {
            create_terrain(world);
        }*/
    }
}
zoxel_declare_system(Player2DTestMainThreadSystem)