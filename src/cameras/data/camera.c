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