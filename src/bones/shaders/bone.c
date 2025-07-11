#include "bone.vert.c"
#include "bone.frag.c"

typedef struct {
    GLint vertex_position;
    GLint vertex_color;
    GLint bone_index;
    GLuint transform_matrix;
    GLuint camera_matrix;
    GLuint bone_matrix;
    GLuint bone_positions;
    GLuint brightness;
    GLuint fog_data;
} MaterialBone;
zox_custom_component(MaterialBone)

MaterialBone create_MaterialBone(const GLuint material) {
    return (MaterialBone) {
        glGetAttribLocation(material, "vertex_position"),
        glGetAttribLocation(material, "vertex_color"),
        glGetAttribLocation(material, "bone_index"),
        glGetUniformLocation(material, "transform_matrix"),
        glGetUniformLocation(material, "camera_matrix"),
        glGetUniformLocation(material, "bone_matrix"),
        glGetUniformLocation(material, "bone_positions"),
        glGetUniformLocation(material, "brightness"),
        glGetUniformLocation(material, "fog_data")
    };
}

ecs_entity_t spawn_shader_bone(ecs_world_t *world) {
    const byte shader_index = get_new_shader_source_index();
    char* vert = get_shader_source(world, "bone.vert");
    char* frag = get_shader_source(world, "bone.frag");
    shader_verts[shader_index] = vert;
    shader_frags[shader_index] = frag;
    const ecs_entity_t e = spawn_shader(world, shader_index);
    zox_name("shader_bone")
    return e;
}

ecs_entity_t shader_bone;
ecs_entity_t material_bone;

ecs_entity_t spawn_material_bone(ecs_world_t *world) {
    const ecs_entity_t shader = spawn_shader_bone(world);
    if (!shader) {
        zox_log(" ! failed spawning bone shader")
        return 0;
    }
    shader_bone = shader;
    GLuint material; // link to gpu
    const ecs_entity_t e = spawn_material(world, shader, &material);
    if (!e) {
        zox_log(" ! failed spawning bone material")
        return 0;
    }
    zox_set(e, ShaderLink, { shader })
    const MaterialBone attributes = create_MaterialBone(material);
    zox_set_data(e, MaterialBone, attributes)
    material_bone = e;
    return e;
}
