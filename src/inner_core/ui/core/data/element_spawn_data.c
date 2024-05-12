// data used when spawning any element
typedef struct {
    int2 position;
    int2 size;
    float2 anchor;
    unsigned char layer;
    unsigned char render_disabled;
    color fill_color;
} ElementSpawnData;
