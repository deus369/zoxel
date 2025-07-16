typedef struct {
    const char* name;
    on_set_event on_set;
    byte type;

    byte min_byte;
    byte max_byte;
    byte value_byte;

    float min_float;
    float max_float;
    float value_float;

    int min_int;
    int max_int;
    int value_int;

    const char* value_string;
} setting;