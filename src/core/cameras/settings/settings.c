#define zox_camera_stage EcsPreStore // EcsPreStore | EcsPostUpdate
#define zox_camera_mode_free 0
#define zox_camera_mode_first_person 1
#define zox_camera_mode_third_person 2
#define zox_camera_mode_ortho 3
#define zox_camera_mode_topdown 4
// how to attach to character
#define zox_camera_follow_mode_attach 0
#define zox_camera_follow_mode_follow_xz 1
#define max_cameras 16
const float camera_near_distance = 0.1f; // 0.01f;
const float camera_far_distance = 800;
int main_cameras_count = 1;
const float camera_limit_x = 1.25f;
unsigned char camera_mode = zox_camera_mode_first_person;
unsigned char camera_fov = 90;
unsigned char camera_follow_mode = zox_camera_follow_mode_attach;
ecs_entity_t main_cameras[max_cameras];
ecs_entity_t ui_cameras[max_cameras];
unsigned char zox_cameras_disable_streaming = 0;
// debugs
// todo: debug frustum planes, draw plane with line for normal and distance, rotated quad with normal line?
// #define zox_draw_frustum
// #define zox_debug_camera_frustum
// #define zox_test_camera_frustum

// test the frustum using position
// #define zox_test_frustum2 // realtime
// now test rotation
float3 debug_plane_rotation = (float3) { 0, 180, 0 };

// #define zox_test_frustum

float3 debug_plane_position = (float3) { -64, 16, -64 };
float debug_plane_distance = 128;
float4x4 debug_camera_transform = float4x4_zero;


void toggle_cameras_updates() {
    zox_cameras_disable_streaming = !zox_cameras_disable_streaming;
    zox_log(" > cameras_streaming are [%s]\n", zox_cameras_disable_streaming ? "disabled" : "enabled")
}
