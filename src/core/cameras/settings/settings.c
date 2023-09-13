#define zox_camera_mode_first_person 0
#define zox_camera_mode_third_person 1
#define zox_camera_mode_ortho 2
#define zox_camera_mode_topdown 3
#define zox_camera_follow_mode_attach 0
#define zox_camera_follow_mode_follow_xz 1
#define max_cameras 16
const float camera_far_distance = 6000;
int main_cameras_count = 1;
const float camera_limit_x = 1.25f;
unsigned char camera_mode = 0;
unsigned char camera_fov = 60;
unsigned char camera_follow_mode = 0;