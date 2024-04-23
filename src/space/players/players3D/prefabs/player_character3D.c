ecs_entity_t prefab_player_character3D;

ecs_entity_t spawn_prefab_player_character3D(ecs_world_t *world) {
    zox_prefab_child(prefab_character3D)
    zox_prefab_name("prefab_player_character3D")
    zox_add_tag(e, PlayerCharacter)
    zox_add_tag(e, PlayerCharacter3D)
    zox_add(e, CameraLink)
    zox_prefab_set(e, DisableMovement, { 0 })
    // zox_remove(e, AnimateChunk)
    zox_add_tag(e, Aura)
    prefab_player_character3D = e;
    return e;
}
