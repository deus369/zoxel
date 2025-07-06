// rename screen to viewport
int2 screen_to_canvas_size(const int2 size, const float4 screen_to_canvas) {
    return (int2) { screen_to_canvas.x * size.x, screen_to_canvas.y * size. y };
}

// rename screen to viewport
int2 screen_to_canvas_position(const int2 size, const float4 screen_to_canvas) {
    return (int2) { screen_to_canvas.z * size.x, screen_to_canvas.w * size. y };
}

void resize_camera(ecs_world_t *world, const ecs_entity_t e, const int2 viewport_position, const int2 viewport_size) {
    if (e && zox_alive(e)) zox_set(e, ScreenPosition, { viewport_position })
    if (e && zox_alive(e)) zox_set(e, ScreenDimensions, { viewport_size })
}

void resize_cameras(ecs_world_t *world, const int2 screen_size) {
    for (int i = 0; i < main_cameras_count; i++) {
        if (!zox_valid(main_cameras[i])) {
            continue;
        }
        const float4 screen_to_canvas = zox_get_value(main_cameras[i], ScreenToCanvas)
        const int2 viewport_size = screen_to_canvas_size(screen_size, screen_to_canvas);
        const int2 viewport_position = screen_to_canvas_position(screen_size, screen_to_canvas);
        resize_camera(world, main_cameras[i], viewport_position, viewport_size);
        resize_camera(world, ui_cameras[i], viewport_position, viewport_size);
    }
}

void set_main_cameras(int new_count) {
    main_cameras_count = new_count;
}

CameraSpawnData get_camera_preset(const byte camera_mode, float vox_model_scale) {
    CameraSpawnData data = { };
    if (camera_mode == zox_camera_mode_topdown) {
        data = camera_preset_top_down;
    } else if (camera_mode == zox_camera_mode_ortho) {
        data = camera_preset_ortho;
    } else if (camera_mode == zox_camera_mode_first_person) {
        data = camera_preset_first_person;
        // convert position with scale
        data.position.x *= vox_model_scale;
        data.position.y *= vox_model_scale;
        data.position.z *= vox_model_scale;
    } else if (camera_mode == zox_camera_mode_third_person) {
        data = camera_preset_third_person;
    } else if (camera_mode == zox_camera_mode_2D) {
        data = camera_preset_2D;
    }
    return data;
}

void set_camera_transform(ecs_world_t *world, const ecs_entity_t camera, const ecs_entity_t character, const byte camera_mode, const float vox_model_scale) {
    if (!zox_valid(camera) || !zox_valid(character)) {
        zox_log_error("! cannot [set_camera_transform] camera/character issue.")
        return;
    }
    float3 target_position = float3_zero;
    const Position3D *position3D = zox_get(character, Position3D)
    if (position3D != NULL) {
        target_position = position3D->value;
    } else {
        target_position = (float3) { 8, 0, 8 };
    }
    const CameraSpawnData data = get_camera_preset(camera_mode, vox_model_scale);
    float3 euler = data.euler;
    float3_multiply_float_p(&euler, degreesToRadians);
    float4 camera_rotation = quaternion_from_euler(euler);
    zox_set(camera, LocalPosition3D, { data.position })
    zox_set(camera, Position3D, { float3_add(target_position, data.position) })
    if (camera_follow_mode == zox_camera_follow_mode_attach) {
        zox_set(camera, LocalRotation3D, { camera_rotation })
        zox_set(camera, Euler, { euler })
    } else zox_set(camera, Rotation3D, { camera_rotation })
}

byte get_camera_mode_fov(const byte camera_mode) {
    return get_camera_preset(camera_mode, 0).fov;
}

void set_camera_mode(ecs_world_t *world, byte new_camera_mode, const float vox_model_scale) {
    // remove 2 camera modes for now
    if (new_camera_mode == zox_camera_mode_free) {
        new_camera_mode = zox_camera_mode_first_person;
    }
    if (camera_mode == new_camera_mode) {
        return;
    }
    camera_mode = new_camera_mode;
    const byte old_camera_follow_mode = camera_follow_mode;
    const byte camera_fov = get_camera_mode_fov(camera_mode);
    camera_follow_mode = get_camera_preset(camera_mode, vox_model_scale).follow_mode;
    for (int i = 0; i < main_cameras_count; i++) {
        const ecs_entity_t camera = main_cameras[i];
        if (camera == 0 || !zox_valid(camera)) {
            continue;
        }
        zox_set(camera, CameraMode, { camera_mode })
        zox_set(camera, FieldOfView, { camera_fov })
        // camera_follow_mode is more complicated, involves how camera is attached to character
        ecs_entity_t character = 0;
        if (old_camera_follow_mode == zox_camera_follow_mode_attach) character = zox_get_value(camera, ParentLink)
        else character = zox_get_value(camera, CameraFollowLink)
        if (old_camera_follow_mode != camera_follow_mode) {
            // remove old link
            if (old_camera_follow_mode == zox_camera_follow_mode_attach) {
                zox_set(camera, ParentLink, { 0 })
            } else {
                zox_set(camera, CameraFollowLink, { 0 })
            }
            // reattach
            if (camera_follow_mode == zox_camera_follow_mode_attach) {
                zox_set(camera, ParentLink, { character })
            } else if (camera_follow_mode == zox_camera_follow_mode_follow_xz) {
                zox_set(camera, CameraFollowLink, { character })
            }
        }
        // set up local positions and rotations
        // use a helper function so attach does the same thing
        set_camera_transform(world, camera, character, camera_mode, vox_model_scale);
    }
}

void toggle_camera_mode(ecs_world_t *world, const float vox_model_scale) {
    byte new_camera_mode = camera_mode + 1;
    if (new_camera_mode> zox_camera_mode_topdown) {
        new_camera_mode = 0;
    }
    set_camera_mode(world, new_camera_mode, vox_model_scale);
}

void set_camera_mode_first_person(ecs_world_t *world, const float vox_model_scale) {
    set_camera_mode(world, zox_camera_mode_first_person, vox_model_scale);
}

void set_camera_mode_third_person(ecs_world_t *world) {
    set_camera_mode(world, zox_camera_mode_third_person, 0);
}

void set_camera_mode_ortho(ecs_world_t *world) {
    set_camera_mode(world, zox_camera_mode_ortho, 0);
}

void set_camera_mode_topdown(ecs_world_t *world) {
    set_camera_mode(world, zox_camera_mode_topdown, 0);
}

void set_camera_mode_2D(ecs_world_t *world) {
    set_camera_mode(world, zox_camera_mode_2D, 0);
}

void set_camera_mode_pre_defined(ecs_world_t *world, const float vox_model_scale) {
#if defined(zox_set_camera_2D)
    set_camera_mode_2D(world, 0);
#elif defined(zox_set_camera_firstperson)
    set_camera_mode_first_person(world, vox_model_scale);
#elif defined(zox_set_camera_thirdperson)
    set_camera_mode_third_person(world, 0);
#elif defined(zox_set_camera_ortho)
    set_camera_mode_ortho(world, 0);
#elif defined(zox_set_camera_topdown)
    set_camera_mode_topdown(world, 0);
#endif
}

extern byte terrain_depth;

// sets camera to main menu location
void set_camera_transform_to_main_menu(float3 *camera_position, float4 *camera_rotation) {
    const float overall_voxel_scale = powers_of_two[terrain_depth]; //  32.0f;
    camera_position->x = 0.25f * overall_voxel_scale;
    camera_position->y = 0.1f * overall_voxel_scale;
    camera_position->z = 0.25f * overall_voxel_scale;
    camera_rotation->x = 0;
    camera_rotation->y = 0;
    camera_rotation->z = 0;
    camera_rotation->w = 1;
    float rot_x = -0.2f;
    float rot_y = -M_PI_2 + M_PI * (rand() % 101) / 100.0f;
    float4 camera_rotation2 = quaternion_from_euler((float3) { rot_x, rot_y, 0 });
    camera_rotation->x = camera_rotation2.x;
    camera_rotation->y = camera_rotation2.y;
    camera_rotation->z = camera_rotation2.z;
    camera_rotation->w = camera_rotation2.w;
}