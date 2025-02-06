#ifndef zox_mod_ui
#define zox_mod_ui

#include "core/core.c"
#include "zigels/zigels.c"
#include "texts/texts.c"
#include "elements/elements.c"

zox_begin_module(Elements)
    initialize_module_ui(world);
    zox_import_module(Zigels)
    zox_import_module(Zexts)
    zox_import_module(Zelements)
zoxel_end_module(Elements)

#endif
