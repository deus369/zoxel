/*
 *  Zox Core
 *
 *      > Maths, Generics, App, Rendering, Files, Etc
 *
 *  The Lowest of the Lows
*/
#ifndef zox_mod_core
#define zox_mod_core

// global variables
unsigned char cpu_tier;
#include "../util/util.c"
#include "../platforms/util/platform_defines.c"
#include "../collections/collections.c"
#include "../ecs/ecs.c"
#include "../maths/maths.c"
#include "../platforms/platforms.c"
#include "../generic/generic.c"
#include "../timing/timing.c"
#include "../transforms/transforms.c"
#include "../networking/networking.c"
#include "../terminals/terminals.c"
#include "../players/players.c"
#include "../inputs/inputs.c"
#include "../apps/apps.c"          // test removing sdl for engine stability
#include "../files/files.c"        // uses sdl path function atm
#include "../cameras/cameras.c"
#include "../rendering/rendering.c"
#include "../sounds/sounds.c"
#include "../nodes/nodes.c"
#include "../realms/realms.c"
#include "../games/games.c"
#include "../raycasts/raycasts.c"
#include "../colors/colors.c"

zox_begin_module(Core)
clear_zoxel_log();
zox_import_module(Platforms)
zox_import_module(Generic)
zox_import_module(Maths)
zox_import_module(Timing)
zox_import_module(Transforms)
zox_import_module(Files)
zox_import_module(Terminals)
#ifndef zox_disable_module_networking // disabled on web atm
zox_import_module(Networking)
#endif
zox_import_module(Players)
zox_import_module(Inputs)
initialize_pathing();
if (!headless) zox_import_module(Apps) // sdl
zox_import_module(Cameras)
zox_import_module(Rendering)
zox_import_module(Sounds)
zox_import_module(Nodes)
zox_import_module(Realms)
zox_import_module(Games)
zox_import_module(Raycasts)
zox_import_module(Colorz)
zoxel_end_module(Core)

#endif
