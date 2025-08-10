/* *
 *  Zox Maths
 *
 *      - This just adds our data types together in mathematical ways
 *      - pure util functions
 *      - todo: put data and fun into util sub folder
 * */
#ifndef zoxm_maths
#define zoxm_maths

// NOTE: we use Column Major Matrix (as opposed to Row Major);

#include "data/constants.c"
#include "data/_.c"
#include "util/_.c"
#include "tests/test_quadrants.c"
#include "bounds/_.c"
#include "planes/_.c"

zoxel_dynamic_array(int)
create_is_in_array_d(int)
zoxel_dynamic_array(float3)
zoxel_dynamic_array(float2)
zoxel_dynamic_array(float4x4)

#endif