#ifndef zoxel_maths
#define zoxel_maths

#ifndef M_PI
#define M_PI 3.141592653589793
#endif
#ifndef degreesToRadians
#define degreesToRadians (M_PI * 2) / 360.0f
#endif

#include <math.h> // for sqrt
// move this to math module?
#include "data/byte2.c"
#include "data/byte4.c"
#include "data/int2.c"
#include "data/int3.c"
#include "data/int4.c"
#include "data/float2.c"
#include "data/float3.c"
#include "data/float4.c"
#include "data/float4x4.c"
#include "data/double2.c"
#include "data/ecs_entity_2.c"
// util
#include "util/math.c"
#include "util/integer_util.c"
#include "util/noise.c"
#include "util/noise_2.c"
#include "util/unique_seed.c"

void MathsImport(ecs_world_t *world) {
    zoxel_module(Maths)
    unsigned long seed = get_unique_time_seed();
    set_noise_seed(seed);
    zoxel_log(" > seed [%lu]\n", seed);
    // set_noise_seed(12666);
}
#endif