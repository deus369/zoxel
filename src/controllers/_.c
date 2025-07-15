#if !defined(zox_mod_controllers) && defined(zox_mod_characters) && defined(zox_mod_inputs) && defined(zox_mod_physics)
#define zox_mod_controllers

#include "data/settings.c"
#include "controllers2/_.c"
#include "controllers3/_.c"
#include "free_roam/free_roam.c"

zox_begin_module(Controllers)
    if (headless) {
        return;
    }
    zox_import_module(Controllers2)
    zox_import_module(Controllers3)
    zox_import_module(FreeRoam)
zox_end_module(Controllers)

#endif