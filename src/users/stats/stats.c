#ifndef zoxel_stats
#define zoxel_stats

// zoxel_component_declares
zox_declare_tag(StateStat)
zox_declare_tag(LevelStat)
zox_declare_tag(HealthStat)
zox_declare_user_data(Stat)
zox_component_float(StatValue)
zox_component_float(StatValueMax)
zox_component_float(ExperienceValue)
zox_component_float(ExperienceMax)
zox_create_user_data_prefabs(Stat, stat, "stat")
// zoxel_prefab_includes
#include "prefabs/stat.c"
// zoxel_system_includes
#include "systems/stat_regen_system.c"
#include "systems/death_system.c"
// modules
#include "ui/ui.c"

int get_stat_label(ecs_world_t *world, char buffer[], int buffer_size, int buffer_index) {
    if (local_character3D) {
        const UserStatLinks *userStatLinks = zox_get(local_character3D, UserStatLinks)
        ecs_entity_t soul_stat = userStatLinks->value[1];
        float level = zox_get_value(soul_stat, StatValue)
        float experience_value = zox_get_value(soul_stat, ExperienceValue)
        float experience_max = zox_get_value(soul_stat, ExperienceMax)
        buffer_index += snprintf(buffer + buffer_index, buffer_size, " lvl %i [%i/%i] ", (int) level, (int) experience_value, (int) experience_max);
    }
    return buffer_index;
}

void spawn_prefabs_stats(ecs_world_t *world) {
    spawn_prefab_user_stat(world);
    spawn_prefabs_stats_ui(world);
}

zox_begin_module(Stats)
// components
zox_define_tag(StateStat)
zox_define_tag(LevelStat)
zox_define_tag(HealthStat)
zox_define_user_data(Stat)
zox_define_component(StatValue)
zox_define_component(StatValueMax)
zox_define_component(ExperienceValue)
zox_define_component(ExperienceMax)
// systems
// debuff system here, skills will add debuffs
zox_system(DeathCleanSystem, EcsOnUpdate, [in] Dead, [in] DiedTime)
zox_system(DeathSystem, EcsOnUpdate, [none] HealthStat, [in] StatValue, [in] UserLink)
zox_system(StatRegenSystem, EcsPostUpdate, [in] UserLink, [in] StatValueMax, [out] StatValue)
// zox_system(DeathShrinkSystem, EcsOnUpdate, [in] Dead, [in] DiedTime, [out] Scale1D)
// sub modules
zox_import_module(StatsUI)
zoxel_end_module(Stats)

#endif
