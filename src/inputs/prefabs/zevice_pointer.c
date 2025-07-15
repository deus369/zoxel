ecs_entity_t spawn_prefab_zevice_pointer(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("zevice_pointer")
    zox_add_tag(e, Zevice)
    zox_prefab_set(e, ID, { 0 })
    zox_prefab_set(e, ZeviceDisabled, { 0 })
    zox_prefab_set(e, ZevicePointer, { 0 })
    zox_prefab_set(e, ZevicePointerOld, { 0 })
    zox_prefab_set(e, ZevicePointerPosition, { int2_zero })
    zox_prefab_set(e, ZevicePointerDelta, { int2_zero })
    zox_prefab_set(e, DeviceButtonType, { 0 })
    zox_prefab_set(e, RealButtonIndex, { 0 })
    zox_prefab_set(e, DeviceLink, { 0 })
    return e;
}

ecs_entity_t spawn_zevice_pointer(ecs_world_t *world, const ecs_entity_t device, byte type, byte index) {
    zox_instance(prefab_zevice_pointer)
    zox_name("zevice_pointer")
    zox_set(e, DeviceLink, { device })
    zox_set(e, DeviceButtonType, { type })
    zox_set(e, RealButtonIndex, { index })
    return e;
}