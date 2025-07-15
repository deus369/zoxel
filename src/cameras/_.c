#if !defined(zox_mod_cameras) && defined(zox_mod_transforms)
#define zox_mod_cameras

#include "data/_.c"
#include "settings/_.c"
#include "components/_.c"
#include "util/_.c"
#include "prefabs/_.c"
#include "systems/_.c"
#include "tests/planes_tests.c"
#include "cameras2/_.c"
#include "cameras3/_.c"

zox_begin_module(Cameras)
    define_components_cameras(world);
    define_systems_cameras(world);
    spawn_prefabs_cameras(world);
    zox_import_module(Cameras2)
    zox_import_module(Cameras3)
zox_end_module(Cameras)

#endif