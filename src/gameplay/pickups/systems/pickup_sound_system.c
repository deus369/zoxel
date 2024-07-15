void PickupSoundSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(PickedUp, pickedUps, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(PickedUp, pickedUps, pickedUp)
        if (pickedUp->value != pickup_state_pickup) continue;
        spawn_sound_from_file_name(world, prefab_sound, "pickup2");
        // move to character, delete after!
        zox_delete(it->entities[i])
    }
} zox_declare_system(PickupSoundSystem)
