unsigned char* convert_string_to_zext(const char* text) {
    if (!text) return NULL;
    const unsigned char text_length = strlen(text);
    unsigned char *zext = malloc(text_length);
    for (unsigned char i = 0; i < text_length; i++) zext[i] = convert_ascii(text[i]);
    return zext;
}

unsigned char* convert_text_to_zext(const char* text) {
    if (!text) return NULL;
    const unsigned char text_length = strlen(text);
    unsigned char *zext = malloc(text_length);
    for (unsigned char i = 0; i < text_length; i++) zext[i] = convert_ascii(text[i]);
    return zext;
}

char* convert_zext_to_text(const unsigned char *zext, unsigned char length) {
    if (!zext || length == 0) return "";
    unsigned char text_length = length + 1;
    char *text = malloc(text_length);
    for (unsigned char i = 0; i < length; i++) text[i] = convert_to_ascii(zext[i]);
    text[length] = '\0'; // last ascii string char
    return text;
}

unsigned char get_text_length(const char* text) {
    unsigned char text_length = strlen(text);
    return text_length;
}

#define text_to_zext(text) get_text_length(text), convert_string_to_zext(text)

#define zox_log_name(log, e) {\
    char *text = convert_zext_to_text(zox_get_value_(e, ZoxName), zox_get_length_(e, ZoxName));\
    zox_log(log"\n", text)\
    free(text);\
}

/*void prefab_set_entity_zox_name(ecs_world_t *world, ecs_entity_t e, char label[]) {
#ifdef zox_entity_names
    char* entity_name = get_entity_string(label, e);
    int length = strlen(entity_name);
    zox_prefab_set(e, ZoxName, { length, convert_string_to_zext(entity_name) })
    free(entity_name);
#endif
}

void set_entity_zox_name(ecs_world_t *world, ecs_entity_t e, char label[]) {
#ifdef zox_entity_names
    char* entity_name = get_entity_string(label, e);
    int length = strlen(entity_name);
    zox_set(e, ZoxName, { length, convert_string_to_zext(entity_name) })
    // zox_log("   + [%s]\n", entity_name)
    free(entity_name);
#endif
}*/

/*void convert_string_zox_name(ZoxName *component, const char* text) {
    unsigned char text_length = strlen(text);
    if (component->length != text_length) resize_memory_component(ZextData, component, unsigned char, text_length)
    for (unsigned char i = 0; i < text_length; i++) component->value[i] = convert_ascii(text[i]);
}*/

/*void print_entity_zox_name(ecs_world_t *world, ecs_entity_t e) {
    if (!zox_has(e, ZoxName)) return;
    const ZoxName *zoxName = zox_get(e, ZoxName)
    char *text = get_zext_text(zoxName);
    zox_log("   > zext %lu [%s] length %i\n", e, text, zoxName->length)
    free(text);
}*/
