//! A basic x2 building block.
typedef struct {
    float4 x;
    float4 y;
    float4 z;
    float4 w;
} float4x4;

float4x4 float4x4_zero() {
    float4x4 identity; // = malloc(16 * 4);
    float* identity2 = (float*) &identity;
    for (int i = 0; i < 16; i++) {
        identity2[i] = 0;
    }
    return identity;
}

float4x4 float4x4_identity() {
    float4x4 identity = float4x4_zero();
    identity.x.x = 1;
    identity.y.y = 1;
    identity.z.z = 1;
    identity.w.w = 1;
    return identity;
}

float4x4 float4x4_multiply(const float4x4 a, const float4x4 b) {
    float4x4 c = float4x4_zero();
    float* a2 = (float*) &a;
    float* b2 = (float*) &b;
    float* c2 = (float*) &c;
    for (unsigned j = 0; j < 16; j++) {
        unsigned i = j % 4;
        unsigned j4 = j & 12;
        c2[j] = a2[j4 + 0] * b2[i + 0] + a2[j4 + 1] * b2[i + 4]
            + a2[j4 + 2] * b2[i + 8] + a2[j4 + 3] * b2[i + 12];
    }
    return c;
}

void float4x4_print(const float4x4 matrix) {
    const float* matrix2 = (float*) &matrix;
    zoxel_log("Matrix;\n\t[%f\t%f\t%f\t%f]\n\t[%f\t%f\t%f\t%f]\n\t[%f\t%f\t%f\t%f]\n\t[%f\t%f\t%f\t%f]\n",
         matrix2[0], matrix2[1], matrix2[2], matrix2[3],
         matrix2[4], matrix2[5], matrix2[6], matrix2[7],
         matrix2[8], matrix2[9], matrix2[10], matrix2[11],
         matrix2[12], matrix2[13], matrix2[14], matrix2[15]);
}
