#ifndef zoxm_ui
#define zoxm_ui

#include "core/_.c"
#include "zigels/_.c"
#include "texts/_.c"
#include "elements2D/_.c"
#include "elements3D/_.c"
#include "touch/_.c"

zox_begin_module(Elements)
    zox_import_module(ElementsCore)
    zox_import_module(Zigels)
    zox_import_module(Texts)
    zox_import_module(Elements2)
    zox_import_module(Elements3)
    zox_import_module(Touch)
zox_end_module(Elements)

#endif