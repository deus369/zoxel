#ifndef zoxel_editor_elements
#define zoxel_editor_elements

// settings
// zoxel_declare_components
zox_declare_tag(EditorElement)
zox_declare_tag(HierarchyUI)
zox_component_byte(HierarchyUIDirty)
// zoxel_include_prefabs
#include "prefabs/hierarchy.c"
#include "prefabs/inspector.c"
// zoxel_include_util
#include "util/shared.c"
#include "util/inspector_util.c"
// zoxel_include_systems
#include "systems/hierarchy_refresh_system.c"
#include "systems/inspector_element_system.c"

void spawn_prefabs_editor(ecs_world_t *world) {
    spawn_prefab_hierarchy(world);
    spawn_prefab_inspector(world);
}

zox_begin_module(EditorElements)
// zoxel_define_components
zox_define_tag(EditorElement)
zox_define_tag(HierarchyUI)
zox_define_component(HierarchyUIDirty)
// zoxel_define_systems
zox_system_1(HierarchyRefreshSystem, main_thread_pipeline, [none] HierarchyUI, [in] Position2D, [in] CanvasPixelPosition, [in] Layer2D, [in] ListUIMax, [in] ElementFontSize, [out] HierarchyUIDirty, [out] PixelSize, [out] TextureSize, [out] Children)
zoxel_end_module(EditorElements)

#endif
