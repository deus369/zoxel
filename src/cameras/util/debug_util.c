int get_label_camera_euler(ecs_world_t *world, const ecs_entity_t player, char buffer[], int buffer_size, int buffer_index) {
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    if (!camera) return buffer_index;
    const float4 rotation3D = zox_get_value(camera, Rotation3D)
    const float3 euler = quaternion_to_euler_360(rotation3D);
    buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "camera_rot [%ix%ix%i]\n", (int) euler.x, (int) euler.y, (int) euler.z);
    return buffer_index;
}

int get_label_camera_position(ecs_world_t *world, const ecs_entity_t player, char buffer[], int buffer_size, int buffer_index) {
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    if (!camera) return buffer_index;
    const float3 position3D = zox_get_value(camera, Position3D)
    buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "camera_pos [%ix%ix%i]\n", (int) position3D.x, (int) position3D.y, (int) position3D.z);
    return buffer_index;
}

int get_label_camera_planes(ecs_world_t *world, const ecs_entity_t player, char buffer[], int buffer_size, int buffer_index) {
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    if (!camera || !zox_has(camera, CameraPlanes)) return buffer_index;
    const CameraPlanes *planes = zox_get(camera, CameraPlanes)
    if (planes->length != 6) buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "camera_planes invalid!\n");
    else {
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "frustum planes [6]\n");
        for (int i = 0; i < 6; i++) buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "%i [%.1fx%.1fx%.1f] [%.1f]\n", (i + 1), planes->value[i].normal.x, planes->value[i].normal.y,  planes->value[i].normal.z, planes->value[i].distance);
    }
    // const float6 bounds = zox_get_value(camera, Position3DBounds)
    // buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "camera bounds x[%.0f:%.0f] y[%.0f:%.0f] z[%.0f:%.0f]\n", bounds.x, bounds.y, bounds.z, bounds.w, bounds.u, bounds.v);
    return buffer_index;
}


int get_label_camera_frustum(ecs_world_t *world, const ecs_entity_t player, char buffer[], int buffer_size, int buffer_index) {
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    if (!camera || !zox_has(camera, FrustumCorners)){
         buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "invalid camera\n");
        return buffer_index;
    }
    const FrustumCorners *corners = zox_get(camera, FrustumCorners)
    if (corners->length != 8) {
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "frustum corners invalid!\n");
    } else {
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "frustum corners [8]\n");
        for (int i = 0; i < 8; i++) {
            buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "%i [%.1fx%.1fx%.1f]\n", (i + 1), corners->value[i].x, corners->value[i].y,  corners->value[i].z);
        }
    }
    return buffer_index;
}
