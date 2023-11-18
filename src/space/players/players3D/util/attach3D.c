/*#define main_camera_rotation_speed 60 * 0.22f

void toggle_camera_perspective(ecs_world_t *world, ecs_entity_t character) {
    if (camera_mode != zox_camera_mode_first_person) return;
    if (ecs_is_valid(world, character) && ecs_has(world, character, CameraLink)) {
        const CameraLink *cameraLink = ecs_get(world, character, CameraLink);
        if (ecs_is_valid(world, cameraLink->value) && cameraLink->value != 0) {
            float vox_scale = model_scale * 16;
            // zox_log("   > vox_scale [%f]\n", vox_scale)
            const LocalPosition3D *localPosition3D = ecs_get(world, cameraLink->value, LocalPosition3D);
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

void detatch_from_character(ecs_world_t *world, ecs_entity_t player, ecs_entity_t camera, ecs_entity_t character) {
    zox_set(player, CharacterLink, { 0 })
    if (camera_follow_mode == zox_camera_follow_mode_attach) zox_set(camera, ParentLink, { 0 })
    else if (camera_follow_mode == zox_camera_follow_mode_follow_xz) zox_set(camera, CameraFollowLink, { 0 })
    zox_remove(camera, FirstPersonCamera)
    //float4 rotationer = quaternion_from_euler( (float3) { 0, -main_camera_rotation_speed * degreesToRadians, 0 });
    //zox_set(camera, EternalRotation, { rotationer })
    zox_set(camera, CanFreeRoam, { 1 })
    zox_add_tag(camera, EulerOverride)
    // float4 rotation = quaternion_from_euler(ecs_get(world, camera, Euler)->value);
    // zox_set(camera, Rotation3D, { rotation })
    float4 camera_rotation3D = ecs_get(world, camera, Rotation3D)->value;
    float3 euler = quaternion_to_euler(camera_rotation3D);
    // zoxel_log(" > camera euler [%fx%fx%f]\n", euler.x, euler.y, euler.z);
    // float4 camera_rotation2 = quaternion_from_euler(euler);
    // float3 euler2 = quaternion_to_euler(camera_rotation2);
    // zoxel_log(" > camera euler2 [%fx%fx%f]\n", euler2.x, euler2.y, euler2.z);
    // zox_set(camera, Euler, {  quaternion_to_euler_x(camera_rotation3D), quaternion_to_euler_y(camera_rotation3D), 0 })
    zox_set(camera, Euler, { euler })
    zox_set(mouse_entity, MouseLock, { 0 })
    if (character != 0) {
        // zox_remove(character, PlayerCharacter3D)
        zox_set(character, CameraLink, { 0 })
    }
    // fix caera rotation to be the same
    // zoxel_log(" > [%lu] is detaching from character [%lu]\n", camera, character);
}

void attach_to_character(ecs_world_t *world, ecs_entity_t player, ecs_entity_t camera, ecs_entity_t character) {
    // const float vox_scale = model_scale * 16;
    if (!character) {
        detatch_from_character(world, player, camera, character);
        return;
    }
    set_camera_transform(world, camera, character, camera_mode); // attach the camera with transform restraints
    zox_add_tag(camera, FirstPersonCamera)
    zox_set(camera, CanFreeRoam, { 0 })
    if (camera_follow_mode == zox_camera_follow_mode_attach) zox_set(camera, ParentLink, { character })
    else if (camera_follow_mode == zox_camera_follow_mode_follow_xz) zox_set(camera, CameraFollowLink, { character })
    zox_set(camera, EternalRotation, { quaternion_identity })
    zox_remove(camera, EulerOverride)
    // character
    // zox_add_tag(character, PlayerCharacter3D)
    zox_set(character, CameraLink, { camera })
    zox_set(character, DisableMovement, { 0 })
    // link character
    zox_set(player, CharacterLink, { character })
    // lock mouse since attached
    zox_set(mouse_entity, MouseLock, { 1 })
    // spawn_element3D(world, character);  // todo: also add this to character's UILinks
    // zoxel_log(" > [%lu] is ataching to character [%lu]\n", camera, character);
}
