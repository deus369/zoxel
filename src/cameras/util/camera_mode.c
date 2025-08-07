void set_main_cameras(int new_count) {
    main_cameras_count = new_count;
}

CameraSpawnData get_camera_preset(
    const byte camera_mode,
    float vox_model_scale
) {
    CameraSpawnData data = { };
    if (camera_mode == zox_camera_mode_topdown) {
        data = camera_preset_top_down;
    } else if (camera_mode == zox_camera_mode_ortho) {
        data = camera_preset_ortho;
    } else if (camera_mode == zox_camera_mode_first_person) {
        data = camera_preset_first_person;
    } else if (camera_mode == zox_camera_mode_third_person) {
        data = camera_preset_third_person;
    } else if (camera_mode == zox_camera_mode_2D) {
        data = camera_preset_2D;
    }
    return data;
}

// our main camera transformer
void set_camera_transform(
    ecs *world,
    const entity camera,
    const entity character,
    const byte camera_mode,
    const float vox_model_scale
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
    const CameraSpawnData data = get_camera_preset(camera_mode, vox_model_scale);
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

byte get_camera_mode_fov(const byte camera_mode) {
    return get_camera_preset(camera_mode, 0).fov;
}

void set_camera_mode(
    ecs *world,
    byte new_camera_mode,
    const float vox_model_scale
) {
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
        const entity camera = main_cameras[i];
        if (camera == 0 || !zox_valid(camera)) {
            continue;
        }
        zox_set(camera, CameraMode, { camera_mode })
        zox_set(camera, FieldOfView, { camera_fov })
        // camera_follow_mode is more complicated, involves how camera is attached to character
        entity character = 0;
        if (old_camera_follow_mode == zox_camera_follow_mode_attach) {
            character = zox_get_value(camera, ParentLink)
        } else {
            character = zox_get_value(camera, CameraFollowLink)
        }
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

void toggle_camera_mode(ecs *world, const float vox_model_scale) {
    byte new_camera_mode = camera_mode + 1;
    if (new_camera_mode> zox_camera_mode_topdown) {
        new_camera_mode = 0;
    }
    set_camera_mode(world, new_camera_mode, vox_model_scale);
}

void set_camera_mode_first_person(ecs *world, const float vox_model_scale) {
    set_camera_mode(world, zox_camera_mode_first_person, vox_model_scale);
}

void set_camera_mode_third_person(ecs *world) {
    set_camera_mode(world, zox_camera_mode_third_person, 0);
}

void set_camera_mode_ortho(ecs *world) {
    set_camera_mode(world, zox_camera_mode_ortho, 0);
}

void set_camera_mode_topdown(ecs *world) {
    set_camera_mode(world, zox_camera_mode_topdown, 0);
}

void set_camera_mode_2D(ecs *world) {
    set_camera_mode(world, zox_camera_mode_2D, 0);
}

void set_camera_mode_pre_defined(ecs *world,
    const float vox_model_scale)
{
    if (zox_game_camera_mode == zox_camera_mode_2D) {
        set_camera_mode_2D(world);
    } else if (zox_game_camera_mode == zox_camera_mode_first_person) {
        set_camera_mode_first_person(world, vox_model_scale);
    } else if (zox_game_camera_mode == zox_camera_mode_third_person) {
        set_camera_mode_third_person(world);
    } else if (zox_game_camera_mode == zox_camera_mode_ortho) {
        set_camera_mode_ortho(world);
    } else if (zox_game_camera_mode == zox_camera_mode_topdown) {
        set_camera_mode_topdown(world);
    }
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