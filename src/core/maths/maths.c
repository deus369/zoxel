#ifndef zoxel_maths
#define zoxel_maths

#ifndef M_PI
#define M_PI 3.141592653589793
#endif
#ifndef M_PI_2
#define M_PI_2 1.570796327
#endif
#ifndef degreesToRadians
#define degreesToRadians (M_PI * 2) / 360.0f
#endif
#include <math.h>       // for sqrt
#include "data/byte2.c"
#include "data/byte3.c"
#include "data/byte4.c"
#include "data/int2.c"
#include "data/int3.c"
#include "data/int4.c"
#include "data/float2.c"
#include "data/float3.c"
#include "data/float4.c"
#include "data/float6.c"
#include "data/float3x3.c"
#include "data/float4x4.c"
#include "data/double2.c"
#include "data/ecs_entity_2.c"
#include "collections/dynamic_array.c"
#include "collections/hash_map.c"
#include "util/math.c"
#include "util/integer_util.c"
#include "util/noise.c"
#include "util/noise_2.c"
#include "util/unique_seed.c"
#include "fun/quaternion.c"
#include "fun/conversion.c"
#include "tests/test_quadrants.c"

zoxel_begin_module(Maths)
unsigned long seed = get_unique_time_seed();
#ifdef zoxel_seed_666
    seed = 666;
#endif
set_noise_seed(seed);
// zoxel_log(" > seed set to [%lu]\n", seed);
// set_noise_seed(12666);
// test_quadrants();
zoxel_end_module(Maths)

#endif