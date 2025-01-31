// todo: add transforms to 2D uis

//! Links to locations inside a base material->
typedef struct {
    GLint vertex_position;
    GLint vertex_uv;
    GLuint camera_matrix;
    GLuint transform_matrix;
    GLuint texture;
} MaterialAttributesRenderTexture;
zox_custom_component(MaterialAttributesRenderTexture)

MaterialAttributesRenderTexture create_MaterialAttributesRenderTexture(const GLuint material) {
    return (MaterialAttributesRenderTexture) {
        .vertex_position = glGetAttribLocation(material, "vertex_position"),
        .vertex_uv = glGetAttribLocation(material, "vertex_uv"),
        .camera_matrix = glGetUniformLocation(material, "camera_matrix"),
        .transform_matrix = glGetUniformLocation(material, "transform_matrix"),
        .texture = glGetUniformLocation(material, "texture") };
}

const GLchar* shader_source_vert_render_texture = "\
#version 320 es\n\
uniform highp mat4 camera_matrix;\
uniform highp mat4 transform_matrix;\
layout(location=0) in lowp vec2 vertex_position;\
layout(location=1) in lowp vec2 vertex_uv;\
out lowp vec2 uv;\
\
void main() {\
    gl_Position = camera_matrix * transform_matrix * vec4(vertex_position, 0.0, 1.0);\
    uv = vertex_uv;\
}";

const GLchar* shader_source_frag_render_texture = "\
#version 320 es\n\
uniform sampler2D tex;\
in lowp vec2 uv;\
out lowp vec4 color;\
\
lowp float random(lowp vec2 st) {\
    return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453123);\
}\
\
void main() {\
    color = texture(tex, uv);\
    lowp float noise = random(uv);\
    lowp float vignette = smoothstep(0.8, 0.2, distance(uv, vec2(0.5)));\
    color.rgb *= vignette;\
    color = mix(color, vec4(noise, noise, noise, 1.0), 0.1);\
}";

// color = vec4(1, 0, 0, 1);
// highp float depth = texture(tex, uv).r;
// color = vec4(vec3(depth), 1.0);
