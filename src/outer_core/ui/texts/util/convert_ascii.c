//! \todo use a Hash Map to convert these
unsigned char convert_ascii(char input)
{
    if (input == '?')
    {
        return 0;
    }
    else if (input == ' ')
    {
        return 27;
    }
    else if (input == 'a')
    {
        return 1;
    }
    else if (input == 'b')
    {
        return 2;
    }
    else if (input == 'c')
    {
        return 3;
    }
    else if (input == 'd')
    {
        return 4;
    }
    else if (input == 'e')
    {
        return 5;
    }
    else if (input == 'f')
    {
        return 6;
    }
    else if (input == 'g')
    {
        return 7;
    }
    else if (input == 'h')
    {
        return 8;
    }
    else if (input == 'i')
    {
        return 9;
    }
    else if (input == 'j')
    {
        return 10;
    }
    else if (input == 'k')
    {
        return 11;
    }
    else if (input == 'l')
    {
        return 12;
    }
    else if (input == 'm')
    {
        return 13;
    }
    else if (input == 'n')
    {
        return 14;
    }
    else if (input == 'o')
    {
        return 15;
    }
    else if (input == 'p')
    {
        return 16;
    }
    else if (input == 'q')
    {
        return 17;
    }
    else if (input == 'r')
    {
        return 18;
    }
    else if (input == 's')
    {
        return 19;
    }
    else if (input == 't')
    {
        return 20;
    }
    else if (input == 'u')
    {
        return 21;
    }
    else if (input == 'v')
    {
        return 22;
    }
    else if (input == 'w')
    {
        return 23;
    }
    else if (input == 'x')
    {
        return 24;
    }
    else if (input == 'y')
    {
        return 25;
    }
    else if (input == 'z')
    {
        return 26;
    }
    return 0;
}