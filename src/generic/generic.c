#ifndef zox_mod_generic
#define zox_mod_generic

#include "components/components.c"
#include "data/color.c"
#include "data/color_rgb.c"
#include "data/octree_helper.c"
#include "data/text_group.c"
#include "data/ecs_entity_2.c"
#include "macros/octree_component.c"
zox_component_byte(GenericEvent)
zox_component_byte(EntityInitialize)
zox_component_int2(ScreenDimensions)
// identitys
zox_component_int(ID)
zox_component_long_int(Seed)
zox_component_zext(ZoxName)
// time events
zox_declare_tag(DestroyInFrame)
zox_component_double(EventTime)
zox_component_entity(EventInput)
zox_function_component(TimedEvent, void, ecs_world_t*, const ecs_entity_t)
// for gameplay _debug , 1
zox_entities_component(EntityLinks) // rename to ChunkEntities - used for characters atm
// used for physics
zox_component_float3(Bounds3D)
zox_component_float6(Position3DBounds)
// used for editor
zox_component_byte(EntityDirty)
zox_component_entity(EntityTarget)
zox_component_entity(ComponentTarget)
#include "macros/names.c"
#include "util/generic_util.c"
#include "util/convert_ascii.c"
#include "util/convert_to_ascii.c"
#include "util/name_util.c"
#include "util/name_generation.c"
#include "util/delay_util.c"
#include "prefabs/generic_event.c"
#include "systems/destroy_in_frame_system.c"
#include "systems/generic_event_debug_system.c"
#include "systems/timed_event_system.c"

void dispose_generic(ecs_world_t *world, void *ctx) {
    dispose_component_ids();
}

void spawn_prefabs_generic(ecs_world_t *world) {
    spawn_prefab_generic_event(world);
}

zox_begin_module(Generic)
    zox_module_dispose(dispose_generic)
    initialize_component_ids();
    zox_define_component_byte(EntityInitialize)
    zox_define_component_byte(EntityDirty)
    zox_define_component_int2(ScreenDimensions)
    zox_define_tag(DestroyInFrame)
    zox_define_component_long_int(Seed)
    zox_define_component_byte(GenericEvent)
    zox_define_component_int(ID)
    zox_define_component_float3(Bounds3D)
    zox_define_component_float6(Position3DBounds)
    zox_define_entities_component(EntityLinks)
    zox_define_component_zext(ZoxName)
    zox_define_component_entity(EntityTarget) // used for editor
    zox_define_component_entity(ComponentTarget)
    zox_define_component_double(EventTime)
    zox_define_component_entity(EventInput)
    zox_define_component(TimedEvent)
    // rest
    zox_system(DestroyInFrameSystem, EcsPreStore, [none] DestroyInFrame)
    zox_system_1(TimedEventSystem, zox_pip_mainthread, [in] TimedEvent, [in] EventInput, [out] EventTime)
    spawn_prefabs_generic(world);
zox_end_module(Generic)

#endif
