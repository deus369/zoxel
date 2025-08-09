byte zox_game_camera_mode = 0;
// Scaling
float viewport_scale = 1;

static inline int2 scale_viewport(int2 v) {
    return (int2) {
        ceil(v.x * viewport_scale),
        ceil(v.y * viewport_scale)
    };
}

// debugs
// #define zox_draw_frustum
// #define zox_draw_frustum_planes
// #define zox_debug_camera_frustum
// #define zox_test_camera_frustum
// #define zox_test_frustum2 // realtime
// #define zox_test_frustum
// #define zox_disable_frustum_planes
float3 debug_plane_rotation = { 0, 180, 0 };
float3 debug_plane_position = { -64, 16, -64 };
float debug_plane_distance = 128;
float4x4 debug_camera_transform = float4x4_zero;

#define zox_camera_stage EcsPreStore // EcsPreStore | EcsPostUpdate
#define max_cameras 16
// todo: I for raycasting, create a second frustum + second matrix
//      WAIT the precision issue also effects frustum
// todo 2: use double4x4 matrix for view matrix??....
// we know from testing smaller far distance it stops the precision errors
float camera_near_distance = 0.003f;
float camera_far_distance = 1024;
int main_cameras_count = 1;
const float camera_limit_x = 1.25f;
// byte camera_mode = 0; // zox_camera_mode_first_person;
byte camera_fov = 0; // camera_fov_first_person;
byte camera_follow_mode = 0; // zox_camera_follow_mode_attach;
entity main_cameras[max_cameras];
entity ui_cameras[max_cameras];
#ifdef zox_disable_streaming
    byte zox_cameras_disable_streaming = 1;
#else
    byte zox_cameras_disable_streaming = 0;
#endif