static inline void zox_gpu_float(uint index, const float value) {
    glUniform1f(index, value);
}

static inline void zox_gpu_float2(uint index, const float2 value) {
    glUniform2f(index, value.x, value.y);
}

static inline void zox_gpu_float3(uint index, const float3 value) {
    glUniform3f(index, value.x, value.y, value.z);
}

static inline void zox_gpu_float4(uint index, const float4 value) {
    glUniform4f(index, value.x, value.y, value.z, value.w);
}

static inline void zox_gpu_float4x4(uint index, const float4x4 value) {
    glUniformMatrix4fv(index, 1, GL_FALSE, (float*) &value);
}

static inline void zox_gpu_float4x4_array(uint index, const float4x4* values, int count) {
    glUniformMatrix4fv(index, count, GL_FALSE, (float*) values);
}

static inline void zox_gpu_float3_array(uint index, const float3* values, int count) {
    glUniform3fv(index, count, (const GLfloat*) values);
}