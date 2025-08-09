static inline void float6_scale_p(float6* input, const float m) {
    input->x *= m;
    input->y *= m;
    input->z *= m;
    input->w *= m;
    input->u *= m;
    input->v *= m;
}

// float6: x=minX, y=maxX, z=minY, w=maxY, u=minZ, v=maxZ
void grow_bounds(float6 *bounds, float factor) {
    float cx = (bounds->x + bounds->y) * 0.5f;
    float cy = (bounds->z + bounds->w) * 0.5f;
    float cz = (bounds->u + bounds->v) * 0.5f;

    float half_dx = (bounds->y - bounds->x) * 0.5f * factor;
    float half_dy = (bounds->w - bounds->z) * 0.5f * factor;
    float half_dz = (bounds->v - bounds->u) * 0.5f * factor;

    bounds->x = cx - half_dx;
    bounds->y = cx + half_dx;
    bounds->z = cy - half_dy;
    bounds->w = cy + half_dy;
    bounds->u = cz - half_dz;
    bounds->v = cz + half_dz;
}
