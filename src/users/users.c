#ifndef zoxel_users
#define zoxel_users

#include "stats/stats.c"
#include "skills/skills.c"
#include "items/items.c"
#include "actions/actions.c"
#include "dialogues/dialogues.c"
#include "quests/quests.c"
#include "classes/classes.c"
#include "jobs/jobs.c"
#include "races/races.c"
#include "clans/clans.c"
#include "lores/lores.c"
#include "achievements/achievements.c"

void spawn_prefabs_users(ecs_world_t *world) {
    spawn_prefabs_stats(world);
}

zox_begin_module(Users)
zox_import_module(Stats)
zox_import_module(Skills)
zox_import_module(Items)
zox_import_module(Actions)
zox_import_module(Dialogues)
zox_import_module(Quests)
zox_import_module(Classes)
zox_import_module(Jobs)
zox_import_module(Races)
zox_import_module(Clans)
zox_import_module(Lores)
zox_import_module(Achievements)
zoxel_end_module(Users)

#endif