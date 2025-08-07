#if !defined(zoxm_controllers) && defined(zoxm_characters) && defined(zoxm_inputs) && defined(zoxm_physics)
#define zoxm_controllers

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