// zox_declare_tag(Player3D)
zox_declare_tag(Character3Player)
zox_component_float3(Movement3)

void define_components_controllers3D(ecs_world_t *world) {
    // zox_define_tag(Player3D)
    zox_define_tag(Character3Player)
    zox_define_component_float3(Movement3)
}