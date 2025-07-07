zox_declare_system_state_event(RealmItems, GenerateRealm, zox_generate_realm_items, spawn_realm_items)

void define_systems_items(ecs_world_t *world) {
    zox_define_system_state_event_1(RealmItems, EcsOnLoad, realms.GenerateRealm, [none] realms.Realm)
}