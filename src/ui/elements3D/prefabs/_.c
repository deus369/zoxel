void set_element_properties(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t parent, const ecs_entity_t canvas, const int2 pixel_position, const int2 pixel_size, const float2 anchor, const byte layer, const float2 position2D, const int2 pixel_position_global) {
    zox_set(e, Anchor, { anchor })
    zox_set(e, Layer2D, { layer })
    zox_set(e, PixelSize, { pixel_size })
    zox_set(e, PixelPosition, { pixel_position })
    zox_set(e, Position2D, { position2D }) // set this inside pixel position system
    zox_set(e, CanvasPosition, { pixel_position_global }) // set this inside system too
    zox_set(e, CanvasLink, { canvas })
    zox_set(e, ParentLink, { parent })
    if (canvas == parent) {
        on_child_added(world, canvas, e);
        zox_set(canvas, WindowToTop, { e })
    }
}

#include "element_world.c"
#include "element_world_child.c"
#include "element3D_invisible.c"
#include "zigel3D.c"
#include "text3D.c"
#include "label3D.c"
#include "popup3D.c"
#include "elementbar3D_front.c"
#include "elementbar3D.c"
ecs_entity_t prefab_element3D;
ecs_entity_t prefab_element3D_child;
ecs_entity_t prefab_element3D_invisible;
ecs_entity_t prefab_elementbar3D;
ecs_entity_t prefab_elementbar3D_front;
ecs_entity_t prefab_text3D;
ecs_entity_t prefab_zigel3D;
ecs_entity_t prefab_label3D;
ecs_entity_t prefab_popup3D;

void spawn_prefabs_elements3D(ecs_world_t *world) {
    prefab_element3D = spawn_prefab_element3D(world);
    prefab_element3D_child = spawn_prefab_element3D_child(world);
    prefab_element3D_invisible = spawn_prefab_element3D_invisible(world);
    prefab_elementbar3D = spawn_prefab_elementbar3D(world, prefab_element3D);
    prefab_elementbar3D_front = spawn_prefab_elementbar3D_front(world, prefab_element3D_child);
    prefab_text3D = spawn_prefab_text3D(world, prefab_element3D_invisible);
    prefab_zigel3D = spawn_prefab_zigel3D(world, prefab_element3D_child);
    prefab_label3D = spawn_prefab_label3D(world, prefab_element3D);
    prefab_popup3D = spawn_prefab_popup3(world, prefab_element3D);
}