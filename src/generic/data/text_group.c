typedef struct {
    const char* text;
} text_group;

typedef struct {
    char* text;
} text_group_dynamic;

zoxel_dynamic_array(text_group)
zoxel_dynamic_array(text_group_dynamic)
