typedef struct {
    int x;
    int y;
    int z;
    int w;
} int4;

#define int4_zero (int4) { 0, 0, 0, 0 }

int2 int4_xy(const int4 value) {
    return (int2) { value.x, value.y };
}

int2 int4_zw(const int4 value) {
    return (int2) { value.z, value.w };
}

// used for lines
void int4_add_int2(int4 *value, const int2 add) {
    value->x += add.x;
    value->y += add.y;
    value->z += add.x;
    value->w += add.y;
}
