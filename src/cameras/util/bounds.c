byte is_bounds_in_position_bounds(const float6 limits, const bounds b) {
    const float3 min_b = float3_subtract(b.center, b.extents);
    const float3 max_b = float3_add(b.center, b.extents);
    return (!(max_b.x < limits.x || min_b.x > limits.y || max_b.y < limits.z || min_b.y > limits.w || max_b.z < limits.u || min_b.z > limits.v));
}