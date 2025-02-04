#define zox_axis_x 0
#define zox_axis_y 1
#define zox_axis_z 2

void float3_set_d(float3 *value, const unsigned char axis, const float d) {
    if (axis == zox_axis_x) value->x = d;
    else if (axis == zox_axis_y) value->y = d;
    else if (axis == zox_axis_z) value->z = d;
}

void int3_set_d(int3 *value, const unsigned char axis, const int d) {
    if (axis == zox_axis_x) value->x = d;
    else if (axis == zox_axis_y) value->y = d;
    else if (axis == zox_axis_z) value->z = d;
}
