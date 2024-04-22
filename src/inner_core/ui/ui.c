#ifndef zoxel_ui
#define zoxel_ui

#ifndef zoxel_on_android
#define default_ui_scale 1.0f
#else
#define default_ui_scale 2.0f
#endif
#include "core/ui_core.c"
#include "texts/texts.c"
#include "elements/elements.c"
#include "game/game_ui.c"
#include "editor/editor.c"
#include "fun/spawn_test_window.c"

void spawn_prefabs_ui(ecs_world_t *world) {
    spawn_prefabs_ui_core(world);
    spawn_prefabs_texts(world);
    spawn_prefabs_elements(world);
    spawn_prefabs_game_ui(world);
    spawn_prefabs_editor(world);
}

zox_begin_module(UI)
// zoxel_module_imports
zox_import_module(UICore)
zox_import_module(Texts)
zox_import_module(Elements)
zox_import_module(GameUI)
zox_import_module(EditorElements)
zoxel_end_module(UI)

#endif
