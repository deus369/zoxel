typedef struct {
    char *value;
    int length;
} string_data;

string_data new_string_data(char *value) {
    return (string_data) { .value = value, .length = strlen(value) };
}

string_data new_string_data_clone(char *value) {
    size_t length = strlen(value);
    char* new_value = (char*) malloc(length + 1); // Allocate memory for the new string
    if (!new_value) {
        return (string_data) {
            .value = NULL,
            .length = 0
        };
    }
    memcpy(new_value, value, length);
    new_value[length] = '\0'; // Null-terminate the new string
    return (string_data) {
        .value = new_value,
        .length = length
    };
}

uint get_string_hash(string_data input) {
    if (input.value == NULL || input.length < 0) {
        // Handle error: invalid input
        return 0; // or some other error code
    }
    uint hash = 5381; // djb2 initial hash constant
    for (int i = 0; i < input.length; i++) {
        hash = ((hash << 5) + hash) + (uint) input.value[i];
    }
    return hash;
}