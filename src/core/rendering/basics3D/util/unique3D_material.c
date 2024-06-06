void set_basic_vert_layout(const Material3D *attributes) {
    // Material3D material3D = spawn_material3D_properties(material);
    glEnableVertexAttribArray(attributes->vertex_position);
    glVertexAttribPointer(attributes->vertex_position, 3, GL_FLOAT, GL_FALSE, 4 * 3, 0);
}
