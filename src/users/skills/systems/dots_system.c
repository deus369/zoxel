// DotsSystem
void DotsSystem(ecs_iter_t *it) {
    const float damage_rate = 2.0f;
    const float delta_time = zox_delta_time;
    zox_iter_world()
    zox_field_in(Poison, poisons, 1)
    zox_field_in(Dead, deads, 2)
    zox_field_in(StatLinks, statLinkss, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Dead, deads, dead)
        if (dead->value) continue;
        zox_field_i_in(Poison, poisons, poison)
        if (!poison->value) continue;
        zox_field_i_in(StatLinks, statLinkss, statLinks)
        const ecs_entity_t health_stat = statLinks->value[0];
        StatValue *statValue = zox_get_mut(health_stat, StatValue)
        statValue->value -= delta_time * damage_rate;
        if (statValue->value < 0) statValue->value = 0;
        zox_modified(health_stat, StatValue)
    }
} zox_declare_system(DotsSystem)
