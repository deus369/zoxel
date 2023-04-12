float quaternion_to_euler_y(float4 q) {
    double sinp = 2 * (q.w * q.y - q.z * q.x);
    if (double_abs(sinp) >= 1) {
        return copysign(M_PI / 2, sinp); // use 90 degrees if out of range
    } else {
        return asin(sinp);
    }
}

float quaternion_to_euler_x(float4 q) {
    float sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
    float cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
    return atan2(sinr_cosp, cosr_cosp);
}

float quaternion_to_euler_z(float4 q) {
    float cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
    float siny_cosp = 2 * (q.w * q.z + q.x * q.y);
    if (fabs(cosy_cosp) < 1e-6) {
        return 0.0f;
    } else {
        return atan2(siny_cosp, cosy_cosp);
    }
}

void correct_euler_quadrant(float3* euler) {
    // quadrant corrections
    if (euler->x > M_PI_2 && euler->z > M_PI_2) {
        // printf("    in 3rd quadrant! [%fx%fx%f]\n", euler.x, euler.y, euler.z);
        euler->x -= M_PI;
        euler->y = - euler->y + M_PI;
        euler->z -= M_PI;
    } else if (euler->x < -M_PI_2 && euler->z < -M_PI_2) {
        // printf("    in 4th quadrant! - M_PI - M_PI\n");
        euler->x += M_PI;
        euler->y = - euler->y + M_PI;
        euler->z += M_PI;
    } else if (euler->x < -M_PI_2 && euler->z > M_PI_2) {
        euler->x += M_PI;
        euler->y = - euler->y + M_PI;
        euler->z -= M_PI;
        // printf("    loom\n");
    } else if (euler->x > M_PI_2 && euler->z < -M_PI_2) {
        euler->x -= M_PI;
        euler->y = - euler->y - M_PI;
        euler->z += M_PI;
        // printf("    boom\n");
    }
    if (euler->y < -M_PI) {
        euler->y += 2 * M_PI;
    }
    if (euler->y > M_PI) {
        euler->y -= 2 * M_PI;
    }
}

float3 quaternion_to_euler(float4 q) {
    float3 euler = { };
    // roll (x-axis rotation)
    euler.x = quaternion_to_euler_x(q);
    // pitch (y-axis rotation)
    euler.y = quaternion_to_euler_y(q);
    // yaw (z-axis rotation)
    euler.z = quaternion_to_euler_z(q);
    correct_euler_quadrant(&euler);
    return euler;
}

unsigned char quaternion_to_quadrant(float4 q) {
    float degree = quaternion_to_euler(q).y * (180.0f / M_PI);
    // float degree = quaternion_to_euler_y(q) * (180.0f / M_PI);
    if (degree < 0) {
         degree += 360;
    }
    // printf("    - degree [%f]\n", degree);
    return (unsigned char)((degree + 0.1f) / 90) % 4;  // 0.1 = 45 before
}

float4 quaternion_from_euler(float3 euler) {
    /*float yaw = euler.x;
    float pitch = euler.y;
    float roll = euler.z;*/
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

#define quaternion_identity (float4) { 0, 0, 0, 1 }

/*euler.x /= degreesToRadians;
euler.y /= degreesToRadians;
euler.z /= degreesToRadians;*/

void print_quadrant(float4 q) {
    unsigned char quadrant = quaternion_to_quadrant(q);
    // unsigned char quadrant = get_quadrant(quaternion_to_euler(q));
    if (quadrant == 0) {
        zoxel_log(" + quadrant 1\n");
    } else if (quadrant == 1) {
        zoxel_log(" + quadrant 2\n");
    } else if (quadrant == 2) {
        zoxel_log(" + quadrant 3\n");
    } else if (quadrant == 3) {
        zoxel_log(" + quadrant 4\n");
    } else {
        zoxel_log(" + quadrant ?\n");
    }
}

float4x4 quaternion_to_matrix(float4 quat) {
    float4x4 m = float4x4_identity();
    float x = quat.x;
    float y = quat.y;
    float z = quat.z;
    float w = quat.w;
    float x2 = x + x;
    float y2 = y + y;
    float z2 = z + z;
    float xx = x * x2;
    float xy = x * y2;
    float xz = x * z2;
    float yy = y * y2;
    float yz = y * z2;
    float zz = z * z2;
    float wx = w * x2;
    float wy = w * y2;
    float wz = w * z2;
    m.x.x = 1.0 - (yy + zz);
    m.x.y = xy - wz;
    m.x.z = xz + wy;
    m.y.x = xy + wz;
    m.y.y = 1.0 - (xx + zz);
    m.y.z = yz - wx;
    m.z.x = xz - wy;
    m.z.y = yz + wx;
    m.z.z = 1.0 - (xx + yy);
    m.w.w = 1.0;
    return m;
}

void float4_print_euler(float4 input) {
    float3 euler = float3_divide_float(quaternion_to_euler(input), degreesToRadians);
    zoxel_log("-> Euler [x:%f y:%f z:%f]\n", euler.x, euler.y, euler.z);
}

unsigned char quaternion_equal(float4 a, float4 b) {
    return ((a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w) ||
        (a.x == -b.x && a.y == -b.y && a.z == -b.z && a.w == -b.w));
}

unsigned char test_quaternion_math(float4 input) {
    float3 input_e = quaternion_to_euler(input);
    float4 output = quaternion_from_euler(input_e);
    zoxel_log("     - in e [%fx%fx%f]\n", input_e.x, input_e.y, input_e.z);
    if (quaternion_equal(input, output)) {
        // zoxel_log(" - quaternion test success\n");
        return 1;
    } else {
        // float3 euler2 = quaternion_to_euler(output);
        // zoxel_log(" - quaternion test failed:\n");
        // zoxel_log("     - out e [%fx%fx%f]\n", euler2.x, euler2.y, euler2.z);
        // zoxel_log("     - in q [%fx%fx%fx%f]\n", input.x, input.y, input.z, input.w);
        // zoxel_log("     - out q [%fx%fx%fx%f]\n", output.x, output.y, output.z, output.w);
        return 0;
    }
}

float4 quaternion_from_axis_angle(float angle, float x, float y, float z) {
    float4 q;
    float s = sin(angle / 2.0f);
    q.x = x * s;
    q.y = y * s;
    q.z = z * s;
    q.w = cos(angle / 2.0f);
    return q;
}

void quaternion_normalize(float4 *quaternion) {
    float magnitude = sqrt(quaternion->x * quaternion->x + quaternion->y * quaternion->y + quaternion->z * quaternion->z + quaternion->w * quaternion->w);
    if (magnitude != 0.0f) {
        quaternion->x /= magnitude;
        quaternion->y /= magnitude;
        quaternion->z /= magnitude;
        quaternion->w /= magnitude;
    }
}

float quaternion_magnitude(float4 quaternion) {
    return sqrt(quaternion.x * quaternion.x + quaternion.y * quaternion.y + quaternion.z * quaternion.z);
}

float4 quaternion_normalized(float4 quaternion, float magnitude) {
    return (float4) { quaternion.x / magnitude, quaternion.y / magnitude, quaternion.z / magnitude, 0.0f };
}

float4 get_delta_rotation(float4 quaternion, float magnitude, double delta_time) {
    float4 normalized = quaternion_normalized(quaternion, magnitude);
    return quaternion_from_axis_angle(magnitude * delta_time, normalized.x, normalized.y, normalized.z);     
}

/*float yaw = euler.x;
float pitch = euler.y;
float roll = euler.z;
float4 output;
output.x = sin(roll/2) * cos(pitch/2) * cos(yaw/2) - cos(roll/2) * sin(pitch/2) * sin(yaw/2);
output.y = cos(roll/2) * sin(pitch/2) * cos(yaw/2) + sin(roll/2) * cos(pitch/2) * sin(yaw/2);
output.z = cos(roll/2) * cos(pitch/2) * sin(yaw/2) - sin(roll/2) * sin(pitch/2) * cos(yaw/2);
output.w = cos(roll/2) * cos(pitch/2) * cos(yaw/2) + sin(roll/2) * sin(pitch/2) * sin(yaw/2);
return output;*/
    // unsigned char quadrant = get_quadrant((float3) { input->x, input->y, input->z });
    /*if (quadrant == 2) {
        input->x += M_PI;
        input->y = - input->y - M_PI;
        input->z += M_PI;
    } else if (quadrant == 3) {
        input->x -= M_PI;
        input->y = - input->y + M_PI;
        input->z -= M_PI;
    }*/
    // quadrant corrections
    /*if (euler->x >= M_PI && euler->z >= M_PI) {
        // printf("    in 3rd quadrant! [%fx%fx%f]\n", euler.x, euler.y, euler.z);
        euler->x -= M_PI;
        euler->y = - euler->y + M_PI;
        euler->z -= M_PI;
    } else if (euler->x <= -M_PI && euler->z <= -M_PI) {
        // printf("    in 4th quadrant! - M_PI - M_PI\n");
        euler->x += M_PI;
        euler->y = euler->y - M_PI;
        euler->z += M_PI;
    }*/
    /*double sinp = 2 * (q.w * q.y - q.z * q.x);
    double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
    double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
    float euler_x = - atan2(sinr_cosp, cosr_cosp);
    float euler_y;
    if (double_abs(sinp) >= 1) {
        euler_y = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
    } else {
        euler_y = asin(sinp);
    }
    if (euler_x == 0.0f) {
        if (euler_y >= 0 && euler_y <= M_PI / 2.0f) {
            zoxel_log(" + quadrant 1\n");
        } else if (euler_y >= -M_PI / 2.0f && euler_y <= 0) {
            zoxel_log(" + quadrant 2\n");
        }
    } else {
        if (euler_y >= 0 && euler_y <= M_PI / 2.0f) {
            zoxel_log(" + quadrant 4\n");   // - pi x z
        } else if (euler_y >= -M_PI / 2.0f && euler_y <= 0) {
            zoxel_log(" + quadrant 3\n");   // + pi x z
        }
    }*/
    /* else if (euler_y >= - M_PI / 4.0f) {
        zoxel_log(" + quadrant 3\n");
    } else if (euler_y >= - M_PI / 2.0f) {
        zoxel_log(" + quadrant 4\n");
    } else {
        zoxel_log(" + quadrant ? [%f]\n", euler_y);
    }*//*unsigned char quaternion_to_quadrant(float4 q) {
    float x = q.x;
    float z = q.z;
    float angle = atan2(z, x);
    float degree = angle * 180 / M_PI;
    if (degree < 0) {
        degree += 360;
    }
    int quadrant = (int) degree / 90;
    return quadrant;
}*/

/*unsigned char get_quadrant(float3 input) {
    if (input.x == 0.0f) {
        if (input.y >= 0 && input.y <= M_PI / 2.0f) {
            return 0;
        } else if (input.y >= -M_PI / 2.0f && input.y <= 0) {
            return 1;
        }
    } else {
        if (input.y >= 0 && input.y <= M_PI / 2.0f) {
            return 3;
        } else if (input.y >= -M_PI / 2.0f && input.y <= 0) {
            return 2;
        }
    }
    return 4;
}*/


/*void correct_euler_for_quadrants(float4 q, float3* euler) {
    unsigned char quadrant = quaternion_to_quadrant(q);
    correct_euler_quadrant(euler);
}

float3 quaternion_to_euler(float4 q) {
    float3 euler = { };
    // roll (x-axis rotation)
    euler.x = quaternion_to_euler_x(q);
    // pitch (y-axis rotation)
    euler.y = quaternion_to_euler_y(q);
    // yaw (z-axis rotation)
    euler.z = quaternion_to_euler_z(q);
    correct_euler_for_quadrants(q, &euler);
    return euler;
}*/