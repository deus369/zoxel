#ifndef zox_engine
#define zox_engine

#include "data/build_settings.c"
#include "data/build_disables.c"
#include "util/defines.c"
#include "util/events.c"
#include "util/includes.c"
#include "data/settings.c"
#include "util/boot_util.c"
#include "util/engine.c"
#include "util/zox_util.c"

// engine imports, besides sub modules, it's core is flecs
zox_begin_module(Zox)
zox_import_module(Core)
zox_import_module(InnerCore)
// zox_import_module(OuterCore)
zox_import_module(Users)
zox_import_module(Gameplay)
zox_import_module(Space)
zoxel_end_module(Zox)

#endif
