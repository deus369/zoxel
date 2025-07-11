// todo: load in .vert and .frag files as strings instead
// later we can pack more information into bone_index uint

// highp mat4 bone = (vertex_position.y < 0.12) ? bone_matrix[0] : bone_matrix[1];
// lowp vec3 original_bone_position = (vertex_position.y < 0.12) ? vec3(0, 0, 0) : vec3(0, 0.18, -0.03f);
// note; this does update by delta... but now its not transforming at all!
// oh i get it, its where the bone initially sets in the mesh, and transform will be done from there
/*
 * vec4 skinned_position = vec4(0.0);
 * for (int i = 0; i < num_bones; ++i) {
 *    skinned_position += bone_weights[i] * (bone_matrices[i] * vec4(vertex_position, 1));
 * }
 * gl_Position = camera_matrix * skinned_position;
 * */
