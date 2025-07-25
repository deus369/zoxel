zox_declare_user_data(Skill)
zox_declare_tag(Melee)
zox_declare_tag(Aura)
zox_declare_tag(Poison)
zox_component_byte(SkillActive)
zox_component_float(SkillDamage)
zox_component_float(SkillDamageMax)
zox_component_float(SkillRange)
zox_component_float(SkillCost)
zox_component_entity(SkillResourceLink)

void define_components_skills(ecs_world_t *world) {
    zox_define_tag(Melee)
    zox_define_tag(Aura)
    zox_define_tag(Poison)
    zox_define_user_data(Skill)
    zox_define_component_float(SkillDamage)
    zox_define_component_float(SkillDamageMax)
    zox_define_component_float(SkillRange)
    zox_define_component_float(SkillCost)
    zox_define_component_byte(SkillActive)
    zox_define_component_entity(SkillResourceLink)
}