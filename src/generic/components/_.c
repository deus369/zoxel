#include "byte.c"
#include "byte2.c"
#include "byte3.c"
#include "long_int.c"
#include "double.c"
#include "int.c"
#include "int2.c"
#include "int3.c"
#include "int4.c"
#include "float.c"
#include "float2.c"
#include "float3.c"
#include "float4.c"
#include "float6.c"
#include "entity.c"
#include "color.c"
#include "color_rgb.c"
#include "zext.c"

#define zox_component_string(type) zox_component_string##_##type(component##_##type)

void initialize_component_ids() {
    initialize_component_ids_byte();
    initialize_component_ids_byte2();
    initialize_component_ids_byte3();
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
    dispose_component_ids_byte3();
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

// identitys
zoxc_int(ID);
zoxc_long_int(Seed);
zoxc_text(ZoxName)
// time events
zox_tag(DestroyInFrame);
zoxc_double(EventTime);
zoxc_entity(EventInput);
zoxc_function(TimedEvent, void, ecs_world_t*, const ecs_entity_t);
// used for physics
zoxc_float3(Bounds3D);
zoxc_float6(Position3DBounds);
// used for editor
zoxc_byte(EntityDirty);
zoxc_entity(EntityTarget);
zoxc_entity(ComponentTarget);
// unsorted
zoxc_byte(GenericEvent);
zoxc_byte(EntityInitialize);
zoxc_int2(ScreenDimensions);
zoxc_byte(SpawnChance);

void define_components_generic(ecs_world_t *world) {
    // ids
    zox_define_component_int(ID);
    zox_define_component_long_int(Seed);
    zox_define_component_zext(ZoxName);
    // timed
    zox_define_tag(DestroyInFrame);
    zox_define_component_double(EventTime);
    zox_define_component_entity(EventInput);
    zox_define_component(TimedEvent);
    // physics
    zox_define_component_float3(Bounds3D);
    zox_define_component_float6(Position3DBounds);
    // editor
    zox_define_component_byte(EntityDirty);
    zox_define_component_entity(EntityTarget);
    zox_define_component_entity(ComponentTarget);
    // unsorted
    zox_define_component_byte(GenericEvent);
    zox_define_component_byte(EntityInitialize);
    zox_define_component_int2(ScreenDimensions);
    zox_define_component_byte(SpawnChance);
}