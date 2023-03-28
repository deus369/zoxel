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

zoxel_begin_module(Users)
zoxel_import_module(Stats)
zoxel_import_module(Skills)
zoxel_import_module(Items)
zoxel_import_module(Actions)
zoxel_import_module(Dialogues)
zoxel_import_module(Quests)
zoxel_import_module(Classes)
zoxel_import_module(Jobs)
zoxel_import_module(Races)
zoxel_import_module(Clans)
zoxel_import_module(Lores)
zoxel_import_module(Achievements)
zoxel_end_module(Users)

#endif