#ifndef zoxel_gameplay
#define zoxel_gameplay

#include "crafting/crafting.c"
#include "farming/farming.c"
#include "characters/characters.c"
#include "turrets/turrets.c"
#include "combat/combat.c"
#include "maps/maps.c"

zox_begin_module(Gameplay)
zox_import_module(Crafting)
zox_import_module(Farming)
zox_import_module(Characters)
zox_import_module(Turrets)
zox_import_module(Combat)
zox_import_module(Maps)
zoxel_end_module(Gameplay)

#endif