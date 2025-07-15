int3 find_closest_point(const int3* points, const int points_length, const int3 target) {
    if (points == NULL) {
        return int3_zero;
    }
    if (points_length == 0) {
        return int3_zero;
    }
    if (points_length == 1) {
        return points[0];
    }
    int3 closest_point = points[0];
    float closest_distance = int3_distance(points[0], target); // 1000000;
    for (byte i = 1; i < points_length; i++) {
        const float distance = int3_distance(points[i], target);
        if (distance < closest_distance) {
            closest_distance = distance;
            closest_point = points[i];
        }
    }
    return closest_point;
}