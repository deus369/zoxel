#ifndef zoxel_ui_core
#define zoxel_ui_core

// 0 | EcsPostUpdate
#define ui_mesh_pipeline 0
long int element_mesh_system_id;
ecs_entity_t main_canvas;
zoxel_declare_tag(Element)                  //! A basic tag for a UI Element.
zoxel_declare_tag(Canvas)
zoxel_declare_tag(ElementRaycaster)
zoxel_component(CanvasPixelPosition, int2)
zoxel_component(Anchor, float2)             //! An anchor, used to get base position using canvas
zoxel_component(CanvasLink, ecs_entity_t)   //! A link to a canvas
zoxel_byte_component(InitializeEntityMesh)
#include "util/ui_util.c"
#include "prefabs/canvas.c"
#include "prefabs/element.c"
#include "systems/element_raycast_system.c"
#include "systems/element_selected_system.c"
#include "systems/element_activate_system.c"
#include "systems/element_position_system.c"
#include "systems/element_mesh_system.c"

zoxel_begin_module(UICore)
zoxel_define_tag(Element)
zoxel_define_tag(Canvas)
zoxel_define_tag(ElementRaycaster)
zoxel_define_component(CanvasPixelPosition)
zoxel_define_component(Anchor)
zoxel_define_component(CanvasLink)
zoxel_define_component(InitializeEntityMesh)
zoxel_filter(ui_query, world, [none] Element, [in] CanvasPixelPosition, [in] PixelSize, [in] Layer2D, [out] SelectableState)
zoxel_filter(pixel_positions_query, world, [none] Element, [in] PixelPosition,
    [none] ParentLink, [none] Anchor, [none] CanvasLink, [none] Position2D, [none] CanvasPixelPosition)
zoxel_system_ctx(world, ElementPositionSystem, EcsPreUpdate, pixel_positions_query, [none] Element, [in] PixelPosition,
    [in] ParentLink, [in] Anchor, [in] CanvasLink, [out] Position2D, [out] CanvasPixelPosition)
zoxel_system_ctx(world, ElementRaycastSystem, EcsOnUpdate, ui_query, [in] Raycaster, [out] RaycasterTarget)
zoxel_system(ElementSelectedSystem, EcsOnUpdate, [out] Element, [in] SelectableState, [out] Brightness)
if (!headless) {
    #ifdef zoxel_inputs
        zoxel_system(ElementActivateSystem, EcsPostUpdate, [in] Mouse, [in] RaycasterTarget)
    #endif
    zoxel_system_main_thread(world, ElementMeshSystem, ui_mesh_pipeline, [none] Element, [in] PixelSize, [in] CanvasLink, [out] InitializeEntityMesh, [out] MeshDirty, [out] GenerateTexture)
    element_mesh_system_id = ecs_id(ElementMeshSystem);
}
spawn_prefab_canvas(world);
spawn_prefab_element(world);
zoxel_end_module(UICore)

// \todo Display a UI Element anchored, with a pixel position.
// \todo Change colour when ray hits a button.
//! \todo When resizing, reposition UIs.
//      - should i use a resize event in the window?
// completely 2D ui? 3D canvas + 3D transforms?
// canvas: still uses 2D posti

#endif