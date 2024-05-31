void prefabs_add_characters_to_player(ecs_world_t *world, const ecs_entity_t e) {
    zox_prefab_set(e, CharacterLink, { 0 })
    zox_prefab_set(e, CameraLink, { 0 })
}
