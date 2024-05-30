// todo: convert camera mouse point to a ray origin and normal
//      > we can use frustum actually, the near and far plane, since we have its corners
//      > camera_point_to_ray

Ray camera_point_to_ray(const float3* frustum_corners, const float2 point) {
    // Interpolate point on the near plane
    float3 near_top = float3_lerp(frustum_corners[0], frustum_corners[1], point.x);
    float3 near_bottom = float3_lerp(frustum_corners[3], frustum_corners[2], point.x);
    float3 near_point = float3_lerp(near_top, near_bottom, point.y);

    // Interpolate point on the far plane
    float3 far_top = float3_lerp(frustum_corners[4], frustum_corners[5], point.x);
    float3 far_bottom = float3_lerp(frustum_corners[7], frustum_corners[6], point.x);
    float3 far_point = float3_lerp(far_top, far_bottom, point.y);

    // Create ray
    Ray ray;
    ray.origin = near_point;
    ray.normal = float3_normalize(float3_sub(far_point, near_point));

    return ray;
}
