#ifndef zoxel_generic
#define zoxel_generic

#include "data/color.c"
zoxel_declare_tag(Selectable)
zoxel_declare_tag(Clickable)
zoxel_declare_tag(Dragable)
zoxel_declare_tag(DestroyInFrame)
zoxel_byte_component(EntityDirty)
zoxel_byte_component(EntityInitialize)
zoxel_byte_component(SelectableState)
zoxel_byte_component(ClickableState)
zoxel_byte_component(DragableState)
zoxel_component(DraggerLink, ecs_entity_t)
zoxel_component(DraggingDelta, int2)
zoxel_component(ID, int)                        //! An unique ID, possibly use GUID?
zoxel_component(Seed, long int)                 //! A unique Seed for generation.
zoxel_component(Raycaster, int2)                //! Contains the raycast mouse position.
zoxel_component(RaycasterTarget, ecs_entity_t)  //! A target entity for the Raycaster.
zoxel_component(Layer2D, unsigned char)         //! A 2D Layer for a entity.
zoxel_component(Color, color)                   //! A generic entity color.
zoxel_component(SecondaryColor, color)                   //! A generic entity color.
zoxel_memory_component(Colors, color)           //! A generic entity colors.
zoxel_byte_component(GenericEvent)             //! Used for game and other events, genetic
zoxel_reset_system(EntityDirtyResetSystem, EntityDirty)
zoxel_reset_system(ClickableStateResetSystem, ClickableState)
zoxel_reset_system(EntityInitializeResetSystem, EntityInitialize)
#include "util/generic_util.c"
#include "util/convert_ascii.c"
#include "util/convert_to_ascii.c"
#include "prefabs/generic_event.c"
#include "systems/destroy_in_frame_system.c"

void GenericImport(ecs_world_t *world) {
    zoxel_module(Generic)
    zoxel_define_tag(Selectable)
    zoxel_define_tag(Clickable)
    zoxel_define_tag(Dragable)
    zoxel_define_tag(DestroyInFrame)
    zoxel_define_component(EntityDirty)
    zoxel_define_component(SelectableState)
    zoxel_define_component(ClickableState)
    zoxel_define_component(DragableState)
    zoxel_define_component(DraggerLink)
    zoxel_define_component(DraggingDelta)
    zoxel_define_component(ID)
    zoxel_define_component(Seed)
    zoxel_define_component(Raycaster)
    zoxel_define_component(RaycasterTarget)
    zoxel_define_component(EntityInitialize)
    zoxel_define_component(Layer2D)
    zoxel_define_component(Color)
    zoxel_define_component(SecondaryColor)
    zoxel_memory_component_define(Colors)
    zoxel_define_component(GenericEvent)
    zoxel_reset_system_define(EntityDirtyResetSystem, EntityDirty)
    zoxel_reset_system_define(ClickableStateResetSystem, ClickableState)
    zoxel_reset_system_define(EntityInitializeResetSystem, EntityInitialize)
    zoxel_system(world, DestroyInFrameSystem, EcsPreStore, [none] DestroyInFrame)
    spawn_prefab_generic_event(world);
}
#endif