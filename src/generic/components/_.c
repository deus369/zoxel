#include "component_byte.c"
#include "component_byte2.c"
#include "component_long_int.c"
#include "component_double.c"
#include "component_int.c"
#include "component_int2.c"
#include "component_int3.c"
#include "component_int4.c"
#include "component_float.c"
#include "component_float2.c"
#include "component_float3.c"
#include "component_float4.c"
#include "component_float6.c"
#include "component_entity.c"
#include "component_color.c"
#include "component_color_rgb.c"
#include "component_zext.c"

#define zox_component_string(type) zox_component_string##_##type(component##_##type)

void initialize_component_ids() {
    initialize_component_ids_byte();
    initialize_component_ids_byte2();
    initialize_component_ids_long_int();
    initialize_component_ids_double();
    initialize_component_ids_int();
    initialize_component_ids_int2();
    initialize_component_ids_int3();
    initialize_component_ids_int4();
    initialize_component_ids_float();
    initialize_component_ids_float2();
    initialize_component_ids_float3();
    initialize_component_ids_float4();
    initialize_component_ids_float6();
    initialize_component_ids_entity();
    initialize_component_ids_color();
    initialize_component_ids_color_rgb();
    initialize_component_ids_zext();
}

void dispose_component_ids() {
    dispose_component_ids_byte();
    dispose_component_ids_byte2();
    dispose_component_ids_long_int();
    dispose_component_ids_double();
    dispose_component_ids_int();
    dispose_component_ids_int2();
    dispose_component_ids_int3();
    dispose_component_ids_int4();
    dispose_component_ids_float();
    dispose_component_ids_float2();
    dispose_component_ids_float3();
    dispose_component_ids_float4();
    dispose_component_ids_float6();
    dispose_component_ids_entity();
    dispose_component_ids_color();
    dispose_component_ids_color_rgb();
    dispose_component_ids_zext();
}

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

void define_components_generic(ecs_world_t *world) {
    zox_define_tag(DestroyInFrame)
    zox_define_component_byte(EntityInitialize)
    zox_define_component_byte(EntityDirty)
    zox_define_component_byte(GenericEvent)
    zox_define_component_int2(ScreenDimensions)
    zox_define_component_int(ID)
    zox_define_component_long_int(Seed)
    zox_define_component_double(EventTime)
    zox_define_component_float3(Bounds3D)
    zox_define_component_float6(Position3DBounds)
    zox_define_component_entity(EntityTarget)
    zox_define_component_entity(ComponentTarget)
    zox_define_component_entity(EventInput)
    zox_define_component(TimedEvent)
    zox_define_component_zext(ZoxName)
    zox_define_entities_component(EntityLinks)
}