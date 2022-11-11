#ifndef zoxel_ui_core
#define zoxel_ui_core

//! \todo When resizing, reposition UIs.
//      - should i use a resize event in the window?

// completely 2D ui? 3D canvas + 3D transforms?
// canvas: still uses 2D posti

// tags
//! A basic tag for a UI Element.
ECS_DECLARE(Element);
ECS_DECLARE(Selectable);
ECS_DECLARE(Clickable);
ECS_DECLARE(Canvas);
ECS_DECLARE(ElementRaycaster);
// UI extras, make extra ui module?
ECS_DECLARE(Button);
// components
zoxel_component(PixelPosition, int2);
zoxel_component(PixelSize, int2);
//! An anchor, used to get base position using canvas
zoxel_component(Anchor, float2);
zoxel_component(CanvasLink, ecs_entity_t);
// prefabs
#include "prefabs/canvas.c"
#include "prefabs/element.c"
#include "prefabs/button.c"
// systems
#include "systems/element_raycast_system.c"

//! Reposition uis after viewport resizes.
void uis_on_viewport_resized(int width, int height)
{
    //printf("uis_on_viewport_resized\n");
    float2 canvasSizef2 = { (float) width, (float) height };
    float aspectRatio = canvasSizef2.x / canvasSizef2.y;
    for (int i = 0; i < ui_entities_count; i++)
    {
        ecs_entity_t e = ui_entities[i];
        //printf("    e [%i] - [%lu]\n", i, (long int) e);
        const PixelPosition *pixelPosition = ecs_get(world, e, PixelPosition);
        const Anchor *anchor = ecs_get(world, e, Anchor);
        float2 position2D = {
            ((pixelPosition->value.x  / canvasSizef2.x) - 0.5f + anchor->value.x) * aspectRatio,
            ((pixelPosition->value.y  / canvasSizef2.y) - 0.5f + anchor->value.y) };
        const PixelSize *pixelSize = ecs_get(world, e, PixelSize);
        float2 scaledSize2D = (float2) { pixelSize->value.x / canvasSizef2.y, pixelSize->value.y / canvasSizef2.y };
        set_mesh_vertices_world_scale2D(world, e, squareTexturedVerts2, 16, scaledSize2D);  // scale the mesh
        ecs_set(world, e, Position2D, { position2D });
        ecs_set(world, e, EntityDirty, { 1 });
    }
}

//! The UI contains ways to interact with 2D objects.
/**
 * \todo Display a UI Element anchored, with a pixel position.
 * \todo Change colour when ray hits a button.
*/
void UICoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, UICore);
    ECS_TAG_DEFINE(world, Element);
    ECS_TAG_DEFINE(world, Selectable);
    ECS_TAG_DEFINE(world, Clickable);
    ECS_TAG_DEFINE(world, Button);
    ECS_TAG_DEFINE(world, Canvas);
    ECS_TAG_DEFINE(world, ElementRaycaster);
    ECS_COMPONENT_DEFINE(world, PixelPosition);
    ECS_COMPONENT_DEFINE(world, PixelSize);
    ECS_COMPONENT_DEFINE(world, Anchor);
    ECS_COMPONENT_DEFINE(world, CanvasLink);
    // Systems
    zoxel_system(world, ElementRaycastSystem, EcsOnUpdate, [none] ElementRaycaster);
    // prefabs
    int2 testSize = { 16, 16 };
    spawn_canvas_prefab(world);
    spawn_element_prefab(world, testSize);
}
#endif