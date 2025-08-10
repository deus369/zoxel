// small helper prints
static void print_plane(const char *tag, int i, const plane p) {
    zox_log("%s plane %d: n=(%.6f %.6f %.6f) d=%.6f",
        tag, i,
        p.normal.x, p.normal.y, p.normal.z,
        p.distance);
}
