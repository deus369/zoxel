float randf() {
    return (float)rand() / (float)RAND_MAX;
}

/*float randf(float max) {
    return (float) rand() / max;
}*/

float randf_range(float min, float max) {
    return min + (max - min) * randf();
}


static inline float3 float6_rand_range(const float6 hsvr) {
    return (float3) {
        randf_range(hsvr.x, hsvr.y),
        randf_range(hsvr.z, hsvr.w),
        randf_range(hsvr.u, hsvr.v)
    };
}