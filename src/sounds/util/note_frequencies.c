const float note_frequencies[] = {
    // 0
    16.35f, // C
    17.32f, // C#
    18.35f, // D
    19.45f, // D#
    20.60f, // E
    21.83f, // F
    23.12f, // F #
    24.50f, // G
    25.96f, // G #
    27.50f, // A
    // 10
    29.14f, // A #
    30.87f, // B
    // level 1
    32.70f, // C1
    34.65f, // C1#
    36.71f, // D1
    38.89f, // D1#
    41.20f, // E1
    43.65f, // F1
    46.25f, // F1#
    49.00f, // G1
    // 20
    51.91f, // G1#
    55.00f, // A1
    58.27f, // A1#
    61.74f, // B1
    // level 2
    69.30f, // C2
    69.30f, // C2#
    73.42f, // D2
    77.78f, // D2#
    82.41f, // E2
    87.31f, // F2
    // 30
    92.50f, // F2#
    98.00f, // G2
    103.83f, // G2#
    110.00f, // A2
    116.54f, // A2#
    123.47f, // B2
    // level 3
    130.81f, // C3
    138.59f, // C3#
    146.83f, // D3
    155.56f, // D3#
    // 40
    164.81f, // E3
    174.61f, // F3
    185.00f, // F3#
    196.00f, // G3
    207.65f, // G3#
    220.00f, // A3
    233.08f, // A3#
    246.94f, // B3
    // level 4
    261.63f, // C4
    277.18f, // C4#
    // 50
    293.66f, // D4
    311.13f, // D4#
    329.63f, // E4
    349.23f, // F4
    369.99f, // F4#
    392.00f, // G4
    415.30f, // G4 #
    440.00f, // A4
    466.16f, // A4 #
    493.88f, // B4
    // 60
    // level 5
    523.25f, // C5
    554.37f, // C5#
    587.33f, // D5
    622.25f, // D5#
    659.25f, // E5
    698.46f, // F5
    739.99f, // F5#
    783.99f, // G5
    830.61f, // G5 #
    880.00f, // A5
    // 70
    932.33f, // A5#
    987.77f // B5
};
const int notes_max = 72;

// Function to find the closest note index for a given frequency
int find_note_index(float frequency) {
    int closest_index = 0;
    float min_diff = fabs(note_frequencies[0] - frequency);
    // Iterate through the note_frequencies array to find the closest match
    for (int i = 1; i < notes_max; i++) {
        float diff = fabs(note_frequencies[i] - frequency);
        if (diff < min_diff) {
            min_diff = diff;
            closest_index = i;
        }
    }
    return closest_index;
}
