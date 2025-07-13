// debugs
// #define zox_draw_frustum
// #define zox_draw_frustum_planes
// #define zox_debug_camera_frustum
// #define zox_test_camera_frustum
// #define zox_test_frustum2 // realtime
// #define zox_test_frustum
// #define zox_disable_frustum_planes
float3 debug_plane_rotation = (float3) { 0, 180, 0 };
float3 debug_plane_position = (float3) { -64, 16, -64 };
float debug_plane_distance = 128;
float4x4 debug_camera_transform = float4x4_zero;

#define zox_camera_stage EcsPreStore // EcsPreStore | EcsPostUpdate
#define zox_camera_mode_free 0
#define zox_camera_mode_first_person 1
#define zox_camera_mode_third_person 2
#define zox_camera_mode_ortho 3
#define zox_camera_mode_topdown 4
#define zox_camera_mode_2D 5
// how to attach to character
#define zox_camera_follow_mode_attach 0
#define zox_camera_follow_mode_follow_xz 1
#define zox_camera_follow_mode_follow_xy 2
#define max_cameras 16
// todo: I for raycasting, create a second frustum + second matrix
//      WAIT the precision issue also effects frustum
// todo 2: use double4x4 matrix for view matrix??....
// we know from testing smaller far distance it stops the precision errors
float camera_near_distance = 0.06f;
float camera_far_distance = 1024;
int main_cameras_count = 1;
const float camera_limit_x = 1.25f;
byte camera_mode = 0; // zox_camera_mode_first_person;
byte camera_fov = 0; // camera_fov_first_person;
byte camera_follow_mode = 0; // zox_camera_follow_mode_attach;
ecs_entity_t main_cameras[max_cameras];
ecs_entity_t ui_cameras[max_cameras];
#ifdef zox_disable_streaming
    byte zox_cameras_disable_streaming = 1;
#else
    byte zox_cameras_disable_streaming = 0;
#endif

const CameraSpawnData camera_preset_first_person = {
    .position = (float3) { 0, 32 * 0.22f, 0.085f * 2 },
    .euler = (float3) { 0, 180, 0 },
    .fov = 90,
    .follow_mode = zox_camera_follow_mode_attach
};

const CameraSpawnData camera_preset_third_person = {
    .position = (float3) { 0, 3.6f * 0.25f, -6.6f * 0.25f },
    .euler = (float3) { -25, 180, 0 },
    .fov = 75,
    .follow_mode = zox_camera_follow_mode_attach
};

const CameraSpawnData camera_preset_top_down = {
    .position = (float3) { 0, 6, 0 },
    .euler = (float3) { -90, 180, 0 },
    .fov = 60,
    .follow_mode = zox_camera_follow_mode_follow_xz
};

const CameraSpawnData camera_preset_ortho = {
    .position = (float3) { -4, 6, -4 },
    .euler = (float3) { -45, 225, 0 },
    .fov = 45,
    .follow_mode = zox_camera_follow_mode_follow_xz
};

const CameraSpawnData camera_preset_2D = {
    .position = float3_zero,
    .euler = float3_zero,
    .fov = 45,
    .follow_mode = zox_camera_follow_mode_follow_xy
};

void toggle_cameras_updates() {
    zox_cameras_disable_streaming = !zox_cameras_disable_streaming;
    zox_log(" > cameras_streaming are [%s]", zox_cameras_disable_streaming ? "disabled" : "enabled")
}