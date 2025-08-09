// Define the ComputeShaderLink component
zoxc(ComputeShaderLink, uint);

// Destructor for ComputeShaderLink component
ECS_DTOR(ComputeShaderLink, ptr, {
    if (ptr->value) glDeleteShader(ptr->value);
})

// Function to generate a compute shader on gpu
uint gpu_spawn_compute_shader() {
    uint buffer = glCreateShader(GL_COMPUTE_SHADER);
    return buffer;
}

// Function to add a compute shader to a prefab
void prefab_add_compute_shader(ecs *world, const entity e) {
    if (!headless) zox_prefab_set(e, ComputeShaderLink, { 0 })
}

// Function to spawn and attach a compute shader to an entity
void spawn_compute_shader(ecs *world, const entity e) {
    if (!headless) zox_set(e, ComputeShaderLink, { gpu_spawn_compute_shader() })
}
