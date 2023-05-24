void attach_to_character(ecs_world_t *world, ecs_entity_t camera, ecs_entity_t character) {
    // zoxel_log(" > attaching to character\n");
    float vox_scale = model_scale * 16; //  * overall_voxel_scale * 16;
    const Rotation3D *rotation3D = ecs_get(world, character, Rotation3D);
    float3 euler = (float3) { 25, 180 * degreesToRadians, 0 };
    float4 rotation = quaternion_from_euler(euler); // quaternion_identity
    zox_add_tag(camera, FirstPersonCamera)
    zox_add_tag(character, PlayerCharacter3D)
    zox_set_only(camera, ParentLink, { character })
    zox_set_only(camera, Rotation3D, { rotation3D->value })
    zox_set_only(camera, LocalPosition3D, {{ 0, vox_scale * 2.2f, - vox_scale * 3.6f }})
    zox_set_only(camera, LocalRotation3D, { rotation })
    zox_set_only(character, DisableMovement, { 0 })
    zox_set_only(mouse_entity, MouseLock, { 1 })
    zox_remove(camera, FreeRoam)
    zox_remove(camera, EulerOverride)
}

void detatch_from_character(ecs_world_t *world, ecs_entity_t camera, ecs_entity_t character) {
    // zoxel_log(" > [%lu] is detaching from character [%lu]\n", camera, character);
    zox_add_tag(camera, EulerOverride)
    zox_set_only(camera, FreeRoam, { 0 })
    zox_set_only(camera, ParentLink, { 0 })
    zox_remove(character, PlayerCharacter3D)
    zox_remove(camera, FirstPersonCamera)
    // fix caera rotation to be the same
}

// ecs_set(world, camera, LocalPosition3D, { 0, 0, vox_scale / 2.0f }); // zoxel_set
// ecs_set(world, camera, LocalPosition3D, { vox_scale / 2.0f, vox_scale + vox_scale / 2.0f, vox_scale });
// ecs_set(world, camera, LocalEuler3D, { float3_zero });
// zoxel_log("scale %f\n", vox_scale);
// const Position3D *position3D = ecs_get(world, character, Position3D);
// ecs_set(world, camera, Position3D, { position3D->value });