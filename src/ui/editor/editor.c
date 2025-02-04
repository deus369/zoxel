#ifndef zox_editor_elements
#define zox_editor_elements

// todo: add_entity_to_labels should be a macro that takes in Tag so I can filter it with zox_has before adding: try these - Element, Character, Camera, Position3D, Position2D,
zox_declare_tag(EditorElement)
zox_declare_tag(HierarchyUI)
zox_declare_tag(InspectorLabel)
zox_component_byte(HierarchyUIDirty)
#include "prefabs/hierarchy.c"
#include "prefabs/inspector.c"
#include "util/shared.c"
#include "util/inspector_util.c"
#include "util/hierarchy_util.c"
#include "systems/hierarchy_refresh_system.c"
#include "systems/inspector_element_system.c"

void spawn_prefabs_editor(ecs_world_t *world) {
    spawn_prefab_hierarchy(world);
    spawn_prefab_inspector(world);
}

zox_begin_module(EditorElements)
    zox_define_tag(EditorElement)
    zox_define_tag(HierarchyUI)
    zox_define_tag(InspectorLabel)
    zox_define_component(HierarchyUIDirty)
    zox_system(InspectorElementSystem, EcsOnUpdate, [none] InspectorLabel, [in] EntityTarget, [in] ComponentTarget)
    zox_system_1(HierarchyRefreshSystem, main_thread_pipeline, [none] HierarchyUI, [in] Position2D, [in] CanvasPosition, [in] Layer2D, [in] Anchor, [in] ListUIMax, [in] ElementFontSize, [in] CanvasLink, [out] HierarchyUIDirty, [out] PixelPosition, [out] PixelSize, [out] TextureSize, [out] Children)
    spawn_prefabs_editor(world);
zoxel_end_module(EditorElements)

#endif
