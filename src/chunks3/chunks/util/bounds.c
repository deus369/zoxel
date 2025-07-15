float3 calculate_vox_bounds(const int3 chunk_size, const float vox_scale) {
    float3 vox_bounds = float3_from_int3(chunk_size);
    float3_multiply_float_p(&vox_bounds, vox_scale * 0.25f);
    return vox_bounds;
}

bounds calculate_chunk_bounds(const float3 position3D, const int3 chunk_size, const float vox_scale) {
    const float3 extents = float3_multiply_float(float3_from_int3(chunk_size), vox_scale * 0.5f);
    const float3 bounds_position = float3_add(position3D, extents);
    // zox_log(" cb2 c[%.0fx%.0fx%.0f] e[%.0fx%.0fx%.0f]\n", bounds_position.x, bounds_position.x, bounds_position.y, extents.y, extents.z, extents.z)
    return (bounds) { bounds_position, extents };
}