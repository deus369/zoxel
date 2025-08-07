#define zox_slider_type_float 0
#define zox_slider_type_int 1

typedef struct {
    const char* name;
    byte type;
    entity prefab_handle;
    float value;
    float2 bounds;
    byte handle_width;
} SpawnSliderData;
