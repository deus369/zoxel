// for only the button
typedef struct {
    SpawnListElement* elements;
    int count;
    int visible_count;
    byte font_size;
    color fill;
    color outline;
    // from window
    Children *children;
    // list spacing
    byte padding; // = 8;   // space in button around font
    byte spacing; // = 24;  // space between list elements
    // slider
    int slider_height; // = 64; // now we doing labels
    int slider_padding; // = 64;
} SpawnList;