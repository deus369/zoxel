// todo: use this
typedef struct {
    int_array_d *indicies;
    float3_array_d* vertices;
    float2_array_d* uvs;
    color_rgb_array_d* color_rgbs;
} mesh_uvs_build_data;

// finalize frees it apparently
/*void free_mesh_uvs_build_data(const mesh_uvs_build_data *data) {
    free(data->indicies);
    free(data->vertices);
    free(data->uvs);
    free(data->color_rgbs);
}*/
