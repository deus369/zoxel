#define quaternion_identity (float4) { 0, 0, 0, 1 }
#define quaternion_flipped_y (float4) { 0, 0, 0, 1 }
const float significant_digits_check = 100000.0f;
#define quaternion_pi_2 1.5707f

void quaternion_normalize(float4 *quaternion) {
    float magnitude = sqrt(quaternion->x * quaternion->x + quaternion->y * quaternion->y + quaternion->z * quaternion->z + quaternion->w * quaternion->w);
    if (magnitude != 0.0f) {
        quaternion->x /= magnitude;
        quaternion->y /= magnitude;
        quaternion->z /= magnitude;
        quaternion->w /= magnitude;
    }
}

static inline float quaternion_magnitude(float4 quaternion) {
    return sqrt(quaternion.x * quaternion.x + quaternion.y * quaternion.y + quaternion.z * quaternion.z);
}

static inline float4 quaternion_normalized(float4 quaternion, float magnitude) {
    return (float4) { quaternion.x / magnitude, quaternion.y / magnitude, quaternion.z / magnitude, 0.0f };
}

static inline float quaternion_to_euler_y(float4 q) {
    double sinp = 2 * (q.w * q.y - q.z * q.x);
    if (double_abs(sinp) >= 1) {
        return copysign(M_PI / 2, sinp); // use 90 degrees if out of range
    }
    else {
        return asin(sinp);
    }
}

static inline float quaternion_to_euler_x(float4 q) {
    float sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
    float cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
    return atan2(sinr_cosp, cosr_cosp);
}

static inline float quaternion_to_euler_z(float4 q) {
    float cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
    float siny_cosp = 2 * (q.w * q.z + q.x * q.y);
    if (fabs(cosy_cosp) < 1e-6) return 0.0f;
    else return atan2(siny_cosp, cosy_cosp);
}

static inline void correct_euler_quadrant(float3* euler) {
    // quadrant corrections
    float euler_x = (int) ceil(euler->x * significant_digits_check) / significant_digits_check;
    float euler_z = (int) ceil(euler->z * significant_digits_check) / significant_digits_check;
    if (euler_x >= quaternion_pi_2 && euler_z >= quaternion_pi_2) {
        euler->x -= M_PI;
        euler->y = - euler->y + M_PI;
        euler->z -= M_PI;
        #ifdef debug_quadrant_correctnion
            zox_log(" +> in 3rd quadrant! [%fx%fx%f]\n", euler->x, euler->y, euler->z);
        #endif
    } else if (euler_x <= -quaternion_pi_2 && euler_z <= -quaternion_pi_2) {
        // printf("    in 4th quadrant! - M_PI - M_PI\n");
        euler->x += M_PI;
        euler->y = - euler->y + M_PI;
        euler->z += M_PI;
        #ifdef debug_quadrant_correctnion
            zox_log(" +> in 4thrd quadrant! [%fx%fx%f]\n", euler->x, euler->y, euler->z);
        #endif
    } else if (euler_x <= -quaternion_pi_2 && euler_z >= quaternion_pi_2) {
        euler->x += M_PI;
        euler->y = - euler->y + M_PI;
        euler->z -= M_PI;
        #ifdef debug_quadrant_correctnion
            zox_log(" +> in 1st quadrant! [%fx%fx%f]\n", euler->x, euler->y, euler->z);
        #endif
    } else if (euler_x >= quaternion_pi_2 && euler_z <= -quaternion_pi_2) {
        euler->x -= M_PI;
        euler->y = - euler->y - M_PI;
        euler->z += M_PI;
        #ifdef debug_quadrant_correctnion
            zox_log(" +> in 2nd quadrant! [%fx%fx%f]\n", euler->x, euler->y, euler->z);
        #endif
    } else {
        #ifdef debug_quadrant_correctnion
            zox_log(" +> in no quadrant! [%fx%fx%f]\n", euler->x, euler->y, euler->z);
        #endif
    }
    // +> in no quadrant! [1.570796x-0.000000x-3.141593]

    if (euler->y < -M_PI) euler->y += 2 * M_PI;
    else if (euler->y > M_PI) euler->y -= 2 * M_PI;
}

static inline float3 quaternion_to_euler(float4 q) {
    float3 euler = { };
    euler.x = quaternion_to_euler_x(q); // roll (x-axis rotation)
    euler.y = quaternion_to_euler_y(q); // pitch (y-axis rotation)
    euler.z = quaternion_to_euler_z(q); // yaw (z-axis rotation)
    correct_euler_quadrant(&euler);
    return euler;
}

static inline float3 quaternion_to_euler_360(float4 q) {
    return float3_scale(quaternion_to_euler(q), (180.0f / M_PI));
}

static inline byte quaternion_to_quadrant(float4 q) {
    float degree = quaternion_to_euler(q).y * (180.0f / M_PI);
    // float degree = quaternion_to_euler_y(q) * (180.0f / M_PI);
    if (degree < 0) degree += 360;
    // printf("    - degree [%f]\n", degree);
    return (byte)((degree + 0.1f) / 90) % 4;  // 0.1 = 45 before
}

static inline float4 quaternion_from_euler(float3 euler) {
    float roll = euler.x;
    float pitch = euler.y;
    float yaw = euler.z;
    float cy = cos(yaw * 0.5f);
    float sy = sin(yaw * 0.5f);
    float cp = cos(pitch * 0.5f);
    float sp = sin(pitch * 0.5f);
    float cr = cos(roll * 0.5f);
    float sr = sin(roll * 0.5f);
    float4 q;
    q.w = cr * cp * cy + sr * sp * sy;
    q.x = sr * cp * cy - cr * sp * sy;
    q.y = cr * sp * cy + sr * cp * sy;
    q.z = cr * cp * sy - sr * sp * cy;
    return q;
}

static inline float4 quaternion_from_between_vectors(float3 u, float3 v) {
    float4 output = float4_zero;
    float3 cross = float3_cross(u, v);
    output.x = cross.x;
    output.y = cross.y;
    output.z = cross.z;
    output.w = sqrt(pow(float3_length(u), 2) * pow(float3_length(v), 2)) + float3_dot(u, v);
    quaternion_normalize(&output);
    return output;
}

// this seems to be okay?
static inline float4 quaternion_from_normal(float3 normal) {
    float3 axis;
    float4 quaternion;
    // Step 1: Normalize the normal vector
    float length = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    normal.x /= length;
    normal.y /= length;
    normal.z /= length;
    // Step 2: Calculate the angle of rotation
    float angle = acos(normal.z); // dot(normal, (0, 0, 1)) = normal.z
    // Step 3: Calculate the axis of rotation
    axis.x = -normal.y;
    axis.y = normal.x;
    axis.z = 0;
    // Step 4: Create the quaternion
    quaternion.x = axis.x * sin(angle / 2);
    quaternion.y = axis.y * sin(angle / 2);
    quaternion.z = axis.z * sin(angle / 2);
    quaternion.w = cos(angle / 2);
    return quaternion;
}

void print_quadrant(float4 q) {
    byte quadrant = quaternion_to_quadrant(q);
    // byte quadrant = get_quadrant(quaternion_to_euler(q));
    if (quadrant == 0) {
        zox_log(" + quadrant 1\n");
    } else if (quadrant == 1) {
        zox_log(" + quadrant 2\n");
    } else if (quadrant == 2) {
        zox_log(" + quadrant 3\n");
    } else if (quadrant == 3) {
        zox_log(" + quadrant 4\n");
    } else {
        zox_log(" + quadrant ?\n");
    }
}

void float4_print_euler(float4 input) {
    float3 euler = float3_divide_float(quaternion_to_euler(input), degreesToRadians);
    zox_log("-> Euler [x:%f y:%f z:%f]\n", euler.x, euler.y, euler.z);
}

static inline byte quaternion_equal(float4 a, float4 b) {
    return ((a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w) ||
        (a.x == -b.x && a.y == -b.y && a.z == -b.z && a.w == -b.w));
}

byte test_quaternion_math(float4 input) {
    float3 input_e = quaternion_to_euler(input);
    float4 output = quaternion_from_euler(input_e);
    zox_log("     - in e [%fx%fx%f]\n", input_e.x, input_e.y, input_e.z);
    if (quaternion_equal(input, output)) {
        // zox_log(" - quaternion test success\n");
        return 1;
    } else {
        // float3 euler2 = quaternion_to_euler(output);
        // zox_log(" - quaternion test failed:\n");
        // zox_log("     - out e [%fx%fx%f]\n", euler2.x, euler2.y, euler2.z);
        // zox_log("     - in q [%fx%fx%fx%f]\n", input.x, input.y, input.z, input.w);
        // zox_log("     - out q [%fx%fx%fx%f]\n", output.x, output.y, output.z, output.w);
        return 0;
    }
}

static inline float4 quaternion_from_axis_angle(float3 v, float a) {
    float4 q;
    float s = sin(a / 2.0f);
    q.x = v.x * s;
    q.y = v.y * s;
    q.z = v.z * s;
    q.w = cos(a / 2.0f);
    return q;
}

// is there a way to do this with just quaternions without messing up the magnitude??
static inline float4 get_delta_rotation(float4 quaternion, float magnitude, double delta_time) {
    //float4 normalized = quaternion_normalized(quaternion, magnitude);
    //return quaternion_from_axis_angle(magnitude * delta_time, normalized.x, normalized.y, normalized.z);
    float3 euler = quaternion_to_euler(quaternion);
    float3_scale_p(&euler, magnitude);
    return quaternion_from_euler(euler);
    // return (float4) { magnitude * quaternion.x, magnitude * quaternion.y, magnitude * quaternion.z, magnitude * quaternion.w };
}