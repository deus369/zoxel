#define bounce_multiplier 1.0f
const float bounce_threshold = 0.001f;
#define bounce_lost_force 0.16f // 0.32 | 0.12
#define bounce_dampening 0.48f
// collision
const float collision_precision = 1.0f; // 0.99f; // 0.999f;    // 9
const float terrain_voxel_scale_inverse = 1 / 0.5f;
const float grounded_velocity_threshold = 0.22f;
// const float terrain_voxel_scale = 0.5f;
const float lowest_velocity_threshold = 0.03f; // 0.3 // 0.001
const byte3 zox_debug_collision_response = (byte3) { 0, 0, 0 };
// draw line to voxel side from character...
// debugs
// #define zox_gizmos_sphere_colliders
