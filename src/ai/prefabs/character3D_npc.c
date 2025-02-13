ecs_entity_t prefab_character3D_npc;

ecs_entity_t spawn_prefab_character3D_npc(ecs_world_t *world) {
    zox_prefab_child(prefab_character3D)
    zox_prefab_name("prefab_character3D_npc")
    zox_add_tag(e, RendererColored)
    zox_add_tag(e, Wanderer)
    zox_add_tag(e, Jumper)
    zox_prefab_set(e, RenderDisabled, { 1 })
    prefab_character3D_npc = e;
    return e;
}

ecs_entity_t spawn_character3D_npc(ecs_world_t *world, ecs_entity_t_array_d* entities, const ecs_entity_t vox, const float3 position, const float4 rotation, const byte character_lod, const byte render_disabled) {
    const ecs_entity_2 e = spawn_character3D(world, prefab_character3D_npc, vox, position, rotation, character_lod, 0, 0, render_disabled);
    add_to_ecs_entity_t_array_d(entities, e.x);
    return e.x;
}
