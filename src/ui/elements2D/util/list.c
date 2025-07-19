byte calculate_list_max_characters(const SpawnList data) {
    byte max_list_characters = 0; // get max text length out of all of the words
    for (byte i = 0; i < data.count; i++) {
        SpawnListElement child_data = data.elements[i];
        byte txt_size = child_data.text ? strlen(child_data.text) : 0;
        if (txt_size > max_list_characters) {
            max_list_characters = txt_size;
        }
    }
    return max_list_characters;
}

static inline int2 calculate_list_size(
    byte max_characters,
    byte font_size,
    byte padding,
    byte spacing,
    byte list_count)
{
    return (int2) {
        max_characters * font_size + padding * 2 + spacing * 2,
        (font_size + padding * 2 + spacing) * list_count + spacing
    };
}