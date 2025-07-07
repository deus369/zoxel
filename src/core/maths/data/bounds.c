typedef struct {
    float3 center, extents;
} bounds;

byte ray_intersects_aabb(const float3 ray_origin, const float3 ray_direction, const bounds box, float *tmin, float *tmax) {
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