byte* convert_string_to_zext(const char* text) {
    if (!text) return NULL;
    const byte text_length = strlen(text);
    byte *zext = malloc(text_length);
    for (byte i = 0; i < text_length; i++) zext[i] = convert_ascii(text[i]);
    return zext;
}

byte* convert_text_to_zext(const char* text) {
    if (!text) return NULL;
    const byte text_length = strlen(text);
    byte *zext = malloc(text_length);
    for (byte i = 0; i < text_length; i++) zext[i] = convert_ascii(text[i]);
    return zext;
}

void convert_zext_to_text_non_malloc(const byte *zext, int length, char* text, int max_text) {
    if (!zext || length == 0) {
        return;
    }
    if (length > max_text - 1) {
        length = max_text - 1;
    }
    for (byte i = 0; i < length; i++) {
        text[i] = convert_to_ascii(zext[i]);
    }
    text[length] = '\0'; // last ascii string char
}

char* convert_zext_to_text(const byte *zext, byte length) {
    if (!zext || length == 0) return "";
    byte text_length = length + 1;
    char *text = malloc(text_length);
    for (byte i = 0; i < length; i++) text[i] = convert_to_ascii(zext[i]);
    text[length] = '\0'; // last ascii string char
    return text;
}

byte get_text_length(const char* text) {
    byte text_length = strlen(text);
    return text_length;
}

#define text_to_zext(text) get_text_length(text), convert_string_to_zext(text)

#define zox_log_name(log, e) {\
    char *text = convert_zext_to_text(zox_get_value_(e, ZoxName), zox_get_length_(e, ZoxName));\
    zox_log(log"\n", text)\
    free(text);\
}
