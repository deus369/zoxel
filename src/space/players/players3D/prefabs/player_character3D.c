ecs_entity_t prefab_character3D_player;

ecs_entity_t spawn_prefab_player_character3D(ecs_world_t *world) {
    zox_prefab_child(prefab_character3D)
    zox_prefab_name("prefab_character3D_player")
    zox_add_tag(e, PlayerCharacter)
    zox_add_tag(e, PlayerCharacter3D)
    zox_add_tag(e, DisableReverseLinkChunk) // silent in chunks, chunksdont know me
    zox_set(e, CameraLink, { 0 })
    zox_prefab_set(e, DisableMovement, { 0 })
    prefab_character3D_player = e;
    return e;
}

ecs_entity_2 spawn_player_character3D_in_world(ecs_world_t *world, const vox_file *vox, const float3 position, const float4 rotation, const unsigned char character_lod, const ecs_entity_t player) {
    const ecs_entity_2 e = spawn_character3D(world, prefab_character3D_player, vox, position, rotation, character_lod, player, player_vox_scale, 0);
    const ecs_entity_t aura = spawn_aura(world, e.x);
    SkillLinks *skillLinks = zox_get_mut(e.x, SkillLinks)
    add_to_SkillLinks(skillLinks, aura);
    zox_modified(e.x, SkillLinks)
    return e;
}
