const double movement_multiplier = 0.08 * 100;
const double shift_movement_multiplier = 3.0;

void FreeCameraMoveSystem(ecs_iter_t *it) {
    ecs_iter_t cameras_it = ecs_query_iter(it->world, it->ctx);
    ecs_query_next(&cameras_it);
    if (cameras_it.count == 0) {
        return;
    }
    unsigned char did_update = 0;
    double movement_power = zoxel_delta_time;
    movement_power *= movement_multiplier;
    #ifdef WEB_BUILD
        movement_power *= 10.0f;
    #endif
    const FreeRoam *freeRoams = ecs_field(&cameras_it, FreeRoam, 2);
    Position3D *positions = ecs_field(&cameras_it, Position3D, 3);
    Rotation3D *rotations = ecs_field(&cameras_it, Rotation3D, 4);
    const Keyboard *keyboards = ecs_field(it, Keyboard, 1);
    for (int i = 0; i < it->count; i++) {
        const Keyboard *keyboard = &keyboards[i];
        float3 movement = { 0, 0, 0 };
        if (keyboard->a.is_pressed) {
            movement.x = -1;
        }
        if (keyboard->d.is_pressed) {
            movement.x = 1;
        }
        if (keyboard->w.is_pressed) {
            movement.z = -1;
        }
        if (keyboard->s.is_pressed) {
            movement.z = 1;
        }
        if (keyboard->q.is_pressed) {
            movement.y = -1;
        }
        if (keyboard->e.is_pressed) {
            movement.y = 1;
        }
        if (!(movement.x == 0 && movement.y == 0 && movement.z == 0)) {
            did_update = 1;
            // printf("Bob Accel %f x %f \n", movement.x, movement.y);
            movement = float3_multiply_float(movement, movement_power);
            if (keyboard->left_shift.is_pressed) {
                movement.x *= shift_movement_multiplier;
                movement.y *= shift_movement_multiplier;
                movement.z *= shift_movement_multiplier;
            }
            for (int j = 0; j < cameras_it.count; j++) {
                const FreeRoam *freeRoam = &freeRoams[j];
                if (freeRoam->value == 1) {
                    const Rotation3D *rotation = &rotations[j];
                    float3 rotatedMovement = float4_rotate_float3(rotation->value, movement);
                    Position3D *position = &positions[j];
                    position->value = float3_add(position->value, rotatedMovement);
                }
            }
        }
        if (keyboard->r.pressed_this_frame) {
            did_update = 1;
            for (int j = 0; j < cameras_it.count; j++) {
                Rotation3D *rotation = &rotations[j];
                rotation->value = quaternion_from_euler( (float3) { 0 * degreesToRadians, 0 * degreesToRadians, 0 * degreesToRadians });
            }
        }
    }
    if (!did_update) {
        // ecs_query_skip(&cameras_it);
    }
}
zoxel_declare_system(FreeCameraMoveSystem)

//printf("Before Movement: %fx%fx%f - [%fx%fx%fx%f]\n", movement.x, movement.y, movement.z,
//    rotation->value.x, rotation->value.y, rotation->value.z, rotation->value.w);
// float4_print_euler(rotation->value);
// float3 rotatedMovement2 = float3_multiply_float(rotatedMovement, 10000);
// printf("Moving [%i x %i x %i]\n", (int) rotatedMovement2.x, (int) rotatedMovement2.y, (int) rotatedMovement2.z);
// printf("    Rotation3D [%f x %f x %f x %f]\n", rotation->value.x, rotation->value.y, rotation->value.z, rotation->value.w);