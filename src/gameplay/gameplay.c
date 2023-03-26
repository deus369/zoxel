#ifndef zoxel_gameplay
#define zoxel_gameplay

#include "stats/stats.c"
#include "skills/skills.c"
#include "items/items.c"
#include "crafting/crafting.c"
#include "farming/farming.c"
#include "actions/actions.c"
#include "dialogues/dialogues.c"
#include "quests/quests.c"
#include "characters/characters.c"
#include "turrets/turrets.c"
#include "classes/classes.c"
#include "jobs/jobs.c"
#include "races/races.c"
#include "clans/clans.c"
#include "combat/combat.c"
#include "maps/maps.c"
#include "lores/lores.c"
#include "achievements/achievements.c"

zoxel_begin_module(Gameplay)
zoxel_import_module(Stats)
zoxel_import_module(Skills)
zoxel_import_module(Items)
zoxel_import_module(Crafting)
zoxel_import_module(Farming)
zoxel_import_module(Actions)
zoxel_import_module(Dialogues)
zoxel_import_module(Quests)
zoxel_import_module(Characters)
zoxel_import_module(Turrets)
zoxel_import_module(Classes)
zoxel_import_module(Jobs)
zoxel_import_module(Races)
zoxel_import_module(Clans)
zoxel_import_module(Combat)
zoxel_import_module(Maps)
zoxel_import_module(Lores)
zoxel_import_module(Achievements)
zoxel_end_module(Gameplay)
#endif