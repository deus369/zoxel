// render distances
byte vox_lod_near = 1;
byte terrain_lod_near = 3;      // also character far
byte terrain_lod_far = 8;       // 1 | 2 | 4 | 8 | 16
byte render_distance_y = 2;     // vertical
// Sub Divisions
byte terrain_depth = 4;         // 4 | 5
byte block_vox_depth = 5;       // 4 | 5
byte character_depth = 5;
// options
byte terrain_lod_far_buffer = 2;    // buffer the near to far - adds a minimum low lods
byte terrain_lod_near_min = 1;
byte terrain_lod_near_max = 5;
byte terrain_lod_far_max = 12;  // options, min + percentage*max

extern int get_characters_count(ecs_world_t *world);
extern int count_entities_npc(ecs_world_t *world);

uint debug_label_lods(ecs_world_t *world,
    const ecs_entity_t player,
    char *buffer,
    const uint size, uint index)
{
    index += snprintf(buffer + index, size - index, "### Lod Settings ###\n");
    index += snprintf(buffer + index, size - index, " - vox near [%i]\n", vox_lod_near);
    index += snprintf(buffer + index, size - index, " - terrain near [%i]\n", terrain_lod_near);
    index += snprintf(buffer + index, size - index, " - terrain far [%i]]\n", terrain_lod_far);
    index += snprintf(buffer + index, size - index, " - terrain vertical [%i]\n", render_distance_y);
    index += snprintf(buffer + index, size - index, " - depths [%i:%i:%i]\n", terrain_depth, block_vox_depth, character_depth);
    index += snprintf(buffer + index, size - index, " - npcs [%i]\n", count_entities_npc(world));

    return index;
}