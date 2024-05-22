#define bounce_multiplier 1.0f
// #define bounce_lost_force 0.32f // 0.0f
#define bounce_lost_force 0.12f // 0.12f
const float bounce_threshold = 0.001f;

// collision
const float collision_precision = 1.0f; // 0.99f; // 0.999f;    // 9
const float terrain_voxel_scale_inverse = 1 / 0.5f;
const float grounded_velocity_threshold = 0.22f;
// const float terrain_voxel_scale = 0.5f;
const float lowest_velocity_threshold = 0.03f; // 0.3 // 0.001
const byte3 zox_debug_collision_response = (byte3) { 0, 0, 0 };
// draw line to voxel side from character...
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
