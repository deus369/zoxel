// #define zox_log_gpu_management
#define zox_pipelines_rendering EcsOnStore
#define zox_max_shaders 64
byte shaders_count = 0;
const GLchar* shader_verts[zox_max_shaders];
const GLchar* shader_frags[zox_max_shaders];