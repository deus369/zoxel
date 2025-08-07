/*
void brain_test_controls(
    ecs_world_t *world,
    const Keyboard *keyboard,
    const ecs_entity_t canvas
) {
    if (!local_brain) return;
    if (keyboard->_1.pressed_this_frame) {
        feed_brain_random_input(world, local_brain);
        spawn_sound_from_file_index(world, prefab_sound, 0);
        zox_log(" + fed brain texture random\n")
    }
    else if (keyboard->_2.pressed_this_frame) {
        if (brain_texture) zox_delete(brain_texture)
        brain_texture = spawn_brain_as_texture(world, local_brain);
        spawn_sound_from_file_index(world, prefab_sound, 0);
        zox_log(" + spawned brain as texture\n")
    }
    else if (keyboard->_3.pressed_this_frame) {
        if (!brain_texture) return;
        if (brain_texture_ui) zox_delete(brain_texture_ui)
        const int2 position = (int2) { 8, 8 };
        const int2 size = (int2) { 32 * 4, 32 * 4 };
        brain_texture_ui = spawn_element_texture(world, canvas, brain_texture, position, size);
        spawn_sound_from_file_index(world, prefab_sound, 0);
        zox_log(" + updated brain texture ui\n")
    }
    else if (keyboard->_4.pressed_this_frame) {
        feed_brain_input(world, local_brain, 0.01f);
        spawn_sound_from_file_index(world, prefab_sound, 0);
        zox_log(" + fed brain empty\n")
    }
    else if (keyboard->_5.pressed_this_frame) {
        zox_log(" + updated brain weights\n")
        randomize_brain_weights(world, local_brain);
        spawn_sound_from_file_index(world, prefab_sound, 0);
    }
    else if (keyboard->_6.pressed_this_frame) {
        zox_log(" + saved brain texture\n")
        save_brain_as_texture(world, local_brain);
        spawn_sound_from_file_index(world, prefab_sound, 0);
    }
}*/