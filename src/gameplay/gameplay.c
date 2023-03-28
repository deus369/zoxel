#ifndef zoxel_gameplay
#define zoxel_gameplay

#include "crafting/crafting.c"
#include "farming/farming.c"
#include "characters/characters.c"
#include "turrets/turrets.c"
#include "combat/combat.c"
#include "maps/maps.c"

zoxel_begin_module(Gameplay)
zoxel_import_module(Crafting)
zoxel_import_module(Farming)
zoxel_import_module(Characters)
zoxel_import_module(Turrets)
zoxel_import_module(Combat)
zoxel_import_module(Maps)
zoxel_end_module(Gameplay)

#endif