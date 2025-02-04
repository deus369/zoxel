const int max_mouse_delta = 120;
const float begin_rotate_power = 0.46; // 0.62
#define camera_quaternion_speed 0.004f // 0.01f

void FreeCameraRotateSystem(ecs_iter_t *it) {
    double rotate_power = begin_rotate_power * zox_delta_time * degreesToRadians * 32.0;
#ifdef zoxel_on_web
    rotate_power *= 10.0;
#endif
    zox_iter_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    zox_field_in(CameraLink, cameraLinks, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(CameraLink, cameraLinks, cameraLink)
        if (cameraLink->value == 0) continue;
        const unsigned char roam_state = zox_get_value(cameraLink->value, CanRoam)
        if (roam_state != 2) continue;
        zox_field_i(DeviceLinks, deviceLinkss, deviceLinks)
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (!device) continue;
            zox_geter(device, Children, zevices)
            for (int k = 0; k < zevices->length; k++) {
                const ecs_entity_t zevice = zevices->value[k];
                if (zox_has(device, Mouse)) {
                    if (!zox_has(zevice, ZevicePointerDelta)) continue;
                    const float2 delta = int2_to_float2(zox_gett_value(zevice, ZevicePointerDelta));
                    if (int_abs(delta.x) + int_abs(delta.y) >= max_mouse_delta || (delta.x == 0 &&delta.y == 0)) continue;
                    zox_get_muter(cameraLink->value, Euler, euler)
                    float3 eulerAddition = { delta.y * rotate_power, -delta.x * rotate_power, 0 };
                    euler->value = float3_add(euler->value, eulerAddition);
                }
            }
        }
    }
} zox_declare_system(FreeCameraRotateSystem)
