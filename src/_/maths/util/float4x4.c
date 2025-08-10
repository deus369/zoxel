/*static inline float4x4 float4x4_identity {
    return float4x4_identity_;
}*/

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


float4x4 float4x4_inverse_safe(const float4x4 m) {
    float4x4 inv_out = float4x4_identity;
    double a[4][4];
    double inv[4][4];

    // Convert column-major float4x4 -> row-major double a[r][c]
    const float *mf = (const float*)&m;
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            // element at row r, col c is mf[c*4 + r] (column-major storage)
            a[r][c] = (double)mf[c*4 + r];
            inv[r][c] = (r == c) ? 1.0 : 0.0;
        }
    }

    // Gauss-Jordan elimination with partial pivoting (row-major)
    for (int i = 0; i < 4; ++i) {
        // find pivot row
        int pivot = i;
        double maxv = fabs(a[i][i]);
        for (int r = i + 1; r < 4; ++r) {
            double v = fabs(a[r][i]);
            if (v > maxv) { maxv = v; pivot = r; }
        }

        // singular (or nearly)
        if (maxv < 1e-12) {
            return float4x4_identity;
        }

        // swap rows i and pivot if needed
        if (pivot != i) {
            for (int c = 0; c < 4; ++c) {
                double tmp = a[i][c]; a[i][c] = a[pivot][c]; a[pivot][c] = tmp;
                tmp = inv[i][c]; inv[i][c] = inv[pivot][c]; inv[pivot][c] = tmp;
            }
        }

        // normalize pivot row
        double piv = a[i][i];
        double pivinv = 1.0 / piv;
        for (int c = 0; c < 4; ++c) {
            a[i][c] *= pivinv;
            inv[i][c] *= pivinv;
        }

        // eliminate other rows
        for (int r = 0; r < 4; ++r) {
            if (r == i) continue;
            double factor = a[r][i];
            if (factor == 0.0) continue;
            for (int c = 0; c < 4; ++c) {
                a[r][c] -= factor * a[i][c];
                inv[r][c] -= factor * inv[i][c];
            }
        }
    }

    // Convert row-major double inv[r][c] -> column-major float4x4 bytes
    float *of = (float*)&inv_out;
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            // store back as column-major: of[c*4 + r]
            of[c*4 + r] = (float)inv[r][c];
        }
    }

    return inv_out;
}