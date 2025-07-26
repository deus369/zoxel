zox_declare_tag(Character3)
zox_declare_tag(SaveCharacter)
zox_component_byte(CharactersChanceMax)
zox_component_byte(Character3Type)
zox_component(CharacterSaveHash, ulong)
zox_component_entity(Character3Link)
zox_component_entity(Character3PrefabLink)

void define_components_characters3(ecs_world_t* world) {
    zox_define_tag(Character3)
    zox_define_tag(SaveCharacter)
    zox_define_component_byte(CharactersChanceMax)
    zox_define_component_byte(Character3Type)
    zox_define_component(CharacterSaveHash)
    zox_define_component_entity(Character3Link)
    zox_define_component_entity(Character3PrefabLink)
}