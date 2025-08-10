void set_main_cameras(int new_count) {
    main_cameras_count = new_count;
}

CameraSpawnData get_camera_preset(
    const byte mode
) {
    CameraSpawnData data = { 0 };
    if (mode == zox_camera_mode_topdown) {
        data = camera_preset_top_down;
    } else if (mode == zox_camera_mode_ortho) {
        data = camera_preset_ortho;
    } else if (mode == zox_camera_mode_first_person) {
        data = camera_preset_first_person;
    } else if (mode == zox_camera_mode_third_person) {
        data = camera_preset_third_person;
    } else if (mode == zox_camera_mode_2D) {
        data = camera_preset_2D;
    }
    return data;
}

// our main camera transformer
void set_camera_transform(
    ecs *world,
    const entity camera,
    const entity character,
    const byte mode
) {
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
    const CameraSpawnData data = get_camera_preset(mode);
    float3 euler = data.euler;
    float3_scale_p(&euler, degreesToRadians);
    float4 camera_rotation = quaternion_from_euler(euler);
    zox_set(camera, LocalPosition3D, { data.position })
    zox_set(camera, Position3D, { float3_add(target_position, data.position) })
    if (camera_follow_mode == zox_camera_follow_mode_attach) {
        zox_set(camera, LocalRotation3D, { camera_rotation })
        zox_set(camera, Euler, { euler })
    } else {
        zox_set(camera, Rotation3D, { camera_rotation })
    }
}

byte get_camera_mode_fov(const byte mode) {
    return get_camera_preset(mode).fov;
}

void set_camera_mode(
    ecs *world,
    const ecs_entity_t e,
    byte mode
) {
    // remove 2 camera modes for now
    if (mode == zox_camera_mode_free) {
        mode = zox_camera_mode_first_person;
    }
    /*if (camera_mode == mode) {
        return;
    }
    camera_mode = new_camera_mode;*/
    const byte old_camera_follow_mode = camera_follow_mode;
    const byte camera_fov = get_camera_mode_fov(mode);

    camera_follow_mode = get_camera_preset(mode).follow_mode;

    //for (int i = 0; i < main_cameras_count; i++) {
    //    const entity camera = main_cameras[i];
    //    if (camera == 0 || !zox_valid(camera)) {
    //        continue;
    //    }
    zox_set(e, CameraMode, { mode });
    zox_set(e, FieldOfView, { camera_fov });
    // camera_follow_mode is more complicated, involves how camera is attached to character
    entity target = 0;
    if (old_camera_follow_mode == zox_camera_follow_mode_attach) {
        target = zox_get_value(e, ParentLink)
    } else {
        target = zox_get_value(e, CameraFollowLink)
    }
    if (old_camera_follow_mode != camera_follow_mode) {
        // remove old link
        if (old_camera_follow_mode == zox_camera_follow_mode_attach) {
            zox_set(e, ParentLink, { 0 })
        } else {
            zox_set(e, CameraFollowLink, { 0 })
        }
        // reattach
        if (camera_follow_mode == zox_camera_follow_mode_attach) {
            zox_set(e, ParentLink, { target })
        } else if (camera_follow_mode == zox_camera_follow_mode_follow_xz) {
            zox_set(e, CameraFollowLink, { target })
        }
    }
    // set up local positions and rotations
    // use a helper function so attach does the same thing
    set_camera_transform(world, e, target, mode);
}

byte toggle_camera_mode(ecs *world, const ecs_entity_t camera) {
    zox_geter_value_non_const(camera, CameraMode, byte, mode);
    mode = mode + 1;
    if (mode > zox_camera_mode_topdown) {
        mode = 0;
    }
    set_camera_mode(world, camera, mode);
    return mode;
}

// sets camera to main menu location
void set_camera_transform_to_main_menu(
    float3 *camera_position,
    float4 *camera_rotation,
    const byte terrain_depth
) {
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