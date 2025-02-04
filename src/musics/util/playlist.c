void play_music(ecs_world_t *world, const ecs_entity_t playlist, const unsigned char new_index) {
    if (!playlist || !zox_has(playlist, PlaylistIndex)) {
        zox_log(" ! cannot play music on null playlist\n")
        return;
    }
    const unsigned char current_index = zox_get_value(playlist, PlaylistIndex)
    if (new_index == current_index) {
        zox_log(" > music is already at [%i]\n", current_index)
        return;
    }
    // set previous music off and new one on
    zox_geter(playlist, MusicLinks, musicLinks)
    zox_set(musicLinks->value[current_index], MusicPlaying, { 0 })
    zox_set(musicLinks->value[new_index], MusicPlaying, { 1 })
    zox_set(playlist, PlaylistIndex, { new_index })
    zox_log(" + music enabled [%i]\n", new_index)
    zox_log(" + music disabled [%i]\n", current_index)
}

void add_music(ecs_world_t *world, ecs_entity_t playlist, ecs_entity_t music) {
    if (!playlist) {
        zox_log(" ! cannot add music to null playlist\n")
        return;
    }
    zox_log(" + added music to playlist [%lu]\n", music)
    zox_get_muter(playlist, MusicLinks, musicLinks)
    add_to_MusicLinks(musicLinks, music);
}

void play_playlist(ecs_world_t *world, const ecs_entity_t realm, const unsigned char index) {
    if (!realm || !zox_has(realm, PlaylistLinks)) {
        zox_log("invalid realm\n")
        return;
    }
    zox_geter(realm, PlaylistLinks, playlistLinks)
    if (!playlistLinks->value) {
        zox_log(" ! invalid playlist links value.\n")
        return;
    }
    if (index >= playlistLinks->length) {
        zox_log("invalid index playlist [%i]\n", index)
        return;
    }
    const ecs_entity_t playlist = playlistLinks->value[index];
    play_music(world, playlist, 0);
}
