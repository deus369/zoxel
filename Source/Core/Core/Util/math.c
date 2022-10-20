#include <math.h> // for sqrt
#include <stdlib.h>
#include <stdio.h>
#ifndef M_PI
#define M_PI 3.141592653589793
#endif
#define degreesToRadians (M_PI * 2) / 360.0f
// const float degreesToRadians = (M_PI * 2) / 360.0f;

float3 normalize(float3 input)
{
    float length = sqrt(input.x * input.x + input.y * input.y + input.z * input.z);
    return (float3) { input.x / length, input.y / length, input.z / length };
}

float3 cross(float3 a, float3 b)
{
    return (float3) { 
        a.y * b.z - a.z * b.y,
        a.y * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
     };
}

float4x4 CreateZeroMatrix()
{
    float4x4 identity; // = malloc(16 * 4);
    float* identity2 = (float*) &identity;
    for (int i = 0; i < 16; i++)
    {
        identity2[i] = 0;
    }
    return identity;
}

float4x4 CreateIdentityMatrix()
{
    float4x4 identity = CreateZeroMatrix();
    identity.x.x = 1;
    identity.y.y = 1;
    identity.z.z = 1;
    identity.w.w = 1;
    return identity;
}

void printMatrix(const float4x4 matrix)
{
    const float* matrix2 = (float*) &matrix;
    printf("Matrix;\n\t[%f\t%f\t%f\t%f]\n\t[%f\t%f\t%f\t%f]\n\t[%f\t%f\t%f\t%f]\n\t[%f\t%f\t%f\t%f]\n",
         matrix2[0], matrix2[1], matrix2[2], matrix2[3],
         matrix2[4], matrix2[5], matrix2[6], matrix2[7],
         matrix2[8], matrix2[9], matrix2[10], matrix2[11],
         matrix2[12], matrix2[13], matrix2[14], matrix2[15]);
}

void print_float4(const float4 input)
{
    printf("Float4 [%f %f %f %f]\n", input.x, input.y, input.z, input.w);
}

float4x4 multiplyMatrix(float4x4 a, const float4x4 b)
{
    float4x4 c = CreateZeroMatrix();
    float* a2 = (float*) &a;
    float* b2 = (float*) &b;
    float* c2 = (float*) &c;
    for (unsigned j = 0; j < 16; j++)
    {
        unsigned i = j % 4;
        unsigned j4 = j & 12;
        c2[j] = 
            a2[j4 + 0] * b2[i + 0] + a2[j4 + 1] * b2[i + 4]
            + a2[j4 + 2] * b2[i + 8] + a2[j4 + 3] * b2[i + 12];
    }
    return c;
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

float4 quaternion_conjugation(float4 rotation)
{ 
    return (float4) { -rotation.x, -rotation.y, -rotation.z, rotation.w }; 
}

void float4_divide(float4 *input, float division)
{
    input->x /= division;
    input->y /= division;
    input->z /= division;
    input->w /= division;
}

/*float4 quaternion_reverse(float4 q)
{
    return (float4) { -q.x, -q.y, -q.z, -q.w };
}*/

float4 quaternion_inverse(float4 q)
{
    float sqr = sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
    float4 output;
    output = quaternion_conjugation(q);
    float4_divide(&output, sqr);
    return output;
}
            
float3 rotateVector(float4 rotation, float3 vertex3)
{
    // does this need conjugation(inverse(rot)) ?
    // Remove float4 use on vert
    float4 vertex = { vertex3.x, vertex3.y, vertex3.z, 0 };
    rotation = quaternion_inverse(rotation);
    float4 output = quaternion_rotate(quaternion_conjugation(rotation), quaternion_rotate(vertex, rotation));
    return (float3) { output.x, output.y, output.z };
}

float4x4 quaternion_to_matrix(float4 quat)
{
    float4x4 m = CreateIdentityMatrix(); // float4x4(float4(0, 0, 0, 0), float4(0, 0, 0, 0), float4(0, 0, 0, 0), float4(0, 0, 0, 0));

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

// float* multiplyMatrix(float* a, const float* b)
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