static const CameraSpawnData camera_preset_top_down = {
    .position = { 0, 6, 0 },
    .euler = { -90, 180, 0 },
    .fov = 60,
    .follow_mode = zox_camera_follow_mode_follow_xz
};

static const CameraSpawnData camera_preset_ortho = {
    .position = { -4, 6, -4 },
    .euler = { -45, 225, 0 },
    .fov = 45,
    .follow_mode = zox_camera_follow_mode_follow_xz
};

static const CameraSpawnData camera_preset_2D = {
    .position = float3_zero,
    .euler = float3_zero,
    .fov = 90, // 45,
    .follow_mode = zox_camera_follow_mode_follow_xy
};