typedef struct {
    float distance;
    float3 normal;
} plane;

typedef struct {
    float3 center;
    float3 extents;
} bounds;


float3 calculate_point_on_plane(const float3 normal, const float distance) {
    // Here, we just choose an arbitrary point on the plane
    // You can choose any point that makes sense for your application
    return (float3) { normal.x * distance, normal.y * distance, normal.z * distance};
}
