#ifndef zoxel_editor_elements
#define zoxel_editor_elements

// settings
// zoxel_declare_components
zox_declare_tag(EditorUI)
// zox_component(QuadsCount, int)
// zoxel_include_prefabs
#include "prefabs/hierarchy.c"
#include "prefabs/inspector.c"
// zoxel_include_systems
// #include "systems/fps_display_system.c"

void spawn_prefabs_editor(ecs_world_t *world) {
    spawn_prefab_hierarchy(world);
    spawn_prefab_inspector(world);
}

zox_begin_module(EditorElements)
// zoxel_define_components
zox_define_tag(EditorUI)
// zox_define_component(QuadsCount)
// zoxel_define_systems
// zox_system(FpsDisplaySystem, EcsOnUpdate, [out] FPSDisplayTicker, [out] ZextDirty, [out] ZextData)
zoxel_end_module(EditorElements)

#endif
