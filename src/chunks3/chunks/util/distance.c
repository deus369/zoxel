// returns simple camera distance for chunks
static inline byte get_camera_chunk_distance(const int3 camera_position, const int3 chunk_position) {
    return (byte) int3_max(chunk_position, camera_position);
}

static inline byte get_camera_chunk_distance_xz(const int3 camera_position, const int3 chunk_position) {
    return (byte) int3_max_xz((int3) { chunk_position.x, 0, chunk_position.z }, camera_position);
}