void attach_to_character(ecs_world_t *world, ecs_entity_t camera, ecs_entity_t character) {
    // zoxel_log(" > attaching to character\n");
    float vox_scale = model_scale * 16; //  * overall_voxel_scale * 16;
    const Position3D *position3D = ecs_get(world, character, Position3D);
    const Rotation3D *rotation3D = ecs_get(world, character, Rotation3D);
    ecs_set(world, camera, ParentLink, { character });
    // ecs_set(world, camera, Position3D, { position3D->value });
    ecs_set(world, camera, Rotation3D, { rotation3D->value });
    ecs_set(world, camera, LocalPosition3D, {{ 0, vox_scale * 2.2f, - vox_scale * 3.6f }});
    float3 euler = (float3) { 25, 180 * degreesToRadians, 0 };
    float4 rotation = quaternion_from_euler(euler); // quaternion_identity
    ecs_set(world, camera, LocalRotation3D, { rotation });
    ecs_add(world, camera, FirstPersonCamera);
    ecs_remove(world, camera, FreeRoam);
    ecs_remove(world, camera, EulerOverride);
    zox_set(character, DisableMovement, { 0 });
    ecs_add(world, character, PlayerCharacter3D);
    ecs_set(world, mouse_entity, MouseLock, { 1 });
    // ecs_set(world, camera, LocalPosition3D, { 0, 0, vox_scale / 2.0f }); // zoxel_set
    // ecs_set(world, camera, LocalPosition3D, { vox_scale / 2.0f, vox_scale + vox_scale / 2.0f, vox_scale });
    // ecs_set(world, camera, LocalEuler3D, { float3_zero });
    // zoxel_log("scale %f\n", vox_scale);
}

void detatch_from_character(ecs_world_t *world, ecs_entity_t camera, ecs_entity_t character) {
    zoxel_log(" > [%lu] is detaching from character [%lu]\n", camera, character);
    ecs_remove(world, character, PlayerCharacter3D);
    ecs_add(world, camera, EulerOverride);
    ecs_set(world, camera, FreeRoam, { 0 });
    ecs_set(world, camera, ParentLink, { 0 });
    ecs_remove(world, camera, FirstPersonCamera);
}