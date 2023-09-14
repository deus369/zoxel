void resize_camera(ecs_world_t *world, ecs_entity_t e, int2 new_screen_dimensions) {
    if (e && ecs_is_alive(world, e)) zox_set_only(e, ScreenDimensions, { new_screen_dimensions })
}

//! Uses ecs_get_mut to resize cameras. \todo Create a viewport resize event.
void resize_cameras(int2 screen_size) {
    for (int i = 0; i < main_cameras_count; i++) resize_camera(world, main_cameras[i], screen_size);
    resize_camera(world, ui_cameras[0], screen_size);
}

void set_main_cameras(int new_count) {
    main_cameras_count = new_count;
}

unsigned char get_mouse_constrained() {
    #ifdef zoxel_mouse_emulate_touch
        return 0;
    #endif
    return ecs_get(world, mouse_entity, MouseLock)->value;
}

void set_camera_transform(ecs_world_t *world, ecs_entity_t camera, ecs_entity_t character, unsigned char camera_mode) {
    if (!camera || !character) return;
    const Position3D *position3D = ecs_get(world, character, Position3D);
    float3 camera_position;
    float3 camera_euler;
    if (camera_mode == zox_camera_mode_topdown) {
        camera_euler = (float3) { -90, 180, 0 };
        camera_position = (float3) { 0, 22, 0 };
    } else if (camera_mode == zox_camera_mode_ortho) {
        camera_euler = (float3) { -45, 225, 0 };
        camera_position = (float3) { -20, 30, -20 };
    } else if (camera_mode == zox_camera_mode_first_person) {
        camera_euler = (float3) { -25, 180, 0 };
        camera_position = (float3) { 0, 2.2f, -3.6f };
    }
    //zoxel_log(" > settings camera transform [%i] - pos [%fx%fx%f] - rot [%fx%fx%f]\n", camera_mode,
    //    camera_position.x,  camera_position.y,  camera_position.z, camera_euler.x, camera_euler.y, camera_euler.z);
    float3_multiply_float_p(&camera_position, 0.25f);
    float3_multiply_float_p(&camera_euler, degreesToRadians);
    float4 camera_rotation = quaternion_from_euler(camera_euler);
    zox_set_only(camera, LocalPosition3D, { camera_position })
    zox_set_only(camera, Position3D, { float3_add(position3D->value, camera_position) })
    if (camera_follow_mode == zox_camera_follow_mode_attach) zox_set_only(camera, LocalRotation3D, { camera_rotation })
    else zox_set_only(camera, Rotation3D, { camera_rotation })
}

void set_camera_mode(ecs_world_t *world, unsigned char new_camera_mode) {
    // remove 2 camera modes for now
    if (new_camera_mode == zox_camera_mode_free) new_camera_mode = zox_camera_mode_first_person;
    if (new_camera_mode == zox_camera_mode_third_person) new_camera_mode = zox_camera_mode_ortho;
    if (camera_mode == new_camera_mode) return;
    camera_mode = new_camera_mode;
    unsigned char old_camera_fov = camera_fov;
    unsigned char old_camera_follow_mode = camera_follow_mode;
    if (camera_mode == zox_camera_mode_first_person) {
        camera_follow_mode = zox_camera_follow_mode_attach;
        camera_fov = 90;
    } else if (camera_mode == zox_camera_mode_ortho) {
        camera_follow_mode = zox_camera_follow_mode_follow_xz;
        camera_fov = 45;
    } else if (camera_mode == zox_camera_mode_topdown) {
        camera_follow_mode = zox_camera_follow_mode_follow_xz;
        camera_fov = 60;
    }
    for (int i = 0; i < max_cameras; i++) {
        ecs_entity_t camera = main_cameras[i];
        if (camera == 0 || !ecs_is_valid(world, camera)) continue;
        zox_set_only(camera, CameraMode, { camera_mode })
        if (old_camera_fov != camera_fov) zox_set_only(camera, FieldOfView, { camera_fov })
        // camera_follow_mode is more complicated, involves how camera is attached to character
        ecs_entity_t character = 0;
        if (old_camera_follow_mode == zox_camera_follow_mode_attach) character = ecs_get(world, camera, ParentLink)->value;
        else character = ecs_get(world, camera, CameraFollowLink)->value;
        if (old_camera_follow_mode != camera_follow_mode) {
            // remove old link
            if (old_camera_follow_mode == zox_camera_follow_mode_attach) zox_set_only(camera, ParentLink, { 0 })
            else zox_set_only(camera, CameraFollowLink, { 0 })
            // reattach
            if (camera_follow_mode == zox_camera_follow_mode_attach) zox_set_only(camera, ParentLink, { character })
            else if (camera_follow_mode == zox_camera_follow_mode_follow_xz) zox_set_only(camera, CameraFollowLink, { character })
        }
        // set up local positions and rotations
        // use a helper function so attach does the same thing
        set_camera_transform(world, camera, character, camera_mode);
    }
    if (camera_mode == zox_camera_mode_first_person) {
        zoxel_log("    > camera_mode set [first person]\n");
    } else if (camera_mode == zox_camera_mode_ortho) {
        zoxel_log("    > camera_mode set [ortho]\n");
    } else if (camera_mode == zox_camera_mode_topdown) {
        zoxel_log("    > camera_mode set [top down]\n");
    } else {
        zoxel_log("    > camera_mode set [%i]\n", camera_mode);
    }
}

void set_camera_mode_first_person(ecs_world_t *world) {
    set_camera_mode(world, zox_camera_mode_first_person);
}

void set_camera_mode_ortho(ecs_world_t *world) {
    set_camera_mode(world, zox_camera_mode_ortho);
}

void set_camera_mode_topdown(ecs_world_t *world) {
    set_camera_mode(world, zox_camera_mode_topdown);
}