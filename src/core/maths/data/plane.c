typedef struct {
    float3 normal;
    float distance;
} plane;

plane plane_from_float4(const float4 v) {
    return (plane) { { v.x, v.y, v.z }, v.w };
}
