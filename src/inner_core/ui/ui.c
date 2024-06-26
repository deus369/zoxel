#ifndef zox_mod_ui
#define zox_mod_ui

#include "core/ui_core.c"
#include "zigels/zigels.c"
#include "texts/texts.c"
#include "elements/elements.c"
#include "game/game_ui.c"
#include "editor/editor.c"
#include "fun/spawn_test_window.c"

zox_begin_module(UI)
zox_import_module(UICore)
zox_import_module(Zigels)
zox_import_module(Zexts)
zox_import_module(Elements)
zox_import_module(GameUI)
zox_import_module(EditorElements)
zoxel_end_module(UI)

#endif
