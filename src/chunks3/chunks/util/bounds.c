float3 calculate_vox_bounds(
    const int3 size,
    const float scale
) {
    float3 b = float3_from_int3(size);
    float3_scale_p(&b, scale * 0.5f);
    return b;
}

bounds calculate_chunk_bounds(
    const float3 position,
    const int3 size,
    const float scale
) {
    const float3 extents = float3_scale(float3_from_int3(size), scale * 0.5f);
    const float3 centre = float3_add(position, extents);
    return (bounds) { centre, extents };
}