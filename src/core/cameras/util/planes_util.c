// Remember: So i finally gett  it, we have 6 planes, normal + distance are their formula
// A normal is direction plane faces, distance is from origin, you can draw this actually
// we have 6, they overlap, but they should all be forming a shape, facing out? idk
// Our check checks if the bounding box intersects with every plane, well checks the side it's on
// if it's not on every side, it's in middle, i.e. inside the cage / frustum shape

// we need to draw these planes. we can get their overlapping 8 points?

void normalize_plane(plane *p) {
    // this b breaks around origin?
    /*if (p->distance < 0) {
        p->normal.x *= -1;
        p->normal.y *= -1;
        p->normal.z *= -1;
        p->distance *= -1;
    }*/
    const float length = float3_magnitude(p->normal);
    if (length == 0) return;
    float3_divide_float_p(&p->normal, length);
    p->distance /= length;
}

void normalize_planes(plane *planes) {
    for (unsigned char i = 0; i < 6; i++) {
        normalize_plane(&planes[i]);
    }
}

float3 generate_plane_normal(const float3 point_a, const float3 point_b, const float3 point_c) {
    const float3 vector_ab = float3_sub(point_a, point_b);
    const float3 vector_ac = float3_sub(point_a, point_c);
    return float3_normalize(float3_cross(vector_ab, vector_ac));
}

plane calculate_plane_from_points(const float3 point_a, const float3 point_b, const float3 point_c) {
    plane result_plane;
    result_plane.normal = generate_plane_normal(point_a, point_b, point_c);
    result_plane.distance = float3_dot(result_plane.normal, point_a);
    // normalize_plane(&result_plane);
    return result_plane;
}

void calculate_planes_from_frustum(float3 *frustum, plane *planes) {
    planes[0] = calculate_plane_from_points(frustum[0], frustum[3], frustum[4]); // 7 L
    planes[1] = calculate_plane_from_points(frustum[1], frustum[2], frustum[5]); // 6 R
    planes[2] = calculate_plane_from_points(frustum[0], frustum[5], frustum[1]); // 4 B
    planes[3] = calculate_plane_from_points(frustum[3], frustum[7], frustum[6]); // 2 T
    planes[4] = calculate_plane_from_points(frustum[3], frustum[2], frustum[1]); // 2 N
    planes[5] = calculate_plane_from_points(frustum[7], frustum[6], frustum[5]); // 4 F
}

void calculate_frustum_planes(const float4x4 view_projection_matrix, plane *planes, float6 *bounds) {
    float3 *frustum = calculate_frustum_corners(view_projection_matrix);
    calculate_frustum_bounds(frustum, bounds);
    calculate_planes_from_frustum(frustum, planes);
    free(frustum);
    normalize_planes(planes);
}

void fix_frustum_normals(const float4x4 transform_matrix, plane *planes) {
    planes[4].normal = float4x4_forward(transform_matrix);
    planes[5].normal = float3_multiply_float(planes[4].normal, -1);
    planes[4].distance = camera_near_distance;
    planes[5].distance = camera_far_distance;
}

plane* create_test_planes_position(float3 position, float distance) {
    plane* planes = malloc(6 * sizeof(plane));
    planes[0] = (plane) { { 1, 0, 0 }, position.x + distance };
    planes[1] = (plane) { { -1, 0, 0 }, -position.x + distance };
    planes[2] = (plane) { { 0, 1, 0 }, position.y + distance };
    planes[3] = (plane) { { 0, -1, 0 }, -position.y + distance };
    planes[4] = (plane) { { 0, 0, 1 }, position.z + distance }; // near
    planes[5] = (plane) { { 0, 0, -1 }, -position.z + distance }; // far
    return planes;
}

plane* create_test_planes(float distance) {
    plane* planes = malloc(6 * sizeof(plane));
    planes[0] = (plane) {{ 1.0f, 0.0f, 0.0f }, distance};  // Right plane: x = 1
    planes[1] = (plane) {{-1.0f, 0.0f, 0.0f }, distance};  // Left plane: x = -1
    planes[2] = (plane) {{ 0.0f, 1.0f, 0.0f }, distance};  // Top plane: y = 1
    planes[3] = (plane) {{ 0.0f, -1.0f, 0.0f }, distance}; // Bottom plane: y = -1
    planes[4] = (plane) {{ 0.0f, 0.0f, 1.0f }, distance};  // Far plane: z = 1
    planes[5] = (plane) {{ 0.0f, 0.0f, -1.0f }, distance}; // Near plane: z = -1
    return planes;
}

void calculate_frustum_planes_alternative(const float4x4 view_projection_matrix, plane *planes) {
    float4x4 mat = (view_projection_matrix);
    planes[0] = plane_from_float4(float4_subtract(mat.w, mat.x));   // r
    planes[1] = plane_from_float4(float4_add(mat.w, mat.x));        // l
    planes[2] = plane_from_float4(float4_subtract(mat.w, mat.y));   // t
    planes[3] = plane_from_float4(float4_add(mat.w, mat.y));        // b
    planes[4] = plane_from_float4(float4_subtract(mat.w, mat.z));   // far
    planes[5] = plane_from_float4(float4_add(mat.w, mat.z));        // near
    // float3_flip(&planes[4].normal);
}

/*void calculate_frustum_planes_old(const float4x4 transform_matrix, const float4x4 projection_matrix, plane *planes) {
    float3 *frustum = calculate_frustum_corners_old(projection_matrix, transform_matrix);
    calculate_planes_from_frustum(frustum, planes);
    free(frustum);
}*/


// Near plane
/*planes[0] = calculate_plane_from_points(frustum[0], frustum[1], frustum[2]);
// Far plane
planes[1] = calculate_plane_from_points(frustum[4], frustum[5], frustum[6]);
// Left plane
planes[2] = calculate_plane_from_points(frustum[0], frustum[4], frustum[7]);
// Right plane
planes[3] = calculate_plane_from_points(frustum[1], frustum[5], frustum[6]);
// Top plane
planes[4] = calculate_plane_from_points(frustum[3], frustum[0], frustum[7]);
// Bottom plane
planes[5] = calculate_plane_from_points(frustum[2], frustum[1], frustum[6]);*/

// transform frustum plane
/*void transform_plane(const float4x4 view_matrix, const float4x4 transform_matrix, plane *plane)  {
    const float4x4 inverse_mat = transform_matrix; // float4x4_inverse(view_matrix); // float4x4_multiply(transform,
    plane->normal = float4x4_multiply_float3(inverse_mat, plane->normal);
    normalize_plane(plane);
}*/

/*void transform_planes(const float4x4 transform_matrix, plane *planes) {
    // const float4x4 inverse_mat = transform; // float4x4_inverse(view_matrix); // float4x4_multiply(transform,
    for (int i = 0; i < 6; i++) planes[i].normal = float4x4_multiply_float3(transform_matrix, planes[i].normal);
    // normalize_plane(plane);
}*/

// this is wrong! - unitys CalculateFrustumPlanes - https://docs.unity3d.com/ScriptReference/GeometryUtility.CalculateFrustumPlanes.html
// view_projection_matrix?
/*void calculate_frustum_planes(const float4x4 mat, plane *planes) {
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
    // normalize_planes(planes);
    // transform_planes(mat, transform, planes);
}*/



/*oid calculate_plane(const float3 *p1, const float3 *p2, const float3 *p3, plane *plane_out) {
    float3 v1, v2, normal;
    // Calculate two vectors in the plane
    v1 = float3_subtract_float3(p2, p1);
    v2 = float3_subtract_float3(p3, p1);
    // Calculate the normal as the cross product of the two vectors
    normal.x = v1.y * v2.z - v1.z * v2.y;
    normal.y = v1.z * v2.x - v1.x * v2.z;
    normal.z = v1.x * v2.y - v1.y * v2.x;
    normal = float3_normalize(normal);
    // Calculate the distance from the plane to the origin
    plane_out->normal = normal;
    plane_out->distance = -(normal.x * p1->x + normal.y * p1->y + normal.z * p1->z);
}*/

float3 intersect_planes(plane plane1, plane plane2, plane plane3) {
    float3 intersection_point;

    float3 p1 = plane1.normal;
    float3 p2 = plane2.normal;
    float3 p3 = plane3.normal;
    float d1 = plane1.distance;
    float d2 = plane2.distance;
    float d3 = plane3.distance;

    float3 n1_cross_n2 = {
        p1.y * p2.z - p1.z * p2.y,
        p1.z * p2.x - p1.x * p2.z,
        p1.x * p2.y - p1.y * p2.x
    };
    float det = p3.x * n1_cross_n2.x + p3.y * n1_cross_n2.y + p3.z * n1_cross_n2.z;

    if (det == 0) {
        // Planes are parallel, no intersection point
        intersection_point.x = intersection_point.y = intersection_point.z = 0.0f;
    } else {
        float3 n2_cross_n3 = {
            p2.y * p3.z - p2.z * p3.y,
            p2.z * p3.x - p2.x * p3.z,
            p2.x * p3.y - p2.y * p3.x
        };
        float3 n3_cross_n1 = {
            p3.y * p1.z - p3.z * p1.y,
            p3.z * p1.x - p3.x * p1.z,
            p3.x * p1.y - p3.y * p1.x
        };

        intersection_point.x = (d1 * n2_cross_n3.x + d2 * n3_cross_n1.x + d3 * n1_cross_n2.x) / det;
        intersection_point.y = (d1 * n2_cross_n3.y + d2 * n3_cross_n1.y + d3 * n1_cross_n2.y) / det;
        intersection_point.z = (d1 * n2_cross_n3.z + d2 * n3_cross_n1.z + d3 * n1_cross_n2.z) / det;
    }
    return intersection_point;
}

float3* find_plane_corners(plane *planes) {
    float3 *corners = malloc(sizeof(float3) * 8);
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 5; ++j) {
            for (int k = j + 1; k < 6; ++k) {
                float3 new_point = intersect_planes(planes[i], planes[j], planes[k]);
                unsigned char added = 0;
                for (int a = 0; a < count; a++) {
                    if (float3_equals(new_point, corners[a])) {
                        added = 1;
                        break;
                    }
                }
                // If the new point is not already added, add it to the corners array
                if (!added) {
                    corners[count++] = new_point;
                    // Early return if all 8 corners are found
                    if (count == 8) {
                        return corners;
                    }
                }
            }
        }
    }
    return corners;
}

    // Calculate the frustum planes
    /*planes[0].normal.x = frustum[3].x - frustum[0].x;
    planes[0].normal.y = frustum[3].y - frustum[0].y;
    planes[0].normal.z = frustum[3].z - frustum[0].z;
    planes[1].normal.x = frustum[7].x - frustum[4].x;
    planes[1].normal.y = frustum[7].y - frustum[4].y;
    planes[1].normal.z = frustum[7].z - frustum[4].z;
    planes[2].normal.x = frustum[7].x - frustum[6].x;
    planes[2].normal.y = frustum[7].y - frustum[6].y;
    planes[2].normal.z = frustum[7].z - frustum[6].z;
    planes[3].normal.x = frustum[3].x - frustum[2].x;
    planes[3].normal.y = frustum[3].y - frustum[2].y;
    planes[3].normal.z = frustum[3].z - frustum[2].z;
    planes[4].normal.x = frustum[5].x - frustum[4].x;
    planes[4].normal.y = frustum[5].y - frustum[4].y;
    planes[4].normal.z = frustum[5].z - frustum[4].z;
    planes[5].normal.x = frustum[1].x - frustum[0].x;
    planes[5].normal.y = frustum[1].y - frustum[0].y;
    planes[5].normal.z = frustum[1].z - frustum[0].z;*/

    /*planes[0].normal = float3_cross(float3_subtract_float3(frustum[3], frustum[0]), float3_subtract_float3(frustum[1], frustum[0]));
    planes[1].normal = float3_cross(float3_subtract_float3(frustum[6], frustum[4]), float3_subtract_float3(frustum[5], frustum[4]));
    planes[2].normal = float3_cross(float3_subtract_float3(frustum[3], frustum[0]), float3_subtract_float3(frustum[2], frustum[0]));
    planes[3].normal = float3_cross(float3_subtract_float3(frustum[1], frustum[0]), float3_subtract_float3(frustum[2], frustum[0]));
    planes[4].normal = float3_cross(float3_subtract_float3(frustum[0], frustum[4]), float3_subtract_float3(frustum[1], frustum[5]));
    planes[5].normal = float3_cross(float3_subtract_float3(frustum[6], frustum[2]), float3_subtract_float3(frustum[7], frustum[3]));

    normalize_planes(planes);

    planes[0].distance = -float3_dot(planes[0].normal, frustum[0]);
    planes[1].distance = -float3_dot(planes[1].normal, frustum[4]);
    planes[2].distance = -float3_dot(planes[2].normal, frustum[6]);
    planes[3].distance = -float3_dot(planes[3].normal, frustum[2]);
    planes[4].distance = -float3_dot(planes[4].normal, frustum[0]);
    planes[5].distance = -float3_dot(planes[5].normal, frustum[0]);*/


/*unsigned char is_in_frustum(const plane *planes, const bounds b) {
    float3 corners[8]; // Calculate the corners of the bounding volume
    corners[0] = float3_add(b.center, float3_multiply_float3(b.extents, (float3){1, 1, 1}));
    corners[1] = float3_add(b.center, float3_multiply_float3(b.extents, (float3){1, 1, -1}));
    corners[2] = float3_add(b.center, float3_multiply_float3(b.extents, (float3){1, -1, 1}));
    corners[3] = float3_add(b.center, float3_multiply_float3(b.extents, (float3){1, -1, -1}));
    corners[4] = float3_add(b.center, float3_multiply_float3(b.extents, (float3){-1, 1, 1}));
    corners[5] = float3_add(b.center, float3_multiply_float3(b.extents, (float3){-1, 1, -1}));
    corners[6] = float3_add(b.center, float3_multiply_float3(b.extents, (float3){-1, -1, 1}));
    corners[7] = float3_add(b.center, float3_multiply_float3(b.extents, (float3){-1, -1, -1}));
    for (int i = 0; i < 6; i++) {
        unsigned char outside = 1;
        for (int j = 0; j < 8; j++) {
            if (float3_dot(corners[j], planes[i].normal) + planes[i].distance >= 0) {
                outside = 0;
                break;
            }
        }
        if (outside) return 0;
    }
    return 1;
}*/
