static inline plane plane_from_float4(const float4 v) {
    return (plane) { { v.x, v.y, v.z }, v.w };
}
