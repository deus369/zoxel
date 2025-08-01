void set_camera_free(ecs_world_t *world,
    const ecs_entity_t camera,
    const byte is_free)
{
    zox_geter_value(camera, Rotation3D, float4, camera_rotation3D)
    const float3 euler = quaternion_to_euler(camera_rotation3D);
    zox_remove(camera, FirstPersonCamera)
    zox_add_tag(camera, EulerOverride)
    zox_set(camera, Euler, { euler })
    if (is_free) {
        zox_set(camera, CanRoam, { 1 })
    }
    if (camera_follow_mode == zox_camera_follow_mode_attach) {
        zox_set(camera, ParentLink, { 0 })
    } else if (camera_follow_mode == zox_camera_follow_mode_follow_xz) {
        zox_set(camera, CameraFollowLink, { 0 })
    }
}

void detatch_camera_from_character(ecs_world_t *world,
    const ecs_entity_t camera,
    const ecs_entity_t character,
    const byte is_free)
{
    // should get mouse from player devices
    if (local_mouse) {
        zox_set(local_mouse, MouseLock, { 0 })
    }
    // character
    if (character) {
        // zox_set(character, CameraLink, { 0 })
        zox_set(character, DisableMovement, { 1 })
    }
    // camera
    set_camera_free(world, camera, is_free);
    // linking
    zox_set(camera, CharacterLink, { 0 })
}