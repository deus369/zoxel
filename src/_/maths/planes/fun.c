// more fun / unused for now

static void normalize_plane(plane *p) {
    double nx = p->normal.x;
    double ny = p->normal.y;
    double nz = p->normal.z;
    double invLen = 1.0 / sqrt(nx*nx + ny*ny + nz*nz);
    p->normal.x = (float)(nx * invLen);
    p->normal.y = (float)(ny * invLen);
    p->normal.z = (float)(nz * invLen);
    p->distance = (float)(p->distance * invLen);
}