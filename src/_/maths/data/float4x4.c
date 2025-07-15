// remember: matrix in column-major order, each float4 is a column

#define float4x4_zero { float4_zero, float4_zero, float4_zero, float4_zero }

const float4x4 float4x4_identity_ = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };

/*
const float4x4 float4x4_zero_ = { float4_zero, float4_zero, float4_zero, float4_zero };
float4x4 float4x4_zero() {
    return float4x4_zero_;
}*/

static inline float4x4 float4x4_identity() {
    return float4x4_identity_;
}

static inline float4x4 float4x4_multiply(const float4x4 a, const float4x4 b) {
    float4x4 c = float4x4_zero;
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

static inline float3 float4x4_forward(const float4x4 matrix) {
    return (float3) { matrix.z.x, matrix.z.y, matrix.z.z };
}

void log_float4x4(char *label, const float4x4 matrix) {
    const float* matrix2 = (float*) &matrix;
    zox_log(" [%s];\n\t[%f\t%f\t%f\t%f]\n\t[%f\t%f\t%f\t%f]\n\t[%f\t%f\t%f\t%f]\n\t[%f\t%f\t%f\t%f]\n",
        label,
        matrix2[0], matrix2[1], matrix2[2], matrix2[3],
        matrix2[4], matrix2[5], matrix2[6], matrix2[7],
        matrix2[8], matrix2[9], matrix2[10], matrix2[11],
        matrix2[12], matrix2[13], matrix2[14], matrix2[15]);
}