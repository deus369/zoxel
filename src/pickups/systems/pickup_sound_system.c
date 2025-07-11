void PickupSoundSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(PickedUp)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(PickedUp, pickedUp)
        if (pickedUp->value != pickup_state_pickup) {
            continue;
        }
        spawn_sound_from_file_name(world, prefab_sound, "pickup2");
        // todo: move to character, delete after!
        zox_delete(e)
    }
} zox_declare_system(PickupSoundSystem)