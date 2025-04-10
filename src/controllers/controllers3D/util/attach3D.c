void set_camera_free(ecs_world_t *world, const ecs_entity_t camera, const byte is_free) {
    zox_remove(camera, FirstPersonCamera)
    const float4 camera_rotation3D = zox_get_value(camera, Rotation3D)
    const float3 euler = quaternion_to_euler(camera_rotation3D);
    zox_add_tag(camera, EulerOverride)
    zox_set(camera, Euler, { euler })
    if (camera_follow_mode == zox_camera_follow_mode_attach) zox_set(camera, ParentLink, { 0 })
    else if (camera_follow_mode == zox_camera_follow_mode_follow_xz) zox_set(camera, CameraFollowLink, { 0 })
    if (is_free) zox_set(camera, CanRoam, { 1 })
}

void set_camera_locked(ecs_world_t *world, const ecs_entity_t camera, const ecs_entity_t target) {
    zox_add_tag(camera, FirstPersonCamera)
    zox_set(camera, CanRoam, { 0 })
    if (camera_follow_mode == zox_camera_follow_mode_attach) zox_set(camera, ParentLink, { target })
    else if (camera_follow_mode == zox_camera_follow_mode_follow_xz) zox_set(camera, CameraFollowLink, { target })
    // zox_set(camera, EternalRotation, { quaternion_identity })
    zox_remove(camera, EulerOverride)
    set_camera_transform(world, camera, target, camera_mode);
}

void detatch_camera_from_character(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t camera, const ecs_entity_t character, const byte is_free) {
    // player
    // zox_set(player, CharacterLink, { 0 })
    // should get mouse from player devices
    if (mouse_entity) zox_set(mouse_entity, MouseLock, { 0 })
    // character
    if (character) {
        // zox_set(character, CameraLink, { 0 })
        zox_set(character, DisableMovement, { 1 })
    }
    // camera
    // zox_set(camera, CharacterLink, { 0 })
    set_camera_free(world, camera, is_free);
}

void attach_camera_to_character(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t camera, const ecs_entity_t character) {
    if (!character) {
        zox_log(" > character null in attach_camera_to_character\n")
        detatch_camera_from_character(world, player, camera, character, 1);
        return;
    }
    // player
    if (mouse_entity) zox_set(mouse_entity, MouseLock, { 1 }) // lock mouse since attached
    // character
    zox_set(character, DisableMovement, { 0 })
    // camera
    set_camera_locked(world, camera, character);
}

void toggle_free_roam_camera(ecs_world_t *world, const ecs_entity_t e) {
    const ecs_entity_t game = zox_get_value(e, GameLink)
    const byte game_state = zox_get_value(game, GameState)
    if (game_state == zox_game_playing) {
        const ecs_entity_t camera = zox_get_value(e, CameraLink)
        const ecs_entity_t character = zox_get_value(e, CharacterLink)
        // const ecs_entity_t character_camera = zox_get_value(character, CameraLink)
        const byte is_camera_free = zox_get_value(camera, CanRoam)
        if (is_camera_free) attach_camera_to_character(world, e, camera, character);
        else detatch_camera_from_character(world, e, camera, character, 1);
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
