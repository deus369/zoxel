// used for resource management
void MeshGPUDisposeSystem(ecs_iter_t *it) {
    zox_field_in(MeshGPULink, meshGPULinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(MeshGPULink, meshGPULinks, meshGPULink)
        if (meshGPULink->value.x != 0) glDeleteBuffers(1, &meshGPULink->value.x);
        if (meshGPULink->value.y != 0) glDeleteBuffers(1, &meshGPULink->value.y);
    }
} zox_declare_system(MeshGPUDisposeSystem)

void MeshUvsGPUDisposeSystem(ecs_iter_t *it) {
    zox_field_in(UvsGPULink, uvsGPULinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(UvsGPULink, uvsGPULinks, uvsGPULink)
        if (uvsGPULink->value != 0) glDeleteBuffers(1, &uvsGPULink->value);
    }
} zox_declare_system(MeshUvsGPUDisposeSystem)

void MeshColorsGPUDisposeSystem(ecs_iter_t *it) {
    zox_field_in(ColorsGPULink, colorsGPULinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(ColorsGPULink, colorsGPULinks, colorsGPULink)
        if (colorsGPULink->value != 0) glDeleteBuffers(1, &colorsGPULink->value);
    }
} zox_declare_system(MeshColorsGPUDisposeSystem)

void ShaderGPUDisposeSystem(ecs_iter_t *it) {
    zox_field_in(ShaderGPULink, shaderGPULinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(ShaderGPULink, shaderGPULinks, shaderGPULink)
        if (shaderGPULink->value.x != 0) glDeleteShader(shaderGPULink->value.x);
        if (shaderGPULink->value.y != 0) glDeleteShader(shaderGPULink->value.y);
    }
} zox_declare_system(ShaderGPUDisposeSystem)

void MaterialGPUDisposeSystem(ecs_iter_t *it) {
    zox_field_in(MaterialGPULink, materialGPULinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(MaterialGPULink, materialGPULinks, materialGPULink)
        if (materialGPULink->value != 0) glDeleteProgram(materialGPULink->value);
    }
} zox_declare_system(MaterialGPUDisposeSystem)

void TextureGPUDisposeSystem(ecs_iter_t *it) {
    zox_field_in(TextureGPULink, textureGPULinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(TextureGPULink, textureGPULinks, textureGPULink)
        if (textureGPULink->value != 0) glDeleteTextures(1, &textureGPULink->value);
    }
} zox_declare_system(TextureGPUDisposeSystem)

