#ifndef zox_editor_ui
#define zox_editor_ui

// todo: add_entity_to_labels should be a macro that takes in Tag so I can filter it with zox_has before adding: try these - Element, Character, Camera, Position3D, Position2D,
zox_declare_tag(EditorElement)
zox_declare_tag(HierarchyUI)
zox_declare_tag(InspectorLabel)
zox_component_byte(HierarchyUIDirty)
#include "prefabs/_.c"
#include "util/_.c"
#include "systems/hierarchy_refresh_system.c"
#include "systems/inspector_element_system.c"

void spawn_prefabs_editor(ecs_world_t *world) {
    spawn_prefab_hierarchy(world);
    spawn_prefab_inspector(world);
}

zox_begin_module(EditorUI)
    zox_define_tag(EditorElement)
    zox_define_tag(HierarchyUI)
    zox_define_tag(InspectorLabel)
    zox_define_component(HierarchyUIDirty)
    zox_system(InspectorElementSystem, EcsOnUpdate,
        [none] InspectorLabel,
        [in] generic.EntityTarget,
        [in] generic.ComponentTarget)
    zox_system_1(HierarchyRefreshSystem, main_thread_pipeline,
        [none] HierarchyUI,
        [in] transforms2.d.Position2D,
        [in] elements.core.CanvasPosition,
        [in] elements.core.Layer2D,
        [in] elements.core.Anchor,
        [in] elements2.d.ListUIMax,
        [in] elements.core.ElementFontSize,
        [in] elements.core.CanvasLink,
        [out] HierarchyUIDirty,
        [out] layouts2.d.PixelPosition,
        [out] layouts2.d.PixelSize,
        [out] textures.core.TextureSize,
        [out] hierarchys.Children)
    spawn_prefabs_editor(world);
zox_end_module(EditorUI)

#endif