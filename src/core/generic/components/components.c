#include "component_byte.c"
#include "component_int.c"
#include "component_long_int.c"
#include "component_float.c"
#include "component_double.c"
#include "component_byte2.c"
#include "component_int2.c"
#include "component_float2.c"
#include "component_int4.c"
#include "component_float3.c"

#define zox_component_string(type) zox_component_string##_##type(component##_##type)

void initialize_component_ids() {
    initialize_component_ids_byte();
    initialize_component_ids_int();
    initialize_component_ids_long_int();
    initialize_component_ids_float();
    initialize_component_ids_double();
    initialize_component_ids_byte2();
    initialize_component_ids_int2();
    initialize_component_ids_float2();
    initialize_component_ids_int4();
    initialize_component_ids_float3();
}

void dispose_component_ids() {
    dispose_component_ids_byte();
    dispose_component_ids_int();
    dispose_component_ids_long_int();
    dispose_component_ids_float();
    dispose_component_ids_double();
    dispose_component_ids_byte2();
    dispose_component_ids_int2();
    dispose_component_ids_float2();
    dispose_component_ids_int4();
    dispose_component_ids_float3();
}
