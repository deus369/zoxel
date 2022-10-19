#include <math.h> // for sqrt
#include <stdlib.h>
#include <stdio.h>

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

float* CreateZeroMatrix()
{
    float* identity = malloc(16 * 4);
    for (int i = 0; i < 16; i++)
    {
        identity[i] = 0;
    }
    return identity;
}

float* CreateIdentityMatrix()
{
    float* identity = CreateZeroMatrix();
    identity[0] = 1;
    identity[5] = 1;
    identity[10] = 1;
    identity[15] = 1;
    return identity;
}

void PrintMatrix(const float* matrix)
{
    printf("Matrix;\n  %f %f %f %f \n  %f %f %f %f \n %f %f %f %f  \n %f %f %f %f \n",
        matrix[0], matrix[1], matrix[2], matrix[3],
        matrix[4], matrix[5], matrix[6], matrix[7],
        matrix[8], matrix[9], matrix[10], matrix[11],
        matrix[12], matrix[13], matrix[14], matrix[15]);
}

float* multiplyMatrix(float* a, const float* b)
{
    float* c = malloc(16 * 4);
    for (unsigned j = 0; j < 16; j++)
    {
        unsigned i = j % 4;
        unsigned j4 = j & 12;  // j4 = j / 4 * 4;
        c[j] = 
            a[j4 + 0]*b[i + 0] + a[j4 + 1]*b[i + 4]
            + a[j4 + 2]*b[i + 8] + a[j4 + 3]*b[i + 12];
    }
    return c;
}

    /*int i, j;
    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 4; ++j)
        {
            c [i + j * 4]= a[i + 4 * j] + b[i + 4 * j];
        }
    }*/