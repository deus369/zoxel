static inline float quaternion_to_euler_y2(float4 q) {
    // 2*(w*y + x*z)
    float num   = 2.0f * (q.w * q.y + q.x * q.z);
    // 1 - 2*(y*y + z*z)
    float denom = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
    return atan2f(num, denom);
}

static inline float3 quaternion_rotate_vector(float4 q, float3 v) {
    // Rotate vector v by quaternion q
    float3 u = { q.x, q.y, q.z };
    float s = q.w;
    float3 uv = float3_cross(u, v);
    float3 uuv = float3_cross(u, uv);
    return float3_add(v, float3_add(float3_scale(uv, 2.0f * s), float3_scale(uuv, 2.0f)));
}

// Returns q1 * q2
static inline float4 quaternion_multiply(float4 q1, float4 q2) {
    return (float4) {
        q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y,
        q1.w*q2.y - q1.x*q2.z + q1.y*q2.w + q1.z*q2.x,
        q1.w*q2.z + q1.x*q2.y - q1.y*q2.x + q1.z*q2.w,
        q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z
    };
}





// Dot product of two quaternions treated as 4D vectors
float quaternion_dot(float4 a, float4 b) {
    return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}

// Scale each component of the quaternion by s
float4 quaternion_scale(float4 q, float s) {
    return (float4){
        q.x * s,
        q.y * s,
        q.z * s,
        q.w * s
    };
}

float quaternion_angle(float4 q) {
    // clamp w to valid acos domain
    float w = q.w;
    if (w >  1.0f) w =  1.0f;
    if (w < -1.0f) w = -1.0f;

    // angle = 2 * arccos(w)
    float angle = 2.0f * acosf(w);
    return angle;
}

// Component‑wise addition of two quaternions
float4 quaternion_add(float4 a, float4 b) {
    return (float4){
        a.x + b.x,
        a.y + b.y,
        a.z + b.z,
        a.w + b.w
    };
}

// Normalize a quaternion (make it unit‑length)
float4 quaternion_normalize2(float4 q) {
    float mag = sqrtf(
        q.x*q.x +
        q.y*q.y +
        q.z*q.z +
        q.w*q.w
    );
    if (mag < 1e-8f) {
        // avoid division by zero—return identity quaternion
        return (float4){ 0, 0, 0, 1 };
    }
    float inv = 1.0f / mag;
    return (float4){
        q.x * inv,
        q.y * inv,
        q.z * inv,
        q.w * inv
    };
}

/// Spherical linear interpolation between unit‑quaternions q1→q2 by t∈[0…1]
float4 quaternion_slerp(float4 q1, float4 q2, float t) {
    // 1) Compute dot product to get cosine of the angle between quats
    float cosTheta = quaternion_dot(q1, q2);

    // 2) If negative, flip one quaternion to take the shorter path
    if (cosTheta < 0.0f) {
        q2 = quaternion_scale(q2, -1.0f);
        cosTheta = -cosTheta;
    }

    // 3) If they’re almost identical, do a simple lerp + normalize
    const float LERP_THRESHOLD = 0.9995f;
    if (cosTheta > LERP_THRESHOLD) {
        float4 result = quaternion_add(
            quaternion_scale(q1, 1.0f - t),
                                       quaternion_scale(q2,        t)
        );
        return quaternion_normalize2(result);
    }

    // 4) Basic SLERP
    float theta0    = acosf(cosTheta);      // angle between input quaternions
    float sinTheta0 = sinf(theta0);         // compute this once
    float theta     = theta0 * t;           // angle for this t
    float sinTheta  = sinf(theta);

    float s0 = cosf(theta) - cosTheta * (sinTheta / sinTheta0);
    float s1 = sinTheta / sinTheta0;

    float4 partA = quaternion_scale(q1, s0);
    float4 partB = quaternion_scale(q2, s1);
    return quaternion_add(partA, partB);
}
