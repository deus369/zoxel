#ifndef zoxel_engine
#define zoxel_engine

// todo: move some things to sdl module in core

// platforms
#if defined(__unix__) && __ANDROID__
    #define ANDROID_BUILD
#endif
#ifdef __EMSCRIPTEN__
    #define WEB_BUILD
#endif
#ifdef _WIN32
    #define WINDOWS_BUILD
#endif
// flecs
#define FLECS_CUSTOM_BUILD
#define FLECS_MODULE
#define FLECS_SYSTEM 
#define FLECS_PIPELINE
#include "../include/flecs/flecs.h"
// sdl
#define SDL_IMAGES
#define SDL_MIXER
// #define USE_SDL_3
#include "build_settings.c"
#include <signal.h> // used for detecting cancel
#include <string.h> // who uses this?
#include <stdlib.h> // for malloc & free
#include <stdio.h>  // just for sprintf and perror

// =-= Zoxel Engine =-=
unsigned char running = 1;
unsigned char headless = 0;
unsigned char server_mode = 0;

//! Quits the application from running indefinitely.
void exit_game() {
    running = 0;
    #ifdef WEB_BUILD
    emscripten_cancel_main_loop();
    #endif
}

void sigint_handler(int sig) {
    // Signal was SIGINT
    // zoxel_log("Zoxel Engine is closing from control + c.\n");
    exit_game();
}

#include "core/core.c"
#include "inner_core/inner_core.c"
#include "outer_core/outer_core.c"
#include "gameplay/gameplay.c"
#include "space/space.c"

int begin(int argc, char* argv[]) {
    return begin_core(argc, argv);
}

void end() {
    close_audio_sdl();
    close_core();
    dispose_vox_files();
}

void main_update() {
    #ifdef zoxel_time_main_loop
        begin_timing()
    #endif
    iterate_fps_time();
    update_core();
    #ifdef zoxel_time_main_loop
        did_do_timing()
        end_timing_cutoff("main_update", zoxel_time_main_loop_cutoff)
    #endif
}

//! Includes special case for emscripten.
void main_loop() {
    // Set up the signal handler for SIGINT
    signal(SIGINT, sigint_handler);
#ifdef WEB_BUILD
    emscripten_set_main_loop(&main_update, -1, 1); // old - 60, 1);
#else
    while (running)
    {
        main_update();
    }
#endif
}

void ZoxelEngineImport(ecs_world_t *world) {
    zoxel_module(ZoxelEngine)
    clear_zoxel_log();
    zoxel_import_module(Core)
    zoxel_import_module(InnerCore)
    zoxel_import_module(OuterCore)
    zoxel_import_module(Gameplay)
    zoxel_import_module(Space)
    zoxel_log(" > imported zoxel engine\n");
}
#endif