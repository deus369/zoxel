void on_overlap_pickup(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t e2) {
    if (!zox_gett_value(e, PickedUp) && zox_has(e2, PickUpperer)) {
        zox_set(e, PickedUp, { pickup_state_trigger })
        zox_set(e, CollisionDisabled, { 1 })
        // zox_log(" > e [%lu] picked up by e2 [%lu]\n", e, e2)
    }
}
