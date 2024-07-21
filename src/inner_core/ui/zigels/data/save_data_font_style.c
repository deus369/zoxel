// a simple struct for saving font styles
#define max_save_data_fonts 256
#define max_font_points 256

typedef struct {
    int length;
    byte2 points[max_font_points];
} SaveDataFont;

typedef struct {
    int length;
    SaveDataFont fonts[max_save_data_fonts];
} SaveDataFontStyle;
