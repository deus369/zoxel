#include "statbar_system.c"
#include "stat_text_system.c"

void define_systems_stats_ui(ecs_world_t *world) {
    zox_system(StatbarSystem, EcsOnUpdate, [in] StatLink, [out] ElementBar, [none] Statbar)
    zox_system(StatTextSystem, EcsOnUpdate, [in] StatLink, [out] TextData, [out] ZextDirty, [none] StatsLabel)
}