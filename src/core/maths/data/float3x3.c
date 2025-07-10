static inline float3x3 quaternion_to_float3x3(float4 q) {
    return (float3x3) {
        (float3) { 1 - 2*q.y*q.y - 2*q.z*q.z, 2*q.x*q.y - 2*q.z*q.w, 2*q.x*q.z + 2*q.y*q.w },
        (float3) { 2*q.x*q.y + 2*q.z*q.w, 1 - 2*q.x*q.x - 2*q.z*q.z, 2*q.y*q.z - 2*q.x*q.w },
        (float3) { 2*q.x*q.z - 2*q.y*q.w, 2*q.y*q.z + 2*q.x*q.w, 1 - 2*q.x*q.x - 2*q.y*q.y }
    };
}

static inline float4 float3x3_to_float4(float3x3 mat) {
    float4 quat;
    float tr = mat.x.x + mat.y.y + mat.z.z;
    if (tr > 0) {
        float S = sqrt(tr + 1.0) * 2; // S=4*qw
        quat.w = 0.25 * S;
        quat.x = (mat.z.y - mat.y.z) / S;
        quat.y = (mat.x.z - mat.z.x) / S;
        quat.z = (mat.y.x - mat.x.y) / S;
    } else if ((mat.x.x > mat.y.y) && (mat.x.x > mat.z.z)) {
        float S = sqrt(1.0 + mat.x.x - mat.y.y - mat.z.z) * 2; // S=4*qx
        quat.w = (mat.z.y - mat.y.z) / S;
        quat.x = 0.25 * S;
        quat.y = (mat.x.y + mat.y.x) / S;
        quat.z = (mat.x.z + mat.z.x) / S;
    } else if (mat.y.y > mat.z.z) {
        float S = sqrt(1.0 + mat.y.y - mat.x.x - mat.z.z) * 2; // S=4*qy
        quat.w = (mat.x.z - mat.z.x) / S;
        quat.x = (mat.x.y + mat.y.x) / S;
        quat.y = 0.25 * S;
        quat.z = (mat.y.z + mat.z.y) / S;
        } else {
        float S = sqrt(1.0 + mat.z.z - mat.x.x - mat.y.y) * 2; // S=4*qz
        quat.w = (mat.y.x - mat.x.y) / S;
        quat.x = (mat.x.z + mat.z.x) / S;
        quat.y = (mat.y.z + mat.z.y) / S;
        quat.z = 0.25 * S;
    }
    return quat;
}