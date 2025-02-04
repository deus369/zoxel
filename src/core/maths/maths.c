/* *
 *  Zox Maths
 *
 *      - This just adds our data types together in mathematical ways
 *      - pure util functions
 *      - todo: put data and fun into util sub folder
 * */
#ifndef zox_mod_maths
#define zox_mod_maths

#include <math.h>       // for sqrt
#include <float.h>
#include "data/constants.c"
#include "util/float_util.c"
// data types
#include "data/data.c"
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
zoxel_dynamic_array(float4x4)

#endif
