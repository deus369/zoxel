ecs_entity_t spawn_prefab_character3D_npc(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_character3D_npc")
    zox_add_tag(e, RendererColored)
    zox_add_tag(e, Wanderer)
    zox_add_tag(e, Jumper)
    zox_prefab_set(e, RenderDisabled, { 1 })
    return e;
}