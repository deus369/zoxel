ecs_entity_t spawn_prefab_character3(ecs_world_t *world,
    const ecs_entity_t prefab)
{
    if (!prefab) {
        return 0;
    }
    zox_prefab_child(prefab)
    zox_prefab_name("character3")
    zox_add_tag(e, Character3)
    // generation
    zox_prefab_set(prefab, Seed, { 999 })
    // name
    zox_prefab_add(e, ZoxName)
    // rendering
    //zox_set(e, RenderDisabled, { 0 })
    // constraints
    zox_prefab_set(e, Position3DBounds, { float6_zero })
    // In Terrain
    zox_add_tag(e, LinkChunk)
    zox_prefab_set(e, VoxLink, { 0 })
    zox_prefab_set(e, ChunkLink, { 0 })
    zox_prefab_set(e, ChunkPosition, { int3_chaos })
    zox_prefab_set(e, VoxelPosition, { int3_zero })
    // Vox
    zox_prefab_set(e, CloneVox, { 0 })
    zox_prefab_set(e, CloneVoxLink, { 0 })
    zox_prefab_set(e, ChunkLod, { 255 })
    // animation
    zox_prefab_set(e, AnimationState, { zox_animation_idle })
    zox_prefab_set(e, AnimationStart, { 0 })
    // hierarchy
    zox_prefab_add(e, Children)         // for bones, particles, etc (transforms)
    zox_prefab_add(e, ElementLinks)     // uis
    // physics3
    // physics -- too big atm to refactor
    zox_add_tag(e, Frictioned)
    zox_prefab_set(e, LastPosition3D, { float3_zero })
    zox_prefab_set(e, LastUnstuck3, { float3_zero })
    zox_prefab_set(e, InitializePhysics3D, { 0 })
    zox_prefab_set(e, Velocity3D, { float3_zero })
    zox_prefab_set(e, Acceleration3D, { float3_zero })
    zox_prefab_set(e, Omega3D, { float3_zero })
    zox_prefab_set(e, Alpha3D, { float3_zero })
    zox_prefab_set(e, Gravity3D, { zox_default_gravity })
    zox_prefab_set(e, DisableGravity, { 0 })
    zox_prefab_set(e, Bounds3D, { (float3) { 0.25f, 0.5f, 0.25f } })
    zox_prefab_set(e, DisableMovement, { 0 })
    zox_prefab_set(e, Grounded, { 0 })
    zox_prefab_set(e, CanJump, { 0 })
    zox_prefab_set(e, Jump, { 0 })
    zox_prefab_set(e, Collision, { 0 })
    zox_prefab_set(e, CollisionDistance, { float3_zero })
    // Debug
    prefab_add_cube_lines(world, e, color_white, 0);
    return e;
}