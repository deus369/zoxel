const int particleSpawnCount = 266;
const float debug_rotation_speed = 12;
const float debug_rotation_addition = 5;
extern ecs_entity_t local_character3D;

void Player2DTestSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const Keyboard *keyboards = ecs_field(it, Keyboard, 1);
    for (int i = 0; i < it->count; i++) {
        const Keyboard *keyboard = &keyboards[i];
        /*if (keyboard->h.pressed_this_frame) {
            has_rendered_elements = 0;
            zoxel_log(" === rendering elements ===\n");
        }*/

        if (keyboard->f.is_pressed) {
            Particle2DSpawnSystem(world, float2_zero, particleSpawnCount);
        }
        // toggle player connected application
        if ((keyboard->left_alt.is_pressed || keyboard->right_alt.is_pressed) && keyboard->enter.pressed_this_frame) {
            sdl_toggle_fullscreen(world, main_window);
        } else if (keyboard->p.pressed_this_frame) {
            const GameState *gameState = ecs_get(world, local_game, GameState);
            if (gameState->value == zoxel_game_state_playing) {
                ecs_entity_t main_camera = main_cameras[0]; // get player camera link instead
                ecs_entity_t character = 0;
                if (camera_mode == zox_camera_mode_first_person) character = ecs_get(world, main_camera, ParentLink)->value;
                else character = ecs_get(world, main_camera, CameraFollowLink)->value;
                if (character == 0) attach_to_character(world, main_player, main_camera, local_character3D);
                else detatch_from_character(world, main_player, main_camera, local_character3D);
            }
        } /*else if (keyboard->b.pressed_this_frame) {
            zoxel_log("testing world ui on character %lu\n", local_character3D);
            spawn_element3D(world, local_character3D);
        }*/
        #ifdef zoxel_tests_rotate_by_keys
            else if (keyboard->r.is_pressed) {
                float3 euler = (float3) { 0, 90 * degreesToRadians, 0 * degreesToRadians };
                //float4 quaternion = (float4) { 0, debug_rotation_speed, 0, 1 };
                //quaternion_normalize(&quaternion);
                ecs_set(world, local_character3D, Alpha3D, { quaternion_from_euler(euler) });
            } else if (keyboard->t.is_pressed) {
                float3 euler = (float3) { 0, -90 * degreesToRadians, 0 * degreesToRadians };
                //float4 quaternion = (float4) { 0, -debug_rotation_speed, 0, 1 };
                //quaternion_normalize(&quaternion);
                ecs_set(world, local_character3D, Alpha3D, { quaternion_from_euler(euler) });
            } else if (keyboard->y.pressed_this_frame) {
                float3 euler = (float3) { 0 * degreesToRadians, (-90 + debug_rotation_addition) * degreesToRadians, 0 * degreesToRadians };
                ecs_set(world, local_character3D, Rotation3D, { quaternion_from_euler(euler) });
            } else if (keyboard->u.pressed_this_frame) {
                float3 euler = (float3) { 0 * degreesToRadians, (0 + debug_rotation_addition) * degreesToRadians, 0 * degreesToRadians };
                ecs_set(world, local_character3D, Rotation3D, { quaternion_from_euler(euler) });
            } else if (keyboard->i.pressed_this_frame) {
                float3 euler = (float3) { 0 * degreesToRadians, (90 + debug_rotation_addition) * degreesToRadians, 0 * degreesToRadians };
                ecs_set(world, local_character3D, Rotation3D, { quaternion_from_euler(euler) });
            } else if (keyboard->o.pressed_this_frame) {
                float3 euler = (float3) { 0 * degreesToRadians, (180 + debug_rotation_addition) * degreesToRadians, 0 * degreesToRadians };
                ecs_set(world, local_character3D, Rotation3D, { quaternion_from_euler(euler) });
            } else if (keyboard->f.pressed_this_frame) {
                zoxel_log(" > reset omega3D\n");
                ecs_set(world, local_character3D, Omega3D, { quaternion_identity });
            } else if (keyboard->g.pressed_this_frame) {
                zoxel_log(" > reset alpha3D\n");
                ecs_set(world, local_character3D, Alpha3D, { quaternion_identity });
            }
        #endif
    }
} zox_declare_system(Player2DTestSystem);


/* else if (keyboard->space.is_pressed || keyboard->f.is_pressed) {
    if (local_player != 0 && ecs_has(world, local_player, Position2D)) {
        const Position2D *position2D = ecs_get(world, local_player, Position2D);
        if (keyboard->space.is_pressed) {
            Particle3DSpawnSystem(world, (float3) { position2D->value.x, position2D->value.y, 0 }, particleSpawnCount);
        }
        if (keyboard->f.is_pressed) {
            Particle2DSpawnSystem(world, position2D->value, particleSpawnCount);
        }
    } else if (local_player != 0 && ecs_has(world, local_player, Position3D)) {
        const Position3D *position = ecs_get(world, local_player, Position3D);
        if (keyboard->space.is_pressed) {
            Particle3DSpawnSystem(world, position->value, particleSpawnCount);
        }
        if (keyboard->f.is_pressed) {
            Particle2DSpawnSystem(world, (float2) { position->value.x, position->value.y }, particleSpawnCount);
        }
    }
}*/
/*else if (keyboard->m.pressed_this_frame) {
    double music_speed = 0.2 + (rand() % 100) * 0.008;
    ecs_set(world, main_music, MusicSpeed, { music_speed });
    ecs_set(world, main_music, GenerateMusic, { 1 });
    zoxel_log(" > generating new music with speed [%f].\n", music_speed);
}*/

/*else if (keyboard->c.pressed_this_frame) {
    zoxel_log(" > spawned new sound\n");
    // spawn_sound(it->world);
    spawn_generated_sound(world, note_frequencies[rand() % 42], 0.8 + 0.4 * (rand() % 101) / 100.0, instrument_violin);
} else if (keyboard->v.pressed_this_frame) {
    zoxel_log(" > total tris [%i]\n", tri_count);
} else if (keyboard->b.pressed_this_frame) {
    spawn_many_characters3D(world);
} else if (keyboard->h.pressed_this_frame) {
    // print positions
    const Children *children = ecs_get(world, quads_label, Children);
    for (int i = 0; i < children->length; i++) {
        const Position2D *position2D = ecs_get(world, children->value[i], Position2D);
        const ZigelIndex *zigelIndex = ecs_get(world, children->value[i], ZigelIndex);
        const CanvasPixelPosition *canvasPixelPosition = ecs_get(world, children->value[i], CanvasPixelPosition);
        const ParentLink *parentLink = ecs_get(world, children->value[i], ParentLink);
        const TextureSize *textureSize = ecs_get(world, children->value[i], TextureSize);
        const TextureData *textureData = ecs_get(world, children->value[i], TextureData);
        zoxel_log("    [%i] is [%fx%f] - zigelIndex [%i] - canvasPixelPosition [%ix%i] - parentLink [%lu] - textureData [%ix%i:%i]\n",
            i, position2D->value.x, position2D->value.y, zigelIndex->value, canvasPixelPosition->value.x, canvasPixelPosition->value.y,
            (long int) parentLink->value, textureSize->value.x, textureSize->value.y, textureData->length);
        ecs_set(world, children->value[i], GenerateTexture, { 1 });
        ecs_set(world, children->value[i], MeshDirty, { 1 });
        ecs_set(world, children->value[i], TextureDirty, { 1 });
    }
} else if (keyboard->j.pressed_this_frame) {
    zoxel_log("deleting main menu\n");
    ecs_delete(world, main_menu);
} else if (keyboard->n.pressed_this_frame) {
    const Position3D *position3D = ecs_get(world, latest_character3D, Position3D);
    const Rotation3D *rotation = ecs_get(world, latest_character3D, Rotation3D);
    const Scale1D *scale1D = ecs_get(world, latest_character3D, Scale1D);
    zoxel_log("Character stats: pos [%fx%fx%f] rot [%fx%fx%fx%f] sca [%f]\n",
        position3D->value.x, position3D->value.y, position3D->value.z,
        rotation->value.x, rotation->value.y, rotation->value.z, rotation->value.w,
        scale1D->value);
    // ecs_set(it->world, latest_character3D, Rotation3D, { { 0, 0, 0, 0 } });
    // ecs_set(it->world, latest_character3D, Rotation3D, { float4_identity });
    ecs_set(world, latest_character3D, Rotation3D, { { 0.01f, 0, 0, 0 } });
} else if (keyboard->y.pressed_this_frame) {
    create_terrain(world);
} else if (keyboard->p.pressed_this_frame) {
    zoxel_log("[Printing Debug]\n");
    DebugParticlesSpawned(world);
    // print_keyboard(world);
}*/
