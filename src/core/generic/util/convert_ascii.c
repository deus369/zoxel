#define zoxel_convert_ascii(char, number) else if (input == char) return number;

//! \todo use a Hash Map to convert these
unsigned char convert_ascii(char input) {
    // special characters
    if (input == '?') return 0;
    zoxel_convert_ascii('\n', 254)
    // lower case
    zoxel_convert_ascii('a', 1)
    zoxel_convert_ascii('b', 2)
    zoxel_convert_ascii('c', 3)
    zoxel_convert_ascii('d', 4)
    zoxel_convert_ascii('e', 5)
    zoxel_convert_ascii('f', 6)
    zoxel_convert_ascii('g', 7)
    zoxel_convert_ascii('h', 8)
    zoxel_convert_ascii('i', 9)
    zoxel_convert_ascii('j', 10)
    zoxel_convert_ascii('k', 11)
    zoxel_convert_ascii('l', 12)
    zoxel_convert_ascii('m', 13)
    zoxel_convert_ascii('n', 14)
    zoxel_convert_ascii('o', 15)
    zoxel_convert_ascii('p', 16)
    zoxel_convert_ascii('q', 17)
    zoxel_convert_ascii('r', 18)
    zoxel_convert_ascii('s', 19)
    zoxel_convert_ascii('t', 20)
    zoxel_convert_ascii('u', 21)
    zoxel_convert_ascii('v', 22)
    zoxel_convert_ascii('w', 23)
    zoxel_convert_ascii('x', 24)
    zoxel_convert_ascii('y', 25)
    zoxel_convert_ascii('z', 26)
    // upper case
    zoxel_convert_ascii('A', 27)
    zoxel_convert_ascii('B', 28)
    zoxel_convert_ascii('C', 29)
    zoxel_convert_ascii('D', 30)
    zoxel_convert_ascii('E', 31)
    zoxel_convert_ascii('F', 32)
    zoxel_convert_ascii('G', 33)
    zoxel_convert_ascii('H', 34)
    zoxel_convert_ascii('I', 35)
    zoxel_convert_ascii('J', 36)
    zoxel_convert_ascii('K', 37)
    zoxel_convert_ascii('L', 38)
    zoxel_convert_ascii('M', 39)
    zoxel_convert_ascii('N', 40)
    zoxel_convert_ascii('O', 41)
    zoxel_convert_ascii('P', 42)
    zoxel_convert_ascii('Q', 43)
    zoxel_convert_ascii('R', 44)
    zoxel_convert_ascii('S', 45)
    zoxel_convert_ascii('T', 46)
    zoxel_convert_ascii('U', 47)
    zoxel_convert_ascii('V', 48)
    zoxel_convert_ascii('W', 49)
    zoxel_convert_ascii('X', 50)
    zoxel_convert_ascii('Y', 51)
    zoxel_convert_ascii('Z', 52)
    // special
    zoxel_convert_ascii(' ', 55)
    zoxel_convert_ascii('.', 56)
    zoxel_convert_ascii(',', 57)
    zoxel_convert_ascii('/', 58)
    zoxel_convert_ascii('\\', 59)
    zoxel_convert_ascii('_', 70)
    zoxel_convert_ascii('[', 71)
    zoxel_convert_ascii(']', 72)
    zoxel_convert_ascii('-', 73)
    zoxel_convert_ascii('+', 74)
    zoxel_convert_ascii('=', 75)
    zoxel_convert_ascii('%', 76)
    // numbers
    zoxel_convert_ascii('0', 60)
    zoxel_convert_ascii('1', 61)
    zoxel_convert_ascii('2', 62)
    zoxel_convert_ascii('3', 63)
    zoxel_convert_ascii('4', 64)
    zoxel_convert_ascii('5', 65)
    zoxel_convert_ascii('6', 66)
    zoxel_convert_ascii('7', 67)
    zoxel_convert_ascii('8', 68)
    zoxel_convert_ascii('9', 69)
    return 0;
}

/*unsigned char* convert_ascii_text(const char *input, int length) {
    static unsigned char output[length];
    for (int i = 0; i < length; i++)
    {
        output[i] = convert_ascii(input[i]);
    }
    return output;
}*/

unsigned char* convert_from_ascii_text_at(const char *input, unsigned char start_buffer) {
    unsigned char length = start_buffer + strlen(input);
    unsigned char *output = malloc(length);
    for (unsigned char i = start_buffer; i < length; i++) {
        unsigned char input_index = i - start_buffer;
        output[i] = convert_ascii(input[input_index]);
        // printf("Converting Ascii to byte: %i : %i : %c\n", i, output[i], input[input_index]);
    }
    return output;
}
