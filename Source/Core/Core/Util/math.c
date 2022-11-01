// Find more math inspiration at https://gist.github.com/mattatz/86fff4b32d198d0928d0fa4ff32cf6fa

float4x4 float4x4_position(float3 position)
{
    float4x4 matrix = float4x4_identity();
    matrix.w.x = position.x;
    matrix.w.y = position.y;
    matrix.w.z = position.z;
    return matrix;
}

//! View Matrix multipled by projection and used to distort pixel magic.
float4x4 float4x4_view_matrix(float3 position, float3 forward, float3 up)
{
    float4x4 matrix = float4x4_position(float3_multiply_float(position, -1.0f));
    float3 side = { };
    side = float3_cross(forward, up);
    side = float3_normalize(side);
    matrix.x.x = side.x;
    matrix.y.x = side.y;
    matrix.z.x = side.z;
    matrix.x.y = up.x;
    matrix.y.y = up.y;
    matrix.z.y = up.z;
    matrix.x.z = -forward.x;
    matrix.y.z = -forward.y;
    matrix.z.z = -forward.z;
    return matrix;
}

void float4x4_rotate(float4x4 *matrix, const float4 rotation)
{
    matrix->x.x *= rotation.x;
    matrix->y.x *= rotation.x;
    matrix->z.x *= rotation.x;
    matrix->w.x *= rotation.x;
    matrix->x.y *= rotation.y;
    matrix->y.y *= rotation.y;
    matrix->z.y *= rotation.y;
    matrix->w.y *= rotation.y;
    matrix->x.z *= rotation.z;
    matrix->y.z *= rotation.z;
    matrix->z.z *= rotation.z;
    matrix->w.z *= rotation.z;
    matrix->x.w *= rotation.w;
    matrix->y.w *= rotation.w;
    matrix->z.w *= rotation.w;
    matrix->w.w *= rotation.w;
}

float4 quaternion_rotate(float4 q1, float4 q2)
{ 
    float4 qr;
    qr.x = (q1.w * q2.x) + (q1.x * q2.w) + (q1.y * q2.z) - (q1.z * q2.y);
    qr.y = (q1.w * q2.y) - (q1.x * q2.z) + (q1.y * q2.w) + (q1.z * q2.x);
    qr.z = (q1.w * q2.z) + (q1.x * q2.y) - (q1.y * q2.x) + (q1.z * q2.w);
    qr.w = (q1.w * q2.w) - (q1.x * q2.x) - (q1.y * q2.y) - (q1.z * q2.z);
    return qr;
}

void float4_divide(float4 *input, float division)
{
    input->x /= division;
    input->y /= division;
    input->z /= division;
    input->w /= division;
}

float4 quaternion_inverse(float4 q)
{
    float sqr = sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
    float4 output;
    output = float4_reverse(q);
    float4_divide(&output, sqr);
    return output;
}
            
float3 float3_rotate_float4(float4 rotation, float3 vertex3)
{
    // does this need conjugation(inverse(rot)) ?
    // Remove float4 use on vert
    float4 vertex = { vertex3.x, vertex3.y, vertex3.z, 0 };
    rotation = quaternion_inverse(rotation);
    float4 output = quaternion_rotate(float4_reverse(rotation), quaternion_rotate(vertex, rotation));
    return (float3) { output.x, output.y, output.z };
}

float4x4 quaternion_to_matrix(float4 quat)
{
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

float3 quaternion_to_euler(float4 q)
{
    float3 euler = { };
    // roll (x-axis rotation)
    double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
    double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
    euler.x = atan2(sinr_cosp, cosr_cosp);
    // pitch (y-axis rotation)
    double sinp = 2 * (q.w * q.y - q.z * q.x);
    if (abs(sinp) >= 1)
        euler.y = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
    else
        euler.y = asin(sinp);
    // yaw (z-axis rotation)
    double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
    double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
    euler.z = atan2(siny_cosp, cosy_cosp);
    euler.x /= degreesToRadians;
    euler.y /= degreesToRadians;
    euler.z /= degreesToRadians;
    return euler;
}

float4 quaternion_from_euler(float3 euler)
{
    float yaw = euler.x;
    float pitch = euler.y;
    float roll = euler.z;
    float4 output;
    output.x = sin(roll/2) * cos(pitch/2) * cos(yaw/2) - cos(roll/2) * sin(pitch/2) * sin(yaw/2);
    output.y = cos(roll/2) * sin(pitch/2) * cos(yaw/2) + sin(roll/2) * cos(pitch/2) * sin(yaw/2);
    output.z = cos(roll/2) * cos(pitch/2) * sin(yaw/2) - sin(roll/2) * sin(pitch/2) * cos(yaw/2);
    output.w = cos(roll/2) * cos(pitch/2) * cos(yaw/2) + sin(roll/2) * sin(pitch/2) * sin(yaw/2);
    return output;
}

/*int i, j;
for (i = 0; i < 4; ++i)
{
    for (j = 0; j < 4; ++j)
    {
        c [i + j * 4]= a[i + 4 * j] + b[i + 4 * j];
    }
}*/

// float* float4x4_multiply(float* a, const float* b)
// {
//     float* c = malloc(16 * 4);
//     for (unsigned j = 0; j < 16; j++)
//     {
//         unsigned i = j % 4;
//         unsigned j4 = j & 12;  // j4 = j / 4 * 4;
//         c[j] = 
//             a[j4 + 0]*b[i + 0] + a[j4 + 1]*b[i + 4]
//             + a[j4 + 2]*b[i + 8] + a[j4 + 3]*b[i + 12];
//     }
//     return c;
// }