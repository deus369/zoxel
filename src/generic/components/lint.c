#define zoxc_lint(name) \
    zoxc(name, lint)

#define zoxd_lint(name)\
    zox_define_component(name)\
    add_to_entity_array_d(component_ids_lint, ecs_id(name));

#define zox_component_string_lint(component) \
    " li [%ld]", component->value

zox_base_type(lint)
