#define zoxel_convert_to_ascii_start(char, number) if (input == number) return char;\

#define zoxel_convert_to_ascii(char, number) else if (input == number) return char;

char convert_to_ascii(unsigned char input) {
    zoxel_convert_to_ascii_start('?', 0)
    zoxel_convert_to_ascii('\n', 254)
    // lower case
    zoxel_convert_to_ascii('a', 1)
    zoxel_convert_to_ascii('b', 2)
    zoxel_convert_to_ascii('c', 3)
    zoxel_convert_to_ascii('d', 4)
    zoxel_convert_to_ascii('e', 5)
    zoxel_convert_to_ascii('f', 6)
    zoxel_convert_to_ascii('g', 7)
    zoxel_convert_to_ascii('h', 8)
    zoxel_convert_to_ascii('i', 9)
    zoxel_convert_to_ascii('j', 10)
    zoxel_convert_to_ascii('k', 11)
    zoxel_convert_to_ascii('l', 12)
    zoxel_convert_to_ascii('m', 13)
    zoxel_convert_to_ascii('n', 14)
    zoxel_convert_to_ascii('o', 15)
    zoxel_convert_to_ascii('p', 16)
    zoxel_convert_to_ascii('q', 17)
    zoxel_convert_to_ascii('r', 18)
    zoxel_convert_to_ascii('s', 19)
    zoxel_convert_to_ascii('t', 20)
    zoxel_convert_to_ascii('u', 21)
    zoxel_convert_to_ascii('v', 22)
    zoxel_convert_to_ascii('w', 23)
    zoxel_convert_to_ascii('x', 24)
    zoxel_convert_to_ascii('y', 25)
    zoxel_convert_to_ascii('z', 26)
    // upper case
    zoxel_convert_to_ascii('A', 27)
    zoxel_convert_to_ascii('B', 28)
    zoxel_convert_to_ascii('C', 29)
    zoxel_convert_to_ascii('D', 30)
    zoxel_convert_to_ascii('E', 31)
    zoxel_convert_to_ascii('F', 32)
    zoxel_convert_to_ascii('G', 33)
    zoxel_convert_to_ascii('H', 34)
    zoxel_convert_to_ascii('I', 35)
    zoxel_convert_to_ascii('J', 36)
    zoxel_convert_to_ascii('K', 37)
    zoxel_convert_to_ascii('L', 38)
    zoxel_convert_to_ascii('M', 39)
    zoxel_convert_to_ascii('N', 40)
    zoxel_convert_to_ascii('O', 41)
    zoxel_convert_to_ascii('P', 42)
    zoxel_convert_to_ascii('Q', 43)
    zoxel_convert_to_ascii('R', 44)
    zoxel_convert_to_ascii('S', 45)
    zoxel_convert_to_ascii('T', 46)
    zoxel_convert_to_ascii('U', 47)
    zoxel_convert_to_ascii('V', 48)
    zoxel_convert_to_ascii('W', 49)
    zoxel_convert_to_ascii('X', 50)
    zoxel_convert_to_ascii('Y', 51)
    zoxel_convert_to_ascii('Z', 52)
    // special
    zoxel_convert_to_ascii(' ', 55)
    zoxel_convert_to_ascii('.', 56)
    zoxel_convert_to_ascii(',', 57)
    zoxel_convert_to_ascii('/', 58)
    zoxel_convert_to_ascii('\\', 59)
    zoxel_convert_to_ascii('_', 70)
    zoxel_convert_to_ascii('[', 71)
    zoxel_convert_to_ascii(']', 72)
    zoxel_convert_to_ascii('-', 73)
    zoxel_convert_to_ascii('+', 74)
    zoxel_convert_to_ascii('=', 75)
    zoxel_convert_to_ascii('%', 76)
    // numbers
    zoxel_convert_to_ascii('0', 60)
    zoxel_convert_to_ascii('1', 61)
    zoxel_convert_to_ascii('2', 62)
    zoxel_convert_to_ascii('3', 63)
    zoxel_convert_to_ascii('4', 64)
    zoxel_convert_to_ascii('5', 65)
    zoxel_convert_to_ascii('6', 66)
    zoxel_convert_to_ascii('7', 67)
    zoxel_convert_to_ascii('8', 68)
    zoxel_convert_to_ascii('9', 69)
    return ' ';
}

char* convert_to_ascii_text(unsigned char *input, int length) {
    char *output = malloc(sizeof(char) * length);
    for (int i = 0; i < length; i++) output[i] = convert_to_ascii(input[i]);
    return output;
}

char* convert_to_ascii_text_at(unsigned char *input, int length, unsigned char at_index) {
    char *output = malloc(sizeof(char) * (length + 1));
    for (unsigned char i = at_index; i < at_index + length; i++) output[(i - at_index)] = convert_to_ascii(input[i]);
    output[length] = '\0';
    return output;
}

// printf("Converting Ascii from byte: %i : %i : %c\n", i, input[i], output[output_index]);
