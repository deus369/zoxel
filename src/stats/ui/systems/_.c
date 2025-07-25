#include "statbar_system.c"
#include "stat_text_system.c"
#include "healthbar_spawner.c"

void define_systems_stats_ui(ecs_world_t *world) {
    zox_system(StatbarSystem, EcsOnUpdate,
            [in] StatLink,
            [out] elements.core.ElementBar,
            [none] Statbar)
    zox_system(StatTextSystem, EcsOnUpdate,
            [in] StatLink,
            [out] texts.TextData,
            [out] texts.ZextDirty,
            [none] StatsLabel)
    zox_system_1(HealthbarSpawnerSystem, EcsOnUpdate,
            [in] combat.InCombat,
            [in] stats.StatLinks,
            [out] elements.core.ElementLinks)
}