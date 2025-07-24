#ifndef zox_mod_ui
#define zox_mod_ui

#include "core/core.c"
#include "zigels/zigels.c"
#include "texts/texts.c"
#include "elements2D/elements2D.c"
#include "elements3D/elements3D.c"

zox_begin_module(Elements)
    zox_import_module(ElementsCore)
    zox_import_module(Zigels)
    zox_import_module(Texts)
    zox_import_module(Elements2)
    zox_import_module(Elements3)
zox_end_module(Elements)

#endif