#ifndef zoxel_generic
#define zoxel_generic

// zoxel_component_includes
#include "data/color.c"
#include "data/color_rgb.c"
#include "data/octree_helper.c"
#include "data/text_group.c"
#include "data/ecs_entity_2.c"
#include "macros/octree_component.c"
#include "components/components.c"
zox_declare_tag(Selectable)
zox_declare_tag(Clickable)
zox_declare_tag(Dragable)
zox_declare_tag(DestroyInFrame)
zox_component_byte(EntityDirty)
zox_component_byte(EntityInitialize)
zox_component_byte(SelectState)
zox_component_byte(ClickState)
zox_component_byte(DraggableState)
zox_component_byte(GenericEvent)
zox_component_byte(RaycasterResult)
zox_component_byte(Layer2D)         //! A 2D Layer for a entity
zox_component_byte(Dead)
zox_component_int(ID)                        //! An unique ID, possibly use GUID
zox_component_int2(DraggingDelta)
zox_component_int4(DraggableLimits)
zox_component_int2(Raycaster)                //! Contains the raycast mouse position
zox_component(DraggerLink, ecs_entity_t)
zox_component(DraggedLink, ecs_entity_t)
zox_component_long_int(Seed)                 //! A unique Seed for generation
zox_component(RaycasterTarget, ecs_entity_t)  //! A target entity for the Raycaster
zox_component(Color, color)
zox_component(SecondaryColor, color)
zox_component(ColorRGB, color_rgb)
zox_component(SecondaryColorRGB, color_rgb)
zox_component(Bounds3D, float3)
zox_time_component(DiedTime)
zox_component(EntityTarget, ecs_entity_t)
zox_component(ComponentTarget, ecs_entity_t)
zox_component(ClickingEntity, ecs_entity_t)
zox_memory_component(ZoxName, unsigned char)
zox_memory_component(ColorRGBs, color_rgb)
zox_memory_component(Colors, color)
zox_entities_component(EntityLinks)
// zoxel_util_includes
#include "util/generic_util.c"
#include "util/convert_ascii.c"
#include "util/convert_to_ascii.c"
#include "util/name_util.c"
// zoxel_prefab_includes
#include "prefabs/generic_event.c"
// zoxel_system_includes
#include "systems/destroy_in_frame_system.c"
#include "systems/generic_event_debug_system.c"
#include "systems/death_clean_system.c"

void dispose_generic(ecs_world_t *world) {
    dispose_component_ids();
}

void spawn_prefabs_generic(ecs_world_t *world) {
    spawn_prefab_generic_event(world);
}

zox_begin_module(Generic)
initialize_component_ids();
// zoxel_component_defines
zox_define_tag(Selectable)
zox_define_tag(Clickable)
zox_define_tag(Dragable)
zox_define_tag(DestroyInFrame)
zox_define_component_long_int(Seed)
zox_define_component_byte(EntityDirty)
zox_define_component_byte(SelectState)
zox_define_component_byte(ClickState)
zox_define_component_byte(DraggableState)
zox_define_component_byte(EntityInitialize)
zox_define_component_byte(Layer2D)
zox_define_component_byte(RaycasterResult)
zox_define_component_byte(Dead)
zox_define_component_byte(GenericEvent)
zox_define_component_int2(DraggingDelta)
zox_define_component_int4(DraggableLimits)
zox_define_component_int2(Raycaster)
zox_define_component_int(ID)
zox_define_component(DraggerLink)       // the what that drags
zox_define_component(DraggedLink)       // the who gets dragged
zox_define_component(RaycasterTarget)
zox_define_component(Color)
zox_define_component(SecondaryColor)
zox_define_component(ColorRGB)
zox_define_component(SecondaryColorRGB)
zox_define_memory_component(ColorRGBs)
zox_define_memory_component(Colors)
zox_define_component(Bounds3D)
zox_define_entities_component(EntityLinks)
zox_define_component(DiedTime)
zox_define_memory_component(ZoxName)
zox_define_component(EntityTarget)
zox_define_component(ComponentTarget)
zox_define_component(ClickingEntity)
// zoxel_system_defines
zox_system(DestroyInFrameSystem, EcsPreStore, [none] DestroyInFrame)
zoxel_end_module(Generic)

#endif
