float randf() {
    return (float)rand() / (float)RAND_MAX;
}

/*float randf(float max) {
    return (float) rand() / max;
}*/

float randf_range(float min, float max) {
    return min + (max - min) * randf();
}