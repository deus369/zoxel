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
        zox_field_i_in(CameraLink, cameraLinks, cameraLink)
        if (cameraLink->value == 0) continue;
        const CanRoam *canRoam = zox_get(cameraLink->value, CanRoam)
        if (canRoam->value != 2) continue;
        zox_field_i_in(DeviceLinks, deviceLinkss, deviceLinks)
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device_entity = deviceLinks->value[j];
            if (zox_has(device_entity, Mouse)) {
                const Mouse *mouse = zox_get(device_entity, Mouse)
                if (int_abs(mouse->delta.x) + int_abs(mouse->delta.y) >= max_mouse_delta || (mouse->delta.x == 0 && mouse->delta.y == 0)) continue;
                Euler *euler = zox_get_mut(cameraLink->value, Euler)
                float3 eulerAddition = { mouse->delta.y * rotate_power, -mouse->delta.x * rotate_power, 0 };
                euler->value = float3_add(euler->value, eulerAddition);
                zox_modified(cameraLink->value, Euler)
            }
        }
    }
} zox_declare_system(FreeCameraRotateSystem)
