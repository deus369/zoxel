#if !defined(zoxm_cameras) && defined(zoxm_transforms)
#define zoxm_cameras

#include "data/_.c"
#include "settings/_.c"
#include "components/_.c"
#include "util/_.c"
#include "prefabs/_.c"
#include "systems/_.c"
#include "tests/planes_tests.c"
#include "cameras2/_.c"
#include "cameras3/_.c"
#include "util/player.c"
#include "debug/_.c"

zox_begin_module(Cameras)
    define_components_cameras(world);
    define_systems_cameras(world);
    spawn_prefabs_cameras(world);
    zox_import_module(Cameras2)
    zox_import_module(Cameras3)
zox_end_module(Cameras)

#endif