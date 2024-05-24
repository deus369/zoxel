


/* else if (keyboard->space.is_pressed || keyboard->f.is_pressed) {
    if (main_player != 0 && zox_has(main_player, Position2D)) {
        const Position2D *position2D = zox_get(world, main_player, Position2D);
        if (keyboard->space.is_pressed) {
            Particle3DSpawnSystem(world, (float3) { position2D->value.x, position2D->value.y, 0 }, particleSpawnCount);
        }
        if (keyboard->f.is_pressed) {
            Particle2DSpawnSystem(world, position2D->value, particleSpawnCount);
        }
    } else if (main_player != 0 && zox_has(main_player, Position3D)) {
        const Position3D *position = zox_get(world, main_player, Position3D);
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
    zox_set(local_music, MusicSpeed, { music_speed });
    zox_set(local_music, GenerateMusic, { 1 });
    zoxel_log(" > generating new music with speed [%f].\n", music_speed);
}*/

/*else if (keyboard->c.pressed_this_frame) {
    zoxel_log(" > spawned new sound\n");
    // spawn_sound(it->world);
    spawn_generated_sound(world, note_frequencies[rand() % 42], 0.8 + 0.4 * (rand() % 101) / 100.0, instrument_violin);
} else if (keyboard->v.pressed_this_frame) {
    zoxel_log(" > total tris [%i]\n", triangles_count);
} else if (keyboard->b.pressed_this_frame) {
    spawn_many_characters3D(world);
} else if (keyboard->h.pressed_this_frame) {
    // print positions
    const Children *children = zox_get(world, quads_label, Children);
    for (int i = 0; i < children->length; i++) {
        const Position2D *position2D = zox_get(world, children->value[i], Position2D);
        const ZigelIndex *zigelIndex = zox_get(world, children->value[i], ZigelIndex);
        const CanvasPosition *canvasPosition = zox_get(world, children->value[i], CanvasPosition);
        const ParentLink *parentLink = zox_get(world, children->value[i], ParentLink);
        const TextureSize *textureSize = zox_get(world, children->value[i], TextureSize);
        const TextureData *textureData = zox_get(world, children->value[i], TextureData);
        zoxel_log("    [%i] is [%fx%f] - zigelIndex [%i] - canvasPosition [%ix%i] - parentLink [%lu] - textureData [%ix%i:%i]\n",
            i, position2D->value.x, position2D->value.y, zigelIndex->value, canvasPosition->value.x, canvasPosition->value.y,
            (long int) parentLink->value, textureSize->value.x, textureSize->value.y, textureData->length);
        zox_set(children->value[i], GenerateTexture, { 1 });
        zox_set(children->value[i], MeshDirty, { 1 });
        zox_set(children->value[i], TextureDirty, { 1 });
    }
} else if (keyboard->j.pressed_this_frame) {
    zoxel_log("deleting main menu\n");
    ecs_delete(world, main_menu);
} else if (keyboard->n.pressed_this_frame) {
    const Position3D *position3D = zox_get(world, latest_character3D, Position3D);
    const Rotation3D *rotation = zox_get(world, latest_character3D, Rotation3D);
    const Scale1D *scale1D = zox_get(world, latest_character3D, Scale1D);
    zoxel_log("Character stats: pos [%fx%fx%f] rot [%fx%fx%fx%f] sca [%f]\n",
        position3D->value.x, position3D->value.y, position3D->value.z,
        rotation->value.x, rotation->value.y, rotation->value.z, rotation->value.w,
        scale1D->value);
    zox_set(latest_character3D, Rotation3D, { { 0.01f, 0, 0, 0 } });
} else if (keyboard->y.pressed_this_frame) {
    create_terrain(world);
} else if (keyboard->p.pressed_this_frame) {
    zoxel_log("[Printing Debug]\n");
    DebugParticlesSpawned(world);
    // print_keyboard(world);
}*/


#ifdef zox_test_quaternion_camera
                /*Rotation3D *rotation3D = &rotation3Ds[j];
                float dx = - mouse->delta.x * camera_quaternion_speed;
                float dy = mouse->delta.y * camera_quaternion_speed;
                float angle = sqrt(dx * dx + dy * dy);
                float axis[3] = { dy / angle, dx / angle, 0 };
                float4 rotate_delta = (float4) {
                    sin(angle / 2.0f) * axis[0],
                    sin(angle / 2.0f) * axis[1],
                    sin(angle / 2.0f) * axis[2],
                    cos(angle / 2.0f)
                };
                rotation3D->value = quaternion_rotate(rotation3D->value, rotate_delta);*/
#else
