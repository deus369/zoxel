#ifndef zox_mod_gameplay
#define zox_mod_gameplay

#include "crafting/crafting.c"
#include "farming/farming.c"
#include "turrets/turrets.c"
#include "combat/combat.c"
#include "maps/maps.c"
#include "ai/ai.c"

zox_begin_module(Gameplay)
zox_import_module(Crafting)
zox_import_module(Farming)
zox_import_module(Turrets)
zox_import_module(Combat)
zox_import_module(Maps)
zox_import_module(AI)
zoxel_end_module(Gameplay)

#endif
