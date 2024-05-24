// #define zoxel_tests_rotate_by_keys

void test_rotation(ecs_world_t *world, const ecs_entity_t character, const keyboard *keyboard) {
    if (keyboard->r.is_pressed) {
        float3 euler = (float3) { 0, 90 * degreesToRadians, 0 * degreesToRadians };
        //float4 quaternion = (float4) { 0, debug_rotation_speed, 0, 1 };
        //quaternion_normalize(&quaternion);
        zox_set(character, Alpha3D, { quaternion_from_euler(euler) });
    } else if (keyboard->t.is_pressed) {
        float3 euler = (float3) { 0, -90 * degreesToRadians, 0 * degreesToRadians };
        //float4 quaternion = (float4) { 0, -debug_rotation_speed, 0, 1 };
        //quaternion_normalize(&quaternion);
        zox_set(character, Alpha3D, { quaternion_from_euler(euler) });
    } else if (keyboard->y.pressed_this_frame) {
        float3 euler = (float3) { 0 * degreesToRadians, (-90 + debug_rotation_addition) * degreesToRadians, 0 * degreesToRadians };
        zox_set(character, Rotation3D, { quaternion_from_euler(euler) });
    } else if (keyboard->u.pressed_this_frame) {
        float3 euler = (float3) { 0 * degreesToRadians, (0 + debug_rotation_addition) * degreesToRadians, 0 * degreesToRadians };
        zox_set(character, Rotation3D, { quaternion_from_euler(euler) });
    } else if (keyboard->i.pressed_this_frame) {
        float3 euler = (float3) { 0 * degreesToRadians, (90 + debug_rotation_addition) * degreesToRadians, 0 * degreesToRadians };
        zox_set(character, Rotation3D, { quaternion_from_euler(euler) });
    } else if (keyboard->o.pressed_this_frame) {
        float3 euler = (float3) { 0 * degreesToRadians, (180 + debug_rotation_addition) * degreesToRadians, 0 * degreesToRadians };
        zox_set(character, Rotation3D, { quaternion_from_euler(euler) });
    } else if (keyboard->f.pressed_this_frame) {
        zoxel_log(" > reset omega3D\n");
        zox_set(character, Omega3D, { quaternion_identity });
    } else if (keyboard->g.pressed_this_frame) {
        zoxel_log(" > reset alpha3D\n");
        zox_set(character, Alpha3D, { quaternion_identity });
    }
}
