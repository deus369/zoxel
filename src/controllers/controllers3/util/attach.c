void set_camera_locked(ecs_world_t *world,
    const ecs_entity_t camera,
    const ecs_entity_t target)
{
    zox_add_tag(camera, FirstPersonCamera)
    zox_set(camera, CanRoam, { 0 })
    if (camera_follow_mode == zox_camera_follow_mode_attach) {
        zox_set(camera, ParentLink, { target })
    } else if (camera_follow_mode == zox_camera_follow_mode_follow_xz) {
        zox_set(camera, CameraFollowLink, { target })
    }
    // zox_set(camera, EternalRotation, { quaternion_identity })
    zox_remove(camera, EulerOverride)
    set_camera_transform(world, camera, target, camera_mode, vox_model_scale);
}

void attach_camera_to_character(ecs_world_t *world,
    const ecs_entity_t camera,
    const ecs_entity_t character)
{
    if (!zox_valid(character)) {
        zox_log_error("character invalid in attach_camera_to_character")
        return;
    }
    // character
    zox_set(character, DisableMovement, { 0 })
    // linking
    zox_set(camera, CharacterLink, { character })
    // camera
    set_camera_locked(world, camera, character);
    // player
    if (local_mouse) {
        zox_set(local_mouse, MouseLock, { 1 }) // lock mouse since attached
    }
}

void toggle_free_roam_camera(ecs_world_t *world, const ecs_entity_t e) {
    zox_geter_value(e, GameLink, ecs_entity_t, game)
    zox_geter_value(game, GameState, byte, game_state)
    if (game_state == zox_game_playing) {
        const ecs_entity_t camera = zox_get_value(e, CameraLink)
        const ecs_entity_t character = zox_get_value(e, CharacterLink)
        zox_geter_value(camera, CanRoam, byte, is_camera_free)
        if (is_camera_free) {
            zox_set(e, PlayerState, { zox_player_state_playing })
            attach_camera_to_character(world, camera, character);
        } else {
            zox_set(e, PlayerState, { zox_player_state_free_roam })
            detatch_camera_from_character(world, camera, character, 1);
        }
    }
}

/*#define main_camera_rotation_speed 60 * 0.22f

void toggle_camera_perspective(ecs_world_t *world, ecs_entity_t character) {
    if (camera_mode != zox_camera_mode_first_person) return;
    if (zox_valid(character) && zox_has(character, CameraLink)) {
        const CameraLink *cameraLink = zox_get(world, character, CameraLink);
        if (zox_valid(cameraLink->value) && cameraLink->value != 0) {
            float vox_scale = vox_model_scale * 16;
            // zox_log("   > vox_scale [%f]\n", vox_scale)
            const LocalPosition3D *localPosition3D = zox_get(world, cameraLink->value, LocalPosition3D);
            if (localPosition3D->value.z == vox_scale * 0.5f) {
                zox_set(cameraLink->value, LocalPosition3D, {{ 0, vox_scale * 2.2f, - vox_scale * 3.6f }})
                zox_set(cameraLink->value, LocalRotation3D, { quaternion_from_euler((float3) { -25 * degreesToRadians, 180 * degreesToRadians, 0 }) })
            } else {
                zox_set(cameraLink->value, LocalPosition3D, {{ 0, vox_scale * 0.5f, vox_scale * 0.5f }})
                zox_set(cameraLink->value, LocalRotation3D, { quaternion_from_euler((float3) { 0, 180 * degreesToRadians, 0 }) })
            }
        }
    }
}*/
