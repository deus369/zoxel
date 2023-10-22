#ifndef zoxel_generic
#define zoxel_generic

// zoxel_component_includes
#include "data/color.c"
#include "data/color_rgb.c"
#include "data/octree_helper.c"
#include "data/octree_component.c"
#include "data/text_group.c"
zox_declare_tag(Selectable)
zox_declare_tag(Clickable)
zox_declare_tag(Dragable)
zox_declare_tag(DestroyInFrame)
zox_byte_component(EntityDirty)
zox_byte_component(EntityInitialize)
zox_byte_component(SelectState)
zox_byte_component(ClickState)
zox_byte_component(DragableState)
zox_component(DraggingDelta, int2)
zox_component(DraggerLink, ecs_entity_t)
zox_component(DraggedLink, ecs_entity_t)
zox_component(DraggableLimits, int2)
zox_component(ID, int)                        //! An unique ID, possibly use GUID?
zox_component(Seed, long int)                 //! A unique Seed for generation
zox_component(Raycaster, int2)                //! Contains the raycast mouse position
zox_component(RaycasterTarget, ecs_entity_t)  //! A target entity for the Raycaster
zox_byte_component(RaycasterResult)
zox_component(Layer2D, unsigned char)         //! A 2D Layer for a entity
zox_component(Color, color)
zox_component(SecondaryColor, color)
zox_component(ColorRGB, color_rgb)
zox_component(SecondaryColorRGB, color_rgb)
zox_memory_component(ColorRGBs, color_rgb)
zox_memory_component(Colors, color)
zox_byte_component(GenericEvent)
zox_component(Bounds3D, float3)
zox_entities_component(EntityLinks)
zox_byte_component(Dead)
zox_time_component(DiedTime)
// zoxel_util_includes
#include "util/generic_util.c"
#include "util/convert_ascii.c"
#include "util/convert_to_ascii.c"
// zoxel_prefab_includes
#include "prefabs/generic_event.c"
// zoxel_system_includes
#include "systems/destroy_in_frame_system.c"
#include "systems/generic_event_debug_system.c"
#include "systems/death_clean_system.c"

void spawn_prefabs_generic(ecs_world_t *world) {
    spawn_prefab_generic_event(world);
}

zox_begin_module(Generic)
// zoxel_component_defines
zox_define_tag(Selectable)
zox_define_tag(Clickable)
zox_define_tag(Dragable)
zox_define_tag(DestroyInFrame)
zox_define_component(EntityDirty)
zox_define_component(SelectState)
zox_define_component(ClickState)
zox_define_component(DragableState)
zox_define_component(DraggingDelta)
zox_define_component(DraggerLink)       // the what that drags
zox_define_component(DraggedLink)       // the who gets dragged
zox_define_component(DraggableLimits)
zox_define_component(ID)
zox_define_component(Seed)
zox_define_component(Raycaster)
zox_define_component(RaycasterTarget)
zox_define_component(RaycasterResult)
zox_define_component(EntityInitialize)
zox_define_component(Layer2D)
zox_define_component(Color)
zox_define_component(SecondaryColor)
zox_define_component(ColorRGB)
zox_define_component(SecondaryColorRGB)
zox_define_memory_component(ColorRGBs)
zox_define_memory_component(Colors)
zox_define_component(GenericEvent)
zox_define_component(Bounds3D)
zox_define_entities_component(EntityLinks)
zox_define_component(Dead)
zox_define_component(DiedTime)
// zoxel_system_defines
zox_system(DestroyInFrameSystem, EcsPreStore, [none] DestroyInFrame)
zoxel_end_module(Generic)

#endif
