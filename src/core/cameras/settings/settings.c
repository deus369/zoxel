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
const float camera_far_distance = 6000;
int main_cameras_count = 1;
const float camera_limit_x = 1.25f;
unsigned char camera_mode = zox_camera_mode_first_person;
unsigned char camera_fov = 90;
unsigned char camera_follow_mode = zox_camera_follow_mode_attach;
ecs_entity_t main_cameras[max_cameras];
ecs_entity_t ui_cameras[max_cameras];
// debugs
// #define zox_debug_camera_frustum
// todo: debug frustum planes, draw plane with line for normal and distance, rotated quad with normal line?
