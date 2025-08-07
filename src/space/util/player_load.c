// NOTE: WE NOW NEED TO SPAWN TERRAIN CHUNK HERE IF IT DOESN"T EXIST!
//      - streaming breaks if all chunks die..

entity game_start_player_load(
    ecs *world,
    const entity player
) {
    const entity model = string_hashmap_get(files_hashmap_voxes, new_string_data(player_vox_model));
    if (!model) {
        zox_log_error("[tall_cube] not found on player")
        return 0;
    }
    const entity camera = zox_get_value(player, CameraLink)
    if (!camera) {
        return 0;
    }
    const entity game = zox_get_value(player, GameLink)
    if (!game) {
        return 0;
    }
    const entity realm = zox_get_value(game, RealmLink)
    if (!realm) {
        return 0;
    }
    const entity terrain = zox_get_value(realm, TerrainLink)
    if (!terrain) {
        return 0;
    }
    TerrainPlace spawn_place;
    spawn_place.chunk = 0;
    load_character_p(
        &spawn_place.position,
        &spawn_place.euler,
        &spawn_place.rotation);

    // if character not in chunk, spawn one here
    const byte depth = terrain_depth;
    const int3 chunk_dimensions = int3_single(powers_of_two[depth]);
    const int3 chunk_position = real_position_to_chunk_position(spawn_place.position, chunk_dimensions, depth);
    zox_mut_begin(terrain, ChunkLinks, chunkLinks)
    spawn_place.chunk = int3_hashmap_get(chunkLinks->value, chunk_position);
    // check if exists first
    byte spawned_first_chunk = 0;
    if (!zox_valid(spawn_place.chunk)) {
        spawn_place.chunk = spawn_chunk_terrain(world,
            prefab_chunk_height,
            terrain,
            chunk_position,
            chunk_position,
            real_chunk_scale);
        spawned_first_chunk = 1;
        if (zox_valid(spawn_place.chunk)) {
            int3_hashmap_add(chunkLinks->value,
                chunk_position,
                spawn_place.chunk);
            zox_mut_end(terrain, ChunkLinks)
            // zox_log("+ spawning chunk for player character loading [%ix%ix%i]:%lu", chunk_position.x, chunk_position.y, chunk_position.z, spawn_place.chunk)
        } else {
            zox_log_error("failed to spawn chunk [%ix%ix%i]:%lu", chunk_position.x, chunk_position.y, chunk_position.z, spawn_place.chunk)
        }
    } else {
        zox_log("+ player character placed into [%ix%ix%i]", chunk_position.x, chunk_position.y, chunk_position.z)
    }
    spawn_character3D_data spawn_data = {
        .model = model,
        .terrain = terrain,
        .terrain_chunk = spawn_place.chunk,
        .chunk_position = chunk_position,
        .position = spawn_place.position,
        .rotation = spawn_place.rotation,
        .euler = spawn_place.euler,
        .player = player,
    };
    zox_set(camera, Position3D, { spawn_place.position }) // reposition camera too
    const entity e = spawn_character3_player(world, spawn_data);
    // assuming we just spawned it
    if (spawned_first_chunk) {
        EntityLinks entities = (EntityLinks) { };
        add_to_EntityLinks(&entities, e);
        zox_set_ptr(spawn_place.chunk, EntityLinks, entities);
    } else {
        if (zox_valid(spawn_place.chunk)) {
            zox_mut_begin(spawn_place.chunk, EntityLinks, entityLinks)
            if (add_to_EntityLinks(entityLinks, e)) {
                zox_mut_end(spawn_place.chunk, EntityLinks)
            }
        }
    }

    delay_event(world, &load_player_e, player, 0.5f);
    return e;
}