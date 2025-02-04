// new: , float4x4_multiply_double4, double3_divide_double
// for higher precision maths

#define double3_zero (double3) { 0, 0, 0 }

double double_abs(const double input) {
    if (input < 0) return -input;
    else return input;
}

double3 double3_lerp(const double3 a, const double3 b, const double t) {
    return (double3) { a.x + t * (b.x - a.x), a.y + t * (b.y - a.y), a.z + t * (b.z - a.z) };
}

double3 double3_add(const double3 a, const double3 b) {
    return (double3) { a.x + b.x, a.y + b.y, a.z + b.z };
}

double3 double3_sub(const double3 a, const double3 b) {
    return (double3) { a.x - b.x, a.y - b.y, a.z - b.z };
}

double3 double3_mul(const double3 a, const double m) {
    return (double3) { a.x * m, a.y * m, a.z * m };
}

double3 double3_divide_double(const double3 input, const double div) {
    return (double3) { input.x / div, input.y / div, input.z / div };
}

double3 double3_normalize(const double3 input) {
    double length = sqrt(input.x * input.x + input.y * input.y + input.z * input.z);
    if (double_abs(length) <= 0.00001) return input;
    return double3_divide_double(input, length);
}

float3 double3_to_float3(const double3 value) {
    return (float3) { (float) value.x, (float) value.y, (float) value.z };
}

double3 float3_to_double3(const float3 value) {
    return (double3) { (double) value.x, (double) value.y, (double) value.z };
}

double4 double4_from_double3(const double3 value, const double w) {
    return (double4) { value.x, value.y, value.z, w };
}

double4 float4x4_multiply_double4(const float4x4 mat, const double4 point) {
    double4 result;
    result.x = mat.x.x * point.x + mat.y.x * point.y + mat.z.x * point.z + mat.w.x * point.w;
    result.y = mat.x.y * point.x + mat.y.y * point.y + mat.z.y * point.z + mat.w.y * point.w;
    result.z = mat.x.z * point.x + mat.y.z * point.y + mat.z.z * point.z + mat.w.z * point.w;
    result.w = mat.x.w * point.x + mat.y.w * point.y + mat.z.w * point.z + mat.w.w * point.w;
    return result;
}

double3 double3_cross(const double3 a, const double3 b) {
    return (double3) { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
}

double double3_dot(const double3 a, const double3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double3 adjust_point_along_normal(const double3 a, const double3 b, const float distance) {
    double3 normal = double3_normalize(double3_sub(a, b));
    return double3_add(a, double3_mul(normal, distance));
}
