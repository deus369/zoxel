#define zoxel_convert_ascii(char, number)\
else if (input == char)\
{\
    return number;\
}

//! \todo use a Hash Map to convert these
unsigned char convert_ascii(char input)
{
    // special characters
    if (input == '?')
    {
        return 0;
    }
    zoxel_convert_ascii(' ', 55)
    zoxel_convert_ascii('.', 56)
    zoxel_convert_ascii(',', 57)
    zoxel_convert_ascii('/', 58)
    zoxel_convert_ascii('\\', 59)
    zoxel_convert_ascii('.', 56)
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
    else if (input == 'A')
    {
        return 27;
    }
    else if (input == 'B')
    {
        return 28;
    }
    else if (input == 'C')
    {
        return 29;
    }
    else if (input == 'D')
    {
        return 30;
    }
    else if (input == 'E')
    {
        return 31;
    }
    else if (input == 'F')
    {
        return 32;
    }
    else if (input == 'G')
    {
        return 33;
    }
    else if (input == 'H')
    {
        return 34;
    }
    else if (input == 'I')
    {
        return 35;
    }
    else if (input == 'J')
    {
        return 36;
    }
    else if (input == 'K')
    {
        return 37;
    }
    else if (input == 'L')
    {
        return 38;
    }
    else if (input == 'M')
    {
        return 39;
    }
    else if (input == 'N')
    {
        return 40;
    }
    else if (input == 'O')
    {
        return 41;
    }
    else if (input == 'P')
    {
        return 42;
    }
    else if (input == 'Q')
    {
        return 43;
    }
    else if (input == 'R')
    {
        return 44;
    }
    else if (input == 'S')
    {
        return 45;
    }
    else if (input == 'T')
    {
        return 46;
    }
    else if (input == 'U')
    {
        return 47;
    }
    else if (input == 'V')
    {
        return 48;
    }
    else if (input == 'W')
    {
        return 49;
    }
    else if (input == 'X')
    {
        return 50;
    }
    else if (input == 'Y')
    {
        return 51;
    }
    else if (input == 'Z')
    {
        return 52;
    }
    return 0;
}