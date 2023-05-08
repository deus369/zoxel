const int max_mouse_delta = 120;
const float begin_rotate_power = 0.46; // 0.62
#define camera_quaternion_speed 0.004f // 0.01f

void FreeCameraRotateSystem(ecs_iter_t *it) {
    // double rotate_power = zox_delta_time;
    double rotate_power = begin_rotate_power * zox_delta_time * degreesToRadians * 32.0;
    #ifdef zoxel_on_web
        rotate_power *= 10.0;
    #endif
    ecs_query_t *cameraQuery = it->ctx;
    if (!cameraQuery) {
        zoxel_log("[FreeCameraMoveSystem; cameraQuery is null]\n");
        return;
    }
    ecs_iter_t cameraIter = ecs_query_iter(it->world, cameraQuery);
    ecs_query_next(&cameraIter);
    if (cameraIter.count == 0) {
        return;
    }
    Mouse *mouses = ecs_field(it, Mouse, 1);
    const FreeRoam *freeRoams = ecs_field(&cameraIter, FreeRoam, 2);
    #ifndef zoxel_quaternion_camera
        Euler *eulers = ecs_field(&cameraIter, Euler, 3);
    #else
        Rotation3D *rotation3Ds = ecs_field(&cameraIter, Rotation3D, 3);
    #endif
    unsigned char can_rotate_cameras = 0;
    for (int j = 0; j < cameraIter.count; j++) {
        const FreeRoam *freeRoam = &freeRoams[j];
        if (freeRoam->value == 1) {
            can_rotate_cameras = 1;
            break;
        }
    }
    if (!can_rotate_cameras) {
        return;
    }
    for (int i = 0; i < it->count; i++) {
        const Mouse *mouse = &mouses[i];
        if (int_abs(mouse->delta.x) + int_abs(mouse->delta.y) >= max_mouse_delta) {
            // zoxel_log("mouse delta out of bounds [%ix%i]\n", mouse->delta.x, mouse->delta.y);
            continue;
        }
        if (!(mouse->delta.x == 0 && mouse->delta.y == 0)) {
            for (int j = 0; j < cameraIter.count; j++) {
                const FreeRoam *freeRoam = &freeRoams[j];
                if (freeRoam->value == 1) {
                    #ifndef zoxel_quaternion_camera
                        float3 eulerAddition = { mouse->delta.y * rotate_power, -mouse->delta.x * rotate_power, 0 };
                        Euler *euler = &eulers[j];
                        euler->value = float3_add(euler->value, eulerAddition);
                    #else
                        Rotation3D *rotation3D = &rotation3Ds[j];
                        float dx = - mouse->delta.x * camera_quaternion_speed;
                        float dy = mouse->delta.y * camera_quaternion_speed;
                        float angle = sqrt(dx * dx + dy * dy);
                        float axis[3] = { dy / angle, dx / angle, 0 };
                        float4 rotate_delta = (float4) {
                            sin(angle / 2.0f) * axis[0],
                            sin(angle / 2.0f) * axis[1],
                            sin(angle / 2.0f) * axis[2],
                            cos(angle / 2.0f)
                        };
                        rotation3D->value = quaternion_rotate(rotation3D->value, rotate_delta);
                        /*float3x3 rotation_matrix = quaternion_to_float3x3(rotation3D->value);
                        rotation_matrix.y.x = 0;
                        rotation_matrix.y.z = 0;
                        rotation3D->value = float3x3_to_float4(rotation_matrix);*/
                    #endif
                    // zoxel_log("mouse->delta eulerAddition [%ix%i]\n", mouse->delta.x, mouse->delta.y);
                    // float3 euler2 = quaternion_to_euler(quaternion_from_euler(euler->value));
                    // zoxel_log(" + rotating [%fx%fx%f] - [%fx%fx%f]\n", euler->value.x, euler->value.y, euler->value.z, euler2.x, euler2.y, euler2.z);
                }
            }
        }
    }
}
zoxel_declare_system(FreeCameraRotateSystem)

    // eulerAddition.x == 0 && eulerAddition.y == 0 && eulerAddition.z == 0)) {
        // float3 eulerAddition = { mouse->delta.y, -mouse->delta.x, 0 };
                        // float3 euler = quaternion_to_euler(rotation3D->value);
                        // euler.x = 0;
                        // rotation3D->value = quaternion_from_euler(euler);