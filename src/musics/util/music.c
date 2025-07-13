void stop_music(ecs_world_t *world, const ecs_entity_t playlist) {
    if (!playlist || !zox_has(playlist, MusicPlaying)) {
        zox_log_error("invalid playlist in [play_music]")
        return;
    }
    const byte old_index = zox_get_value(playlist, MusicPlaying)
    zox_geter(playlist, MusicLinks, musicLinks)
    if (old_index >= musicLinks->length) {
        zox_log_error("old_index out of bounds [%i] >= [%i]", old_index, musicLinks->length)
        return;
    }
    zox_set(musicLinks->value[old_index], MusicEnabled, { 0 })
    zox_log("- playlist stopped track [%i]", old_index)
}

void play_music(ecs_world_t *world, const ecs_entity_t playlist, const byte new_index) {
    if (!playlist || !zox_has(playlist, MusicPlaying)) {
        zox_log_error("invalid playlist in [play_music]")
        return;
    }
    const byte old_index = zox_get_value(playlist, MusicPlaying)
    /*if (new_index == old_index) {
     *       zox_log_error("playlist already playing track [%i]", old_index)
     *       return;
}*/
    // set previous music off and new one on
    zox_geter(playlist, MusicLinks, musicLinks)
    if (new_index >= musicLinks->length) {
        zox_log_error("new_index out of bounds [%i] >= [%i]", new_index, musicLinks->length)
        return;
    }
    zox_set(musicLinks->value[old_index], MusicEnabled, { 0 })
    zox_set(musicLinks->value[new_index], MusicEnabled, { 1 })
    zox_set(playlist, MusicPlaying, { new_index })
    zox_log("+ playlist playing new track [%i] -> [%i]", old_index, new_index)
}

void add_music(ecs_world_t *world, ecs_entity_t playlist, ecs_entity_t music) {
    if (!playlist) {
        zox_log_error("cannot add music to null playlist")
        return;
    }
    // zox_log(" + added music to playlist [%lu]\n", music)
    zox_get_muter(playlist, MusicLinks, musicLinks)
    add_to_MusicLinks(musicLinks, music);
}