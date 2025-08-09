zox_tag(SphereCollider);
zoxc_byte(Collision);       // a flag for sides collided with
zoxc_byte(Grounded); // use for friction - todo: use bit operations to check what sides cause friction and apply like that
zoxc_float3(CollisionDistance);
zoxc_float(BasicCollider);
zoxc_float(SphereRadius);
zoxc_function(OverlapEvent, void, ecs*, entity, entity);

void define_components_collisions3(ecs* world) {
    zox_define_tag(SphereCollider);
    zox_define_component_byte(Collision);
    zox_define_component_byte(Grounded);
    zox_define_component_float(BasicCollider);
    zox_define_component_float(SphereRadius);
    zox_define_component_float3(CollisionDistance);
    zox_define_component(OverlapEvent);
}