#define zoxc_text(T) \
    zoxc_arrayd(T, byte)

#define zoxd_text(T)\
    zox_define_memory_component(T)\
    add_to_entity_array_d(component_ids_text, ecs_id(T));

extern char* convert_zext_to_text(const byte *zext, byte length);

#define zox_component_string_text(c) \
    " [%s]", convert_zext_to_text(c->value.value, c->value.length)

zox_base_type(text)
