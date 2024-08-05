#ifndef zox_mod_maths
#define zox_mod_maths

#include <math.h>       // for sqrt
#include <float.h>
#include "data/constants.c"
#include "util/float_util.c"
typedef unsigned int uint;
// data types
#include "data/int2.c"
#include "data/int3.c"
#include "data/int4.c"
#include "data/byte2.c"
#include "data/byte3.c"
#include "data/byte4.c"
#include "data/float2.c"
#include "data/float3.c"
#include "data/float4.c"
#include "data/float6.c"
#include "data/float3x3.c"
#include "data/float4x4.c"
#include "data/double2.c"
#include "data/double3.c"
#include "data/ecs_entity_2.c"
#include "data/uint2.c"
#include "data/uint3.c"
#include "data/int_hashmap.c"
#include "data/int3_hashmap.c"
#include "data/byte3_hashmap.c"
#include "data/string_hashmap.c"
#include "util/math.c"
#include "util/integer_util.c"
#include "util/int3_util.c"
#include "util/noise.c"
#include "util/noise_2.c"
#include "util/unique_seed.c"
#include "util/conversion.c"
#include "fun/quaternion.c"
#include "fun/conversion.c"
#include "tests/test_quadrants.c"

zoxel_dynamic_array(int)
create_is_in_array_d(int)
zoxel_dynamic_array(float3)
zoxel_dynamic_array(float2)

zox_begin_module(Maths)
set_noise_seed(get_unique_time_seed());
zoxel_end_module(Maths)

#endif
