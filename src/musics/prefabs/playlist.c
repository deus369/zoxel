ecs_entity_t spawn_prefab_playlist(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_playlist")
    zox_add_tag(e, Playlist)
    zox_prefab_set(e, PlaylistIndex, { 0 })
    zox_add(e, MusicLinks)
    return e;
}

ecs_entity_t spawn_playlist(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_instance(prefab)
    zox_name("playlist")
    return e;
}
