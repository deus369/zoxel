#ifndef zox_editor_ui
#define zox_editor_ui

// todo: make basic structs just to read out generic component data

// todo: add_entity_to_labels should be a macro that takes in Tag so I can filter it with zox_has before adding: try these - Element, Character, Camera, Position3D, Position2D,
zox_declare_tag(EditorElement)
zox_declare_tag(HierarchyUI)
zox_declare_tag(InspectorLabel)
zox_component_byte(HierarchyUIDirty)
#include "prefabs/_.c"
#include "util/_.c"
#include "systems/_.c"

zox_begin_module(EditorUI)
    zox_define_tag(EditorElement)
    zox_define_tag(HierarchyUI)
    zox_define_tag(InspectorLabel)
    zox_define_component(HierarchyUIDirty)
    zox_define_systems_editor(world);
    spawn_prefabs_editor(world);
zox_end_module(EditorUI)

#endif