extern ecs_entity_t spawn_pickup_basic(ecs_world_t*, const float3);
extern ecs_entity_t spawn_pickup_block(ecs_world_t*, const float3, const ecs_entity_t);

// we should drop from actions too!
void ItemDropSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(Dead)
    zox_sys_in(Position3D)
    zox_sys_in(ItemLinks)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Dead, dead)
        zox_sys_i(Position3D, position)
        zox_sys_i(ItemLinks, items)
        // proces if i die
        if (dead->value != zox_dirty_active) {
            continue;
        }
        // drop item
        // zox_log("character dropping [%i] items", items->length)
        for (int j = 0; j < items->length; j++) {
            const ecs_entity_t item = items->value[j];
            if (zox_valid(item)) {
                zox_get_prefab(item, meta)
                ecs_entity_t pickup;
                if (zox_has(item, BlockLink)) {
                    zox_geter_value(item, BlockLink, ecs_entity_t, block)
                    pickup = spawn_pickup_block(world, position->value, block);
                } else {
                    pickup = spawn_pickup_basic(world, position->value);
                }
                // zox_log("  - [%s] - m [%s]", zox_get_name(item), zox_get_name(meta))
                zox_set(pickup, ItemLink, { meta })
            }
        }
        // destroy voxel sound
        // spawn_sound_generated(world, prefab_sound_generated, instrument_piano, note_frequencies[24 + rand() % 6], 0.4, 1.2f * get_volume_sfx());
    }
} zox_declare_system(ItemDropSystem)
