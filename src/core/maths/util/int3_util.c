float3 int3_to_float3(const int3 input) {
    return (float3) { input.x, input.y, input.z };
}

float3 byte3_to_float3(const byte3 input) {
    return (float3) { input.x, input.y, input.z };
}

// depreciated
float3 float3_from_int3(const int3 input) {
    return (float3) { input.x, input.y, input.z };
}

int3 find_closest_point(const int3* points, const int points_length, const int3 target) {
    if (points_length == 0) return int3_zero;
    int3 closest_point = points[0];
    float closest_distance = int3_distance(points[0], target); // 1000000;
    for (unsigned char i = 1; i < points_length; i++) {
        const float distance = int3_distance(points[i], target);
        if (distance < closest_distance) {
            closest_distance = distance;
            closest_point = points[i];
        }
    }
    return closest_point;
}
