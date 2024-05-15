typedef struct {
    float distance;
    float3 normal;
} plane;

float3 calculate_point_on_plane(const float3 normal, const float distance) {
    // Here, we just choose an arbitrary point on the plane
    // You can choose any point that makes sense for your application
    return (float3) { normal.x * distance, normal.y * distance, normal.z * distance};
}

unsigned char compare_point_on_plane(const float3 point, const plane p) {
    float distance = float3_dot(point, p.normal) - p.distance;
    if (distance > 0) {
        return 1; // Point lies on the side of the plane pointed by the normal
    } else if (distance < 0) {
        return 0; // Point lies on the opposite side of the plane
    } else {
        return 2; // Point lies exactly on the plane
    }
}
