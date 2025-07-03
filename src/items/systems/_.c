zox_declare_system_state_event(RealmItems, GenerateRealm, zox_generate_realm_items, spawn_realm_items)

void zox_define_systems_items(ecs_world_t *world) {
    zox_define_system_state_event_1(RealmItems, EcsOnLoad, GenerateRealm) // , [none] realms.Realm)
}