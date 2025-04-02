void render_entity_3D(float3 position, float4 rotation, float scale1D, float brightness) {
    /*glUniform3f(material3D.position, position.x, position.y, position.z);
    glUniform4f(material3D.rotation, rotation.x, rotation.y, rotation.z, rotation.w);
    glUniform1f(material3D.scale, scale1D);
    glUniform1f(material3D.brightness, brightness);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    opengl_render(6);*/
}

void InstanceRender3DSystem(ecs_iter_t *it) {
    /*zox_log("render instances %i\n", it->count);
    zox_field_in(Position3D, position3Ds, 2)
    zox_field_in(Rotation3D, rotation3Ds, 3)
    zox_field_in(Scale1D, scale1Ds, 4)
    zox_field_in(Brightness, brightnesses, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Position3D, position3Ds, position3D)
        zox_field_i(Rotation3D, rotation3Ds, rotation3D)
        zox_field_i(Scale1D, scale1Ds, scale1D)
        zox_field_i(Brightness, brightnesses, brightness)
        render_entity_3D(position3D->value, rotation3D->value, scale1D->value, brightness->value);
    }*/
} zox_declare_system(InstanceRender3DSystem)
