void spawn_realm_playlist(ecs_world_t *world, const ecs_entity_t realm) {
    if (!realm) {
        zox_log_error("! realm is null.")
        return;
    }
    // add them to realm
    if (!zox_has(realm, PlaylistLinks)) {
        zox_log_error("! realm [%lu] has no PlaylistLinks")
        return;
    }
    // zox_get_muter(realm, PlaylistLinks, playlistLinks)
    PlaylistLinks playlistLinks2 = { 0, NULL };
    PlaylistLinks *playlistLinks = &playlistLinks2;
    const ecs_entity_t playlist_main_menu = spawn_playlist(world, prefab_playlist);
    const ecs_entity_t playlist_game = spawn_playlist(world, prefab_playlist);
    add_to_PlaylistLinks(playlistLinks, playlist_main_menu);
    add_to_PlaylistLinks(playlistLinks, playlist_game);
    // musics
    const ecs_entity_t music_file = load_music_file(world, prefab_music_file, prefab_note);
    const ecs_entity_t generated_music = spawn_music_generated(world, prefab_music_generated); // _square
    // add musics to playlists
    add_music(world, playlist_main_menu, music_file);
    add_music(world, playlist_game, generated_music);
    // zox_set(realm, PlaylistLink, { playlist })
    // play_playlist(world, realm, 0);
    local_music = music_file;
    zox_set(local_music, MusicPlaying, { 1 })
    zox_set(realm, PlaylistLinks, { playlistLinks->length, playlistLinks->value });
}
