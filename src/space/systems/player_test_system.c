/*void test_sounds(ecs_world_t *world, const Keyboard *keyboard) {
    if (keyboard->_1.pressed_this_frame || keyboard->_2.pressed_this_frame || keyboard->_3.pressed_this_frame || keyboard->_4.pressed_this_frame || keyboard->_5.pressed_this_frame || keyboard->_6.pressed_this_frame || keyboard->_7.pressed_this_frame || keyboard->_8.pressed_this_frame) spawn_sound_from_file_index(world, prefab_sound, 0);

    else if (keyboard->_2.pressed_this_frame) {
        spawn_sound_generated(world, note_frequencies[42], 0.6, instrument_piano);
    } else if (keyboard->_3.pressed_this_frame) {
        spawn_sound_generated(world, note_frequencies[42], 0.3, instrument_piano_square);
    } else if (keyboard->_4.pressed_this_frame) {
        spawn_sound_generated(world, note_frequencies[42], 0.8, instrument_violin);
    } else if (keyboard->_5.pressed_this_frame) {
        spawn_sound_generated(world, note_frequencies[42], 0.8, instrument_organ);
    } else if (keyboard->_6.pressed_this_frame) {
        spawn_sound_generated(world, note_frequencies[42], 0.8, instrument_edm);
    } else if (keyboard->_7.pressed_this_frame) {
        spawn_sound_generated(world, note_frequencies[42], 0.6, instrument_guitar);
    } else if (keyboard->_8.pressed_this_frame) {
        spawn_sound_generated(world, note_frequencies[42], 0.8, instrument_flute);
    }
} */

/*void test_raycast(ecs_world_t *world, const Keyboard *keyboard, const ecs_entity_t realm, const ecs_entity_t player) {
    if (keyboard->_1.pressed_this_frame) set_player_voxel_ray(world, realm, player, 0, 0, 2);
    else if (keyboard->_2.pressed_this_frame) set_player_voxel_ray(world, realm, player, 0, 1, 1);
    else if (keyboard->_3.pressed_this_frame) set_player_voxel_ray(world, realm, player, 0, 3, 1);
    else if (keyboard->_4.pressed_this_frame) set_player_voxel_ray(world, realm, player, 0, 4, 1);
    else if (keyboard->_5.pressed_this_frame) set_player_voxel_ray(world, realm, player, 0, zox_block_dirt_rubble, 1);
}*/

// Shortcuts just for testing new stuff
/*void PlayerTestSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(DeviceLinks)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(DeviceLinks, deviceLinks)
        // const ecs_entity_t canvas = canvasLink->value;
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (!zox_valid(device) || zox_gett_value(device, DeviceDisabled)) {
                continue;
            }
            if (zox_has(device, Keyboard)) {
                const Keyboard *keyboard = zox_get(device, Keyboard)
                // brain_test_controls(world, keyboard, canvas);
                // test_raycast(world, keyboard, local_realm, it->entities[i]);
#ifdef test_particles2D
                if (keyboard->f.is_pressed) {
                    Particle2DSpawnSystem(world, float2_zero, particleSpawnCount);
                }
#endif
            }
        }
    }
} zoxd_system(PlayerTestSystem)*/
