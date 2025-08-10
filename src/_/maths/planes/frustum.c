// Remember: So i finally gett  it, we have 6 planes, normal + distance are their formula
// A normal is direction plane faces, distance is from origin, you can draw this actually
// we have 6, they overlap, but they should all be forming a shape, facing out? idk
// Our check checks if the bounding box intersects with every plane, well checks the side it's on
// if it's not on every side, it's in middle, i.e. inside the cage / frustum shape
// we need to draw these planes. we can get their overlapping 8 points?
// return float3_dot(p.normal, point) >= p.distance;

#define frustum_eps 0.01f   // was 0 before

// Returns 1 if the point is outside the plane
static inline byte is_outside_plane(const plane p, const float3 point) {
    // Positive distance means point is in direction of normal
    return (float3_dot(p.normal, point) - p.distance) > frustum_eps;
}

// checks if any part of bounds is inside 6 planes

byte is_in_frustum(const plane *planes, bounds b, byte inwards) {
    // Precompute the 8 corners of the bounding box
    float3 corners[8];
    corners[0] = float3_add(b.center, (float3){-b.extents.x, -b.extents.y, -b.extents.z});
    corners[1] = float3_add(b.center, (float3){-b.extents.x, -b.extents.y,  b.extents.z});
    corners[2] = float3_add(b.center, (float3){-b.extents.x,  b.extents.y, -b.extents.z});
    corners[3] = float3_add(b.center, (float3){-b.extents.x,  b.extents.y,  b.extents.z});
    corners[4] = float3_add(b.center, (float3){ b.extents.x, -b.extents.y, -b.extents.z});
    corners[5] = float3_add(b.center, (float3){ b.extents.x, -b.extents.y,  b.extents.z});
    corners[6] = float3_add(b.center, (float3){ b.extents.x,  b.extents.y, -b.extents.z});
    corners[7] = float3_add(b.center, (float3){ b.extents.x,  b.extents.y,  b.extents.z});

    // For each plane, if all corners are outside, reject the box
    for (byte i = 0; i < 6; i++) {
        byte all_outside = 1;
        for (byte c = 0; c < 8; c++) {
            if (inwards && is_outside_plane(planes[i], corners[c])) {
                all_outside = 0;
                break;
            } else if (!inwards && !is_outside_plane(planes[i], corners[c])) {
                all_outside = 0;
                break;
            }
        }
        if (all_outside) {
            return 0; // outside frustum
        }
    }
    return 1; // inside or intersecting
}