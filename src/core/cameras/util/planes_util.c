void normalize_plane(plane *p) {
    const float length = float3_magnitude(p->normal);
    if (length == 0) return;
    float3_divide_float_p(&p->normal, length);
    // p->distance /= length;
}

void normalize_planes(plane *planes) {
    for (unsigned char i = 0; i < 6; i++) {
        normalize_plane(&planes[i]);
    }
}

void transform_planes(const float4x4 mat, plane *planes) {
    const float4x4 inverse_mat = float4x4_inverse(mat);
    for (int i = 0; i < 6; i++) planes[i].normal = float4x4_multiply_float3(inverse_mat, planes[i].normal);
}

// this is wrong! - unitys CalculateFrustumPlanes - https://docs.unity3d.com/ScriptReference/GeometryUtility.CalculateFrustumPlanes.html
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
    // zox_log(" + distance near: %f to far: %f\n", planes[4].distance, planes[5].distance)
    normalize_planes(planes);
    transform_planes(mat, planes);
    normalize_planes(planes);
}

/*void calculate_frustum_planes2(const float4x4 view, const float4x4 proj, plane *planes) {
    // Left plane: column0 + column3
    planes[0].normal.x = proj.x.w + view.x.x;
    planes[0].normal.y = proj.y.w + view.x.y;
    planes[0].normal.z = proj.z.w + view.x.z;
    planes[0].distance = proj.w.w + view.x.w;

    // Right plane: column3 - column0
    planes[1].normal.x = proj.x.w - view.x.x;
    planes[1].normal.y = proj.y.w - view.x.y;
    planes[1].normal.z = proj.z.w - view.x.z;
    planes[1].distance = proj.w.w - view.x.w;

    // Bottom plane: column1 + column3
    planes[2].normal.x = proj.x.w + view.y.x;
    planes[2].normal.y = proj.y.w + view.y.y;
    planes[2].normal.z = proj.z.w + view.y.z;
    planes[2].distance = proj.w.w + view.y.w;

    // Top plane: column3 - column1
    planes[3].normal.x = proj.x.w - view.y.x;
    planes[3].normal.y = proj.y.w - view.y.y;
    planes[3].normal.z = proj.z.w - view.y.z;
    planes[3].distance = proj.w.w - view.y.w;

    // Near plane: column2 + column3
    planes[4].normal.x = proj.x.w + view.z.x;
    planes[4].normal.y = proj.y.w + view.z.y;
    planes[4].normal.z = proj.z.w + view.z.z;
    planes[4].distance = proj.w.w + view.z.w;

    // Far plane: column3 - column2
    planes[5].normal.x = proj.x.w - view.z.x;
    planes[5].normal.y = proj.y.w - view.z.y;
    planes[5].normal.z = proj.z.w - view.z.z;
    planes[5].distance = proj.w.w - view.z.w;
}*/

// checks if bounds point is outside of plane - test TestPlanesAABB
unsigned char is_in_frustum(const plane *planes, const bounds b) {
    for (unsigned char i = 0; i < 6; i++) {
        const float3 normal = planes[i].normal;
        const float3 bounds_point = float3_add(b.center, float3_multiply_float3(b.extents, float3_sign(normal)));
        const float distance_check = float3_dot(bounds_point, normal) + planes[i].distance;
        if (distance_check < 0) return 0;
    }
    return 1;
}

// #define EPSILON 0.0001f

/*unsigned char is_in_frustum(const plane *planes, const bounds b) {
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
}*/

/*const plane camera_plane = planes[i];
const float3 normal_sign = float3_sign(camera_plane.normal);
const float3 target_point = float3_add(b.center, float3_multiply_float3(b.extents, normal_sign));
const float dot = float3_dot(target_point, camera_plane.normal);
// Consider points lying exactly on the plane
if (fabs(dot + camera_plane.distance) < EPSILON) continue;
// Check if the point is outside the plane
if (dot + camera_plane.distance < -EPSILON) return 0;*/
