// profiling: make build/dev && make run-dev-profiler
//todo: move our library wrappers to top of stack here:
//  flecs, sdl, opengl, etc

// release defines
// can we check if debug here?
#ifndef zox_debug
    #define zox_disable_names
    #define zox_disable_logs
#endif

// Platforms
#ifdef zox_windows
    #define max_args 64
    #define max_arg_len 256
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #include <shellapi.h>
#endif
#ifdef zox_web
    #include <emscripten.h>
#endif
#ifdef zox_android
    #include <android/log.h>
    #include <android/asset_manager.h>
    #include <android/asset_manager_jni.h>
    #include <SDL2/SDL_system.h>
    #include <sys/types.h>
#endif

// Libraries
#include "_.c" // defines our platform things too
// core includes
#include <signal.h>     // used for detecting cancel
#include <stdlib.h>     // for malloc & free
#include <stdio.h>      // just for sprintf and perror
#include <stdint.h>     // for ints?
// Memory Copies and Strlen!
#include <string.h>
// for thread locks in memory management - pthread_rwlock_init
#include <pthread.h>
// math module
#include <math.h>
#include <float.h>
// time module
#include <time.h>
// # Pathing #
// for DIR, readdir, closedir etc
#include <dirent.h>
// for pathing - can we do without?
#include <sys/stat.h>   // pathing
// used in pathing, doing funky stuff??
#include <unistd.h>
// also used in pathing - ENOENT
// and networking - EWOULDBLOCK
#include <errno.h>
//! Included Libraries for App
#ifndef zox_disable_logs
    #include <stdarg.h>
#endif

// SDL2 & OpenGL
#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL.h>
#ifdef zox_windows
    #include <GL/glew.h>
#endif
#include <SDL2/SDL_opengl.h>
#ifdef zox_sdl_images
    #include <SDL2/SDL_image.h>
#endif
#ifdef zox_vulkan
    #include <SDL2/SDL_vulkan.h>
    #include <vulkan/vulkan.h>
    #include <vulkan/vulkan_wayland.h>
#endif

// engine modules
#include "_/logs/_.c"
#include "_/collections/_.c"
#include "_/maths/_.c"
#include "flecs/_.c"

// todo: include all these automatically
#include "_/_.c"
#include "generic/_.c"
#include "timing/_.c"
#include "transforms/_.c"
#include "networking/_.c"
#include "inputs/_.c"
#include "apps/_.c"
#include "sdl/_.c"
#include "opengl/_.c"
#include "vulkan/_.c"

// basic b locks
#include "assets/_.c" // uses sdl path function atm
#include "nodes/_.c"
#include "realms/_.c"
#include "games/_.c"
#include "players/_.c"
#include "colors/_.c"

// beef
#include "cameras/_.c"
#include "rendering/_.c"
#include "sounds/_.c"

#include "raycasts/_.c"
#include "lines/_.c"

// inner core
#include "textures/_.c"
#include "musics/_.c"
#include "animations/_.c"
#include "bones/_.c"

#include "ui/_.c"
#include "lines/lines2/_.c"
#include "plots/_.c"

#include "genetics/_.c"
#include "neurals/_.c"
#include "cubes/_.c"
#include "blocks/_.c"
#include "chunks2/_.c"
#include "chunks3/_.c"
#include "voxes/_.c"

#include "models/_.c"
#include "weathers/_.c"
#include "terrain/_.c"
#include "physics/_.c"
#include "particles/_.c"
#include "blueprints/_.c"
#include "characters/_.c"
#include "dungeons/_.c"
#include "game_ui/_.c"
// user data
#include "users/_.c"
#include "combat/_.c"
#include "stats/_.c"
#include "items/_.c"
#include "skills/_.c"
#include "actions/_.c"
#include "dialogues/_.c"
#include "quests/_.c"
#include "classes/_.c"
#include "jobs/_.c"
#include "races/_.c"
#include "clans/_.c"
#include "lores/_.c"
#include "achievements/_.c"
#include "users/util/post_users.c"
// gameplay
#include "pickups/_.c"
#include "crafting/_.c"
#include "farming/_.c"
#include "turrets/_.c"
#include "combat/_.c"
#include "maps/_.c"
#include "npcs/_.c"
#include "editor_ui/_.c"
// on top
#include "controllers/_.c"
#include "space/_.c"
#include "debug/_.c"

// event used by testers atm
typedef byte (*boot_zox)(ecs_world_t*, ecs_entity_t);
boot_zox boot_event;

// engine imports, besides sub modules, it's core is flecs
zox_begin_module(Zox)
    zox_import_module(Core)
    zox_import_module(Generic)
    zox_import_module(Timing)
    zox_import_module(Transforms)
#ifndef zox_disable_module_networking // disabled on web atm
    zox_import_module(Networking)
#endif
    zox_import_module(Inputs)
    if (!headless) {
        zox_import_module(Apps)
        zox_import_module(Sdl)
    }
    zox_import_module(Assets)
    zox_import_module(Realms)
    zox_import_module(Games)
    zox_import_module(Players)
    zox_import_module(Nodes)
    zox_import_module(Colorz)

    zox_import_module(Cameras)
    zox_import_module(Rendering)
    zox_import_module(Sounds)

    zox_import_module(Raycasts)
    zox_import_module(Lines)

    zox_import_module(Texturez)
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

    zox_import_module(Models)
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

#include zox_nexus_game

int main(int argc, char* argv[]) {
#ifndef zox_mod_game
    zox_log_error("[zox_mod_game] not defined: game cannot load")
    return EXIT_FAILURE;
#endif
    fetch_pc_info();    // gets our cpu core count
    ecs_world_t *world = initialize_ecs(argc, argv, cpu_core_count);
    if (!world) {
        zox_log_error("[initialize_ecs] failed")
        return EXIT_FAILURE;
    }
    zox_logv("Loading Modules");
    zox_import_module(Zox)
    zox_import_module(ZoxGame)
    zox_logv("Running Terminal Commands");
    run_hook_terminal_command(world, argv, argc);
    zox_logv("Initializing ECS Settings");
    initialize_ecs_settings(world);                 // sets ecs threads
    zox_logv("Initializing SDL Video");
    if (initialize_sdl_video(world) == EXIT_FAILURE) {
        zox_log_error("[initialize_sdl_video] failed")
        dispose_zox(world);
        return EXIT_FAILURE;
    }
    // spawn app (creates our opengl context too)
    zox_logv("Spawning SDL Window");
    ecs_entity_t app = !headless ? spawn_window_opengl_with_icon(world) : 0;
    // inits glew on windows
    zox_logv("Initializing Rendering");
    initialize_rendering(world, render_backend);
    zox_logv("Initializing Glew");
    if (zox_init_glew() == EXIT_FAILURE) {
        zox_log_error("[initialize_rendering] failed")
        dispose_zox(world);
        return EXIT_FAILURE;
    }
    zox_logv("Initializing Sounds");
    initialize_sounds(world);                       // starts sdl mixer etc
    if (!headless && !app) {
        zox_log_error("[engine_spawn_window] failed")
        dispose_zox(world);
        return EXIT_FAILURE;
    }

    // loads all our files
    zox_logv("Loading Files All");
    run_hook_files_load(world);

    // black screen if no shaders btw
    zox_logv("Procecssing Shaders");
    process_shaders(world); // we should process them after loaded?

    // always have realm and game
    zox_logv("Spawning Realm and Game");
    const ecs_entity_t realm = spawn_realm(world, prefab_realm);
    const ecs_entity_t game = spawn_game(world, realm);
    zox_set(app, RealmLink, { realm });
    zox_set(app, GameLink, { game });

    zox_logv("Running our Boot Hook");
    run_hook_on_boot(world, app);
    if (boot_event && boot_event(world, app) == EXIT_FAILURE) {
        zox_log_error("[boot_event] failed")
        dispose_zox(world);
        return EXIT_FAILURE;
    }

    zox_logv("Running Main Loop [%s]", game_name);
    engine_loop(world);

    // return after loop ends; during a close event
    zox_logv("Ended Main Loop [%s]", game_name);
    return EXIT_SUCCESS;
}

#ifdef zox_windows

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    int argc = 0;
    wchar_t** argvW = CommandLineToArgvW(GetCommandLineW(), &argc);
    // Array to hold arguments
    static char argv_storage[max_args][max_arg_len];
    static char* argv[max_args];
    for (int i = 0; i < argc && i < max_args; i++) {
        // Convert wide char string to char string
        wcstombs(argv_storage[i], argvW[i], max_arg_len);
        argv_storage[i][max_arg_len - 1] = '\0'; // Ensure null termination
        argv[i] = argv_storage[i];
    }
    LocalFree(argvW); // Free memory allocated by CommandLineToArgvW
    return main(argc, argv);
}

#endif