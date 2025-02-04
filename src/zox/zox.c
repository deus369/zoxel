#ifndef zox_mod_engine
#define zox_mod_engine

// big defines
#include "data/build_settings.c"
#include "data/build_disables.c"
#include "data/define_groups.c"
#include "util/defines.c"
#include zox_nexus_defines
// our engine
#include "../_includes.c"
#include "data/settings.c"
#include "util/engine.c"

// engine imports, besides sub modules, it's core is flecs
zox_begin_module(Zox)
    zox_import_module(Core)
    zox_import_module(Generic)
    zox_import_module(Timing)
    zox_import_module(Transforms)
    #ifndef zox_disable_module_networking // disabled on web atm
        zox_import_module(Networking)
    #endif
    zox_import_module(Players)
    zox_import_module(Inputs)
    if (!headless) {
        zox_import_module(Apps) // sdl
    }
    zox_import_module(Files)
    zox_import_module(Cameras)
    zox_import_module(Rendering)
    zox_import_module(Sounds)
    zox_import_module(Nodes)
    zox_import_module(Realms)
    zox_import_module(Games)
    zox_import_module(Raycasts)
    zox_import_module(Colorz)

    zox_import_module(Textures)
    zox_import_module(Musics)
    zox_import_module(Animations)
    zox_import_module(Bones)
    #ifdef zox_mod_ui
    zox_import_module(Elements)
    #endif
    zox_import_module(Lines)
    zox_import_module(Plots)
    zox_import_module(Genetics)
    zox_import_module(Neurals)
    zox_import_module(Tiles)
    zox_import_module(Voxels)
    zox_import_module(Physics)
    zox_import_module(Cubes)
    zox_import_module(Particles)
    zox_import_module(Blueprints)
    zox_import_module(Characters)

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
