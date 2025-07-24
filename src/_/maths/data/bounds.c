typedef struct {
    float3 center, extents;
} bounds;

byte ray_intersects_aabb(
    const float3 ray_origin,
    const float3 ray_direction,
    const bounds box,
    float *tmin,
    float *tmax)
{
    float t1 = (box.center.x - box.extents.x - ray_origin.x) / ray_direction.x;
    float t2 = (box.center.x + box.extents.x - ray_origin.x) / ray_direction.x;
    float t3 = (box.center.y - box.extents.y - ray_origin.y) / ray_direction.y;
    float t4 = (box.center.y + box.extents.y - ray_origin.y) / ray_direction.y;
    float t5 = (box.center.z - box.extents.z - ray_origin.z) / ray_direction.z;
    float t6 = (box.center.z + box.extents.z - ray_origin.z) / ray_direction.z;

    float tmin_temp = fmax(fmax(fmin(t1, t2), fmin(t3, t4)), fmin(t5, t6));
    float tmax_temp = fmin(fmin(fmax(t1, t2), fmax(t3, t4)), fmax(t5, t6));

    if (tmax_temp < 0 || tmin_temp > tmax_temp)
        return 0;

    if (tmin_temp < 0)
        tmin_temp = 0;

    *tmin = tmin_temp;
    *tmax = tmax_temp;
    return 1;
}


float3 calculate_aabb_extents(float3 bounds, float4 q) {
    float xx = q.x * q.x;
    float yy = q.y * q.y;
    float zz = q.z * q.z;
    float xy = q.x * q.y;
    float xz = q.x * q.z;
    float yz = q.y * q.z;
    float wx = q.w * q.x;
    float wy = q.w * q.y;
    float wz = q.w * q.z;

    // Rotation matrix rows (row-major, from quaternion)
    float3 right = {
        1.0f - 2.0f * (yy + zz),
        2.0f * (xy + wz),
        2.0f * (xz - wy)
    };

    float3 up = {
        2.0f * (xy - wz),
        1.0f - 2.0f * (xx + zz),
        2.0f * (yz + wx)
    };

    float3 forward = {
        2.0f * (xz + wy),
        2.0f * (yz - wx),
        1.0f - 2.0f * (xx + yy)
    };

    float3 extents = {
        fabsf(right.x) * bounds.x + fabsf(up.x) * bounds.y + fabsf(forward.x) * bounds.z,
        fabsf(right.y) * bounds.x + fabsf(up.y) * bounds.y + fabsf(forward.y) * bounds.z,
        fabsf(right.z) * bounds.x + fabsf(up.z) * bounds.y + fabsf(forward.z) * bounds.z
    };

    return extents;
}

static inline byte point_in_aabb(const float3 point, const bounds b) {
    float3 d = float3_subtract(b.center, point);
    return
    fabsf(d.x) <= b.extents.x &&
    fabsf(d.y) <= b.extents.y &&
    fabsf(d.z) <= b.extents.z;
}