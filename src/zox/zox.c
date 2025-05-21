#ifndef zox_mod_engine
#define zox_mod_engine

#include "data/settings.c"
#include "util/engine.c"
#include "util/window.c"

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
        zox_import_module(Sdl)
    }
    zox_import_module(Assets)
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
    zox_import_module(GameUI)
    zox_import_module(EditorUI)
    #endif
    zox_import_module(Lines)
    zox_import_module(Plots)
    zox_import_module(Genetics)
    zox_import_module(Neurals)
    zox_import_module(Tiles)
    zox_import_module(Cubes)
    zox_import_module(Voxels)
    zox_import_module(Voxes)
    zox_import_module(Weathers)
    zox_import_module(Terrain)
    zox_import_module(Physics)
    zox_import_module(Particles)
    zox_import_module(Blueprints)
    zox_import_module(Characters)
    // user data
    zox_import_module(Users)
    zox_import_module(Combat)
    zox_import_module(Stats)
    zox_import_module(Items)
    zox_import_module(Skills)
    zox_import_module(Actions)
    zox_import_module(Dialogues)
    zox_import_module(Quests)
    zox_import_module(Classes)
    zox_import_module(Jobs)
    zox_import_module(Races)
    zox_import_module(Clans)
    zox_import_module(Lores)
    zox_import_module(Achievements)
    // gameplay
    zox_import_module(Pickups)
    zox_import_module(Crafting)
    zox_import_module(Farming)
    zox_import_module(Turrets)
    zox_import_module(Maps)
    zox_import_module(AI)
    // space
    #if defined(zox_mod_players)
    if (!headless) {
        zox_import_module(Controllers)
        zox_import_module(Space)
    }
    #endif
    #if defined(zox_mod_debug)
    zox_import_module(Debug)
    #endif
zox_end_module(Zox)

#endif
