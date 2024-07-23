void spawn_realm_achievements(ecs_world_t *world, const ecs_entity_t realm) {
    // zox_get_muter(realm, AchievementLinks, achievements)
    // clear previous
    // for (int i = 0; i < achievements->length; i++) if (achievements->value[i]) zox_delete(achievements->value[i])
    // initialize_memory_component(AchievementLinks, achievements, ecs_entity_t, 1)

#ifdef zox_log_realm_generate
    zox_log(" + generated realm [achievements]\n")
#endif
}
