#ifndef zoxel_maths
#define zoxel_maths

#ifndef M_PI
#define M_PI 3.141592653589793
#endif
#ifndef degreesToRadians
#define degreesToRadians (M_PI * 2) / 360.0f
#endif

// libraries
#include <stdlib.h>
#include <stdio.h>
#include <math.h> // for sqrt
// move this to math module?
#include "data/byte2.c"
#include "data/float2.c"
#include "data/float3.c"
#include "data/float4.c"
#include "data/float4x4.c"
#include "data/double2.c"
#include "data/int2.c"
#include "data/int3.c"
// util
#include "util/math.c"
#include "util/integer_util.c"

void MathsImport(ecs_world_t *world)
{
    ECS_MODULE(world, Maths);
}
#endif