// used for resource management
void MeshGPUDisposeSystem(ecs_iter_t *it) {
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 1);
    for (int i = 0; i < it->count; i++) {
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        if (meshGPULink->value.x != 0) glDeleteBuffers(1, &meshGPULink->value.x);
        if (meshGPULink->value.y != 0) glDeleteBuffers(1, &meshGPULink->value.y);
    }
} zox_declare_system(MeshGPUDisposeSystem)

void MeshUvsGPUDisposeSystem(ecs_iter_t *it) {
    const UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 1);
    for (int i = 0; i < it->count; i++) {
        const UvsGPULink *uvsGPULink = &uvsGPULinks[i];
        if (uvsGPULink->value != 0) glDeleteBuffers(1, &uvsGPULink->value);
    }
} zox_declare_system(MeshUvsGPUDisposeSystem)

void MeshColorsGPUDisposeSystem(ecs_iter_t *it) {
    const ColorsGPULink *colorsGPULinks = ecs_field(it, ColorsGPULink, 1);
    for (int i = 0; i < it->count; i++) {
        const ColorsGPULink *colorsGPULink = &colorsGPULinks[i];
        if (colorsGPULink->value != 0) glDeleteBuffers(1, &colorsGPULink->value);
    }
} zox_declare_system(MeshColorsGPUDisposeSystem)

void ShaderGPUDisposeSystem(ecs_iter_t *it) {
    const ShaderGPULink *shaderGPULinks = ecs_field(it, ShaderGPULink, 1);
    for (int i = 0; i < it->count; i++) {
        const ShaderGPULink *shaderGPULink = &shaderGPULinks[i];
        if (shaderGPULink->value.x != 0) glDeleteShader(shaderGPULink->value.x);
        if (shaderGPULink->value.y != 0) glDeleteShader(shaderGPULink->value.y);
    }
} zox_declare_system(ShaderGPUDisposeSystem)

void MaterialGPUDisposeSystem(ecs_iter_t *it) {
    const MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 1);
    for (int i = 0; i < it->count; i++) {
        const MaterialGPULink *materialGPULink = &materialGPULinks[i];
        if (materialGPULink->value != 0) glDeleteProgram(materialGPULink->value);
    }
} zox_declare_system(MaterialGPUDisposeSystem)