const char *syllabells[] = {
    "mo",
    "monn",
    "fay",
    "shi",
    "zag",
    "zen",
    "tex",
    "zel",
    "pie",
    "ze",
    "zi",
    "me",
    "mi",
    "el",
    "te",
    "ex",
    "te",
    "bi",
    "si",
    "le",
    "ga",
    "ta",
    "ba"
};

char ascii_to_upper(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 32; // Convert lowercase to uppercase
    }
    return c; // If already uppercase or not a letter, return the character unchanged
}

char* generate_name() {
    // srand(time(NULL));
    int syllable_count = rand() % 3 + 2; // Random number between 2 and 4
    char* name = (char*) malloc((syllable_count * 3) + 1); // Assuming max length of syllable is 3
    if (name == NULL) return NULL;
    name[0] = '\0';
    for (int i = 0; i < syllable_count; i++) {
        strcat(name, syllabells[rand() % 23]);
    }
    name[0] = ascii_to_upper(name[0]);
    return name;
}
