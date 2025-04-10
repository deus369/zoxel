#if !defined(zox_mod_controllers) && defined(zox_mod_characters) && defined(zox_mod_inputs) && defined(zox_mod_physics)
#define zox_mod_controllers

#include "data/settings.c"
#include "controllers2D/controllers2D.c"
#include "controllers3D/controllers3D.c"
#include "free_roam/free_roam.c"

zox_begin_module(Controllers)
    if (headless) {
        return;
    }
    zox_import_module(Controllers2D)
    zox_import_module(Controllers3D)
    zox_import_module(FreeRoam)
zox_end_module(Controllers)

#endif