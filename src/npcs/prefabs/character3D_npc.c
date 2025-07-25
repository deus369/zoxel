ecs_entity_t spawn_prefab_character3_npc(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("character3D_npc")
    zox_add_tag(e, Npc)
    zox_add_tag(e, RendererColored)
    zox_add_tag(e, Jumper)
    zox_prefab_set(e, Behaviour, { zox_behaviour_idle })
    zox_prefab_set(e, DefaultBehaviour, { zox_behaviour_wander })
    zox_prefab_set(e, MoveForwards, { 0 })
    zox_prefab_set(e, RotateTowards, { 0 })
    zox_prefab_set(e, MoveSpeed, { 4 })
    zox_prefab_add(e, TargetPosition)
    zox_prefab_add(e, ThreatPosition)
    zox_prefab_add(e, WanderDirection)
    zox_set(e, RenderDisabled, { 1 })
    return e;
}


// hook to spawning
void on_spawned_character3_npc(ecs_world_t* world, const ecs_entity_t e) {
    if (rand() % 100 <= 6) {
        zox_set(e, DefaultBehaviour, { zox_behaviour_idle })
    }
    if (rand() % 100 <= 40) {
        zox_add_tag(e, Coward)
    }
    if (disable_npc_movement) {
        zox_set(e, DisableMovement, { 1 })
    }
}
