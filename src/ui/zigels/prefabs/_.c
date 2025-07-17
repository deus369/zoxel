ecs_entity_t prefab_zigel;
ecs_entity_t zox_font_style_monocraft;
#include "font.c"
#include "font_style.c"
#include "zigel.c"
#include "ttf_font.c"
ecs_entity_t prefab_font_style;
ecs_entity_t prefab_font;
ecs_entity_t zox_font_style_default;

ecs_entity_t get_font_style_using() {
    if (zox_font_style_monocraft) return zox_font_style_monocraft;
    return zox_font_style_default;
}

int get_zigels_count(ecs_world_t *world) {
    return zox_count_types(Zigel)
}

void spawn_prefabs_zigels(ecs_world_t *world) {
    prefab_font = spawn_font_prefab(world);
    prefab_font_style = spawn_prefab_font_style(world, prefab_font);
    prefab_zigel = spawn_zigel_prefab(world, prefab_element_basic);
}