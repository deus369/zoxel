#ifndef zoxel_generic
#define zoxel_generic

#include "data/color.c"
#include "data/color_rgb.c"
zox_declare_tag(Selectable)
zox_declare_tag(Clickable)
zox_declare_tag(Dragable)
zox_declare_tag(DestroyInFrame)
zox_byte_component(EntityDirty)
zox_byte_component(EntityInitialize)
zox_byte_component(SelectableState)
zox_byte_component(ClickableState)
zox_byte_component(DragableState)
zox_component(DraggerLink, ecs_entity_t)
zox_component(DraggingDelta, int2)
zox_component(ID, int)                        //! An unique ID, possibly use GUID?
zox_component(Seed, long int)                 //! A unique Seed for generation
zox_component(Raycaster, int2)                //! Contains the raycast mouse position
zox_component(RaycasterTarget, ecs_entity_t)  //! A target entity for the Raycaster
zox_component(Layer2D, unsigned char)         //! A 2D Layer for a entity
zox_component(ColorRGB, color_rgb)
zox_component(Color, color)                   //! A generic entity color
zox_component(SecondaryColor, color)          //! A generic entity color
zox_memory_component(ColorRGBs, color_rgb)           //! A generic entity colorRGBs
zox_memory_component(Colors, color)           //! A generic entity colorRGBs
zox_byte_component(GenericEvent)              //! Used for game and other events, genetic
zox_component(Bounds3D, float3)
zox_entities_component(EntityLinks)
zox_reset_system(EntityDirtyResetSystem, EntityDirty)
zox_reset_system(ClickableStateResetSystem, ClickableState)
zox_reset_system(EntityInitializeResetSystem, EntityInitialize)
#include "util/generic_util.c"
#include "util/convert_ascii.c"
#include "util/convert_to_ascii.c"
#include "prefabs/generic_event.c"
#include "systems/destroy_in_frame_system.c"

zox_begin_module(Generic)
zox_define_tag(Selectable)
zox_define_tag(Clickable)
zox_define_tag(Dragable)
zox_define_tag(DestroyInFrame)
zox_define_component(EntityDirty)
zox_define_component(SelectableState)
zox_define_component(ClickableState)
zox_define_component(DragableState)
zox_define_component(DraggerLink)
zox_define_component(DraggingDelta)
zox_define_component(ID)
zox_define_component(Seed)
zox_define_component(Raycaster)
zox_define_component(RaycasterTarget)
zox_define_component(EntityInitialize)
zox_define_component(Layer2D)
zox_define_component(ColorRGB)
zox_define_component(Color)
zox_define_component(SecondaryColor)
zox_define_memory_component(ColorRGBs)
zox_define_memory_component(Colors)
zox_define_component(GenericEvent)
zox_define_component(Bounds3D)
zox_define_entities_component(EntityLinks, [in] EntityLinks)
zox_define_reset_system(EntityDirtyResetSystem, EntityDirty)
zox_define_reset_system(ClickableStateResetSystem, ClickableState)
zox_define_reset_system(EntityInitializeResetSystem, EntityInitialize)
zox_system(DestroyInFrameSystem, EcsPreStore, [none] DestroyInFrame)
spawn_prefab_generic_event(world);
zoxel_end_module(Generic)

#endif