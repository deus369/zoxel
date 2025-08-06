void crosshair_set_type(ecs_world_t* world, ecs_entity_t e, byte new) {
    if (!zox_valid(e) || !zox_has(e, HitType)) {
        return;
    }
    zox_geter_value(e, HitType, byte, old)
    if (old == new) {
        return;
    }
    color c;
    if (new == ray_hit_type_none) {
        c = crosshair_air;
    } else if (new == ray_hit_type_terrain) {
        c = crosshair_terrain;
    } else if (new == ray_hit_type_block_vox) {
        c = crosshair_terrain;
    } else if (new == ray_hit_type_character) {
        c = crosshair_target;
    } else {
        c = crosshair_air;
    }
    // zox_log("+ setting crosshair type [%i]", new)
    zox_set(local_crosshair, HitType, { new })
    zox_set(local_crosshair, OutlineColor, { c })
    zox_set(local_crosshair, GenerateTexture, { zox_generate_texture_trigger })
}