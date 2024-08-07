#ifndef zox_mod_engine
#define zox_mod_engine

#include "data/build_settings.c"
#include "data/build_disables.c"
#include "util/defines.c"
#include zox_nexus_defines
#include "util/events.c"
#include "util/includes.c"
#include "data/settings.c"
#include "util/ui.c"
#include "util/camera.c"
#include "util/boot_util.c"
#include "util/engine.c"

// engine imports, besides sub modules, it's core is flecs
zox_begin_module(Zox)
zox_import_module(Core)
#ifdef zox_mod_inner_core
    zox_import_module(InnerCore)
#endif
#ifdef zox_mod_users
    zox_import_module(Users)
#endif
#ifdef zox_mod_gameplay
    zox_import_module(Gameplay)
#endif
#ifdef zox_mod_space
    zox_import_module(Space)
#endif
zoxel_end_module(Zox)

#endif
