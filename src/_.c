#ifndef zox_mod_engine
#define zox_mod_engine

//todo: move our library wrappers to top of stack here:
//  flecs, sdl, opengl, etc

// pre engine defines
#include "zox/data/build_settings.c"
#include "zox/data/build_disables.c"
#include "zox/data/define_groups.c"
#include "zox/util/defines.c"

// engine modules
#include "_/logs/_.c"
#include "_/collections/_.c"
#include "_/maths/_.c"
#include "flecs/_.c"

// todo: include all these automatically
#include "_/_.c"
#include "generic/generic.c"
#include "timing/timing.c"
#include "transforms/transforms.c"
#include "networking/networking.c"
#include "players/players.c"
#include "inputs/inputs.c"
#include "apps/apps.c"
#include "sdl/sdl.c"
#include "opengl/_.c"
#include "vulkan/_.c"

// basic b locks
#include "assets/assets.c" // uses sdl path function atm
#include "nodes/nodes.c"
#include "realms/realms.c"
#include "games/games.c"
#include "colors/colors.c"

// beef
#include "cameras/_.c"
#include "rendering/_.c"
#include "sounds/sounds.c"

#include "raycasts/raycasts.c"
#include "lines/lines.c"

// inner core
#include "textures/textures.c"
#include "musics/musics.c"
#include "animations/animations.c"
#include "bones/bones.c"

#include "ui/ui.c"
#include "lines/lines2D/lines2D.c"
#include "plots/plots.c"

#include "genetics/genetics.c"
#include "neurals/neurals.c"
#include "cubes/cubes.c"
#include "blocks/_.c"
#include "chunks2/_.c"
#include "chunks3/_.c"
#include "voxes/voxes.c"
#include "weathers/weathers.c"
#include "terrain/_.c"
#include "physics/_.c"
#include "particles/particles.c"
#include "blueprints/blueprints.c"
#include "characters/_.c"
#include "dungeons/dungeons.c"
#include "game_ui/game_ui.c"
// user data
#include "users/users.c"
#include "combat/combat.c"
#include "stats/stats.c"
#include "items/items.c"
#include "skills/skills.c"
#include "actions/actions.c"
#include "dialogues/dialogues.c"
#include "quests/quests.c"
#include "classes/classes.c"
#include "jobs/jobs.c"
#include "races/races.c"
#include "clans/clans.c"
#include "lores/lores.c"
#include "achievements/achievements.c"
#include "users/util/post_users.c"
// gameplay
#include "pickups/pickups.c"
#include "crafting/crafting.c"
#include "farming/farming.c"
#include "turrets/turrets.c"
#include "combat/combat.c"
#include "maps/maps.c"
#include "ai/_.c"
#include "editor_ui/editor_ui.c"
// on top
#include "controllers/_.c"
#include "space/space.c"
#include "debug/debug.c"

#include "zox/data/settings.c"
#include "zox/util/engine.c"
#include "zox/util/window.c"

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
        zox_import_module(Apps)
        zox_import_module(Sdl)
    }
    zox_import_module(Assets)
    zox_import_module(Realms)
    zox_import_module(Games)
    zox_import_module(Nodes)
    zox_import_module(Colorz)

    zox_import_module(Cameras)
    zox_import_module(Rendering)
    zox_import_module(Sounds)

    zox_import_module(Raycasts)
    zox_import_module(Lines)

    zox_import_module(Textures)
    zox_import_module(Musics)
    zox_import_module(Animations)
    zox_import_module(Bones)
    zox_import_module(Elements)
    zox_import_module(Lines2D)
    zox_import_module(Plots)

    zox_import_module(Genetics)
    zox_import_module(Neurals)
    zox_import_module(Cubes)

    zox_import_module(Blocks)
    zox_import_module(Tiles)
    zox_import_module(Chunks3)
    zox_import_module(Voxes)

    zox_import_module(Weathers)
    zox_import_module(Terrain)
    zox_import_module(Physics)
    zox_import_module(Particles)
    zox_import_module(Blueprints)
    zox_import_module(Characters)
    zox_import_module(Dungeons)
    zox_import_module(GameUI)

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
    zox_import_module(Npcs)
    zox_import_module(EditorUI)
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