// #include <ncurses.h>
#include <stdio.h>
#include <termios.h> // for termios, tcgetattr, tcsetattr
#include <unistd.h> // for read, select
// #include <sys/select.h> // for fd_set, FD_ZERO, FD_SET

struct termios old_tio;

void save_terminal_settings() {
    struct termios new_tio;
    /* Save the current terminal settings */
    tcgetattr(STDIN_FILENO, &old_tio);
    /* Set terminal to non-blocking input mode */
    new_tio = old_tio;
    // new_tio.c_lflag &= ~ICANON;
    new_tio.c_lflag &= ~(ICANON | ECHO);
    new_tio.c_cc[VMIN] = 0;
    new_tio.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

void save_terminal_settings_log() {
    struct termios new_tio;
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    // new_tio.c_lflag &= ~(ECHO);
    new_tio.c_lflag &= ~(ICANON | ECHO);
    new_tio.c_cc[VMIN] = 0;
    new_tio.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
    puts("Setting terminal settings to logging.");
}

void restore_terminal_settings() {
    /* Restore the original terminal settings */
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
}

char get_keyboard_key(int is_terminal_ui) {
    char c = 0;
    read(STDIN_FILENO, &c, 1);
    if (!is_terminal_ui && c != '\0') {
        printf("Key input: %c\n", c);
    }
    return c;
}


    /* Clear the terminal buffer */
    // fflush(stdin);
    /* Get the last input character */
    // c = getchar();

    // Check for user input
    // char c = getchar();
    // char c = '';
    /*new_attributes.c_lflag &= ~ICANON;
    new_attributes.c_cc[VMIN] = 0;
    new_attributes.c_cc[VTIME] = 0;*/

    /*if (read(0, &c, 1) > 0) {
    }*/
    /*tcsetattr(STDIN_FILENO, TCSANOW, &old_attributes); // restore terminal
    if (ch == 'q') {
        c = ch;
        //  return 1;
    }*/

    // tcsetattr(STDIN_FILENO, TCSANOW, &old_attributes); // restore terminal
    // tcflush(STDIN_FILENO, TCIFLUSH);



/*char get_keyboard_key() {
    struct termios old_attributes, new_attributes;
    char c;
    // Set terminal to non-blocking mode
    tcgetattr(STDIN_FILENO, &old_attributes);
    new_attributes = old_attributes;
    new_attributes.c_lflag &= ~(ICANON | ECHO);
    new_attributes.c_cc[VMIN] = 1;
    new_attributes.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_attributes);
    tcflush(STDIN_FILENO, TCIFLUSH);

    read(0, &c, 1);
    return c;
}*/