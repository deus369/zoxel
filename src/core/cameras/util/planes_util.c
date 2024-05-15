void normalize_planes(plane *planes) {
    for (unsigned char i = 0; i < 6; i++) {
        float length = float3_magnitude(planes[i].normal);
        if (length == 0) continue;
        float3_divide_float_p(&planes[i].normal, length);
        planes[i].distance /= length;
    }
}

void calculate_frustum_planes(const float4x4 mat, plane *planes) {
    // left plane > w + x
    planes[0].normal.x = mat.w.x + mat.x.x;
    planes[0].normal.y = mat.w.y + mat.x.y;
    planes[0].normal.z = mat.w.z + mat.x.z;
    planes[0].distance = mat.w.w + mat.x.w;
    // right plane > w - x
    planes[1].normal.x = mat.w.x - mat.x.x;
    planes[1].normal.y = mat.w.y - mat.x.y;
    planes[1].normal.z = mat.w.z - mat.x.z;
    planes[1].distance = mat.w.w - mat.x.w;
    // bottom plane > w + y
    planes[2].normal.x = mat.w.x + mat.y.x;
    planes[2].normal.y = mat.w.y + mat.y.y;
    planes[2].normal.z = mat.w.z + mat.y.z;
    planes[2].distance = mat.w.w + mat.y.w;
    // top plane > w - y
    planes[3].normal.x = mat.w.x - mat.y.x;
    planes[3].normal.y = mat.w.y - mat.y.y;
    planes[3].normal.z = mat.w.z - mat.y.z;
    planes[3].distance = mat.w.w - mat.y.w;
    // near plane > w + z
    planes[4].normal.x = mat.w.x + mat.z.x;
    planes[4].normal.y = mat.w.y + mat.z.y;
    planes[4].normal.z = mat.w.z + mat.z.z;
    planes[4].distance = mat.w.w + mat.z.w;
    // far plane > w - z
    planes[5].normal.x = mat.w.x - mat.z.x;
    planes[5].normal.y = mat.w.y - mat.z.y;
    planes[5].normal.z = mat.w.z - mat.z.z;
    planes[5].distance = mat.w.w - mat.z.w;
    normalize_planes(planes);
}

// checks if bounds point is outside of plane
/*unsigned char is_in_frustum(const plane *planes, const bounds target_bounds) {
    for (unsigned char i = 0; i < 6; i++) {
        const plane camera_plane = planes[i];
        const float3 normal_sign = float3_sign(camera_plane.normal);
        const float3 target_point = float3_add(target_bounds.center, float3_multiply_float3(target_bounds.extents, normal_sign));
        const float dot = float3_dot(target_point, camera_plane.normal);
        if (dot + camera_plane.distance < 0) return 0;
    }
    return 1;
}*/
// #define EPSILON 0.0001f

unsigned char is_in_frustum(const plane *planes, const bounds b) {
    for (unsigned char i = 0; i < 6; i++) {
        float3 offset;
        for (offset.x = -b.extents.x; offset.x <= b.extents.x; offset.x += b.extents.x * 2) {
            for (offset.y = -b.extents.y; offset.y <= b.extents.y; offset.y += b.extents.y * 2) {
                for (offset.z = -b.extents.z; offset.z <= b.extents.z; offset.z += b.extents.z * 2) {
                    const float3 point = float3_add(b.center, offset);
                    const unsigned char is_on_plane = compare_point_on_plane(point, planes[i]);
                    if (!is_on_plane) return 0;
                }
            }
        }
    }
    return 1;
}

/*const plane camera_plane = planes[i];
const float3 normal_sign = float3_sign(camera_plane.normal);
const float3 target_point = float3_add(b.center, float3_multiply_float3(b.extents, normal_sign));
const float dot = float3_dot(target_point, camera_plane.normal);
// Consider points lying exactly on the plane
if (fabs(dot + camera_plane.distance) < EPSILON) continue;
// Check if the point is outside the plane
if (dot + camera_plane.distance < -EPSILON) return 0;*/
