zox_tag(StatState);
zox_tag(StatRegen);
zox_tag(StatAttribute);
zox_tag(StatLevel);
zoxc_float(StatValue);
zoxc_float(StatValueMax);
zoxc_float(ExperienceValue);
zoxc_float(ExperienceMax);
zoxc_entities(DotLinks)
zoxc_userdata(Stat);
zoxf_user_prefabs(Stat, stat, "stat")
// special stats
zox_tag(HealthStat);
zox_tag(StatSoul);

void define_components_stats(ecs_world_t *world) {
    zox_define_tag(StatState);
    zox_define_tag(StatRegen);
    zox_define_tag(StatAttribute);
    zox_define_tag(StatLevel);
    zoxd_userdata(Stat);
    zox_define_component_float(StatValue);
    zox_define_component_float(StatValueMax);
    zox_define_component_float(ExperienceValue);
    zox_define_component_float(ExperienceMax);
    zox_define_entities_component(DotLinks);
    // special stats
    zox_define_tag(HealthStat);
    zox_define_tag(StatSoul);
}