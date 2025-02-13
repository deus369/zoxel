#ifndef zox_mod_ui
#define zox_mod_ui

#include "core/core.c"
#include "zigels/zigels.c"
#include "texts/texts.c"
#include "elements/elements.c"

zox_begin_module(Elements)
    zox_import_module(ElementsCore)
    zox_import_module(Zigels)
    zox_import_module(Zexts)
    zox_import_module(SubElements)
zox_end_module(Elements)

#endif
