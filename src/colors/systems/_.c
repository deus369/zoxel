#include "realm_colors_generate_system.c"
zox_declare_system_state_event(RealmColors, GenerateRealm, zox_generate_realm_colors, spawn_realm_colors)

void define_systems_colors(ecs_world_t *world) {
    zox_define_system_state_event_1(RealmColors, EcsOnLoad, GenerateRealm)
}