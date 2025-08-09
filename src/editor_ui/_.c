#ifndef zoxm_editor
#define zoxm_editor

// todo: make basic structs just to read out generic component data

// todo: add_entity_to_labels should be a macro that takes in Tag so I can filter it with zox_has before adding: try these - Element, Character, Camera, Position3D, Position2D,
zox_tag(EditorElement);
zox_tag(HierarchyUI);
zox_tag(InspectorLabel);
zoxc_byte(HierarchyUIDirty);
#include "prefabs/_.c"
#include "util/_.c"
#include "systems/_.c"
#include "debug/_.c"

zox_begin_module(EditorUI)
    zox_define_tag(EditorElement);
    zox_define_tag(HierarchyUI);
    zox_define_tag(InspectorLabel);
    zox_define_component(HierarchyUIDirty);
    zox_define_systems_editor(world);
    add_hook_spawn_prefabs(spawn_prefabs_editor);
zox_end_module(EditorUI)

#endif