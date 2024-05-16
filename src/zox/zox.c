#ifndef zox_engine
#define zox_engine

// engine imports, besides sub modules, it's core is flecs
#include "../core/util/settings/build_settings.c"
#include "../core/util/settings/build_disables.c"
#define FLECS_CUSTOM_BUILD
#define FLECS_MODULE
#define FLECS_SYSTEM
#define FLECS_PIPELINE
#ifndef zox_disable_audio
#define SDL_MIXER
#endif
#include <signal.h> // used for detecting cancel
#include <string.h> // who uses this?
#include <stdlib.h> // for malloc & free
#include <stdio.h>  // just for sprintf and perror
#include "../../include/flecs.h"
#include "util/events.c"
#include "../core/core.c"
#include "util/game_store_util.c"
#include "../inner_core/inner_core.c"
#include "../outer_core/outer_core.c"
#include "../users/users.c"
#include "../gameplay/gameplay.c"
#include "../space/space.c"
#include "util/engine_util.c"
#include "util/main_loop_util.c"
#include "util/boot_util.c"
typedef unsigned char (*boot_zox)(ecs_world_t*);
boot_zox boot_event;
#include "util/zox_util.c"

zox_begin_module(Zox)
zox_import_module(Core)
zox_import_module(InnerCore)
zox_import_module(OuterCore)
zox_import_module(Users)
zox_import_module(Gameplay)
zox_import_module(Space)
zoxel_end_module(Zox)

#endif
