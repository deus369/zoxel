#include <stdarg.h> // for va_list, va_start, and va_end
#include <stdlib.h>     // for system function
#include <unistd.h>     // for write function

int is_dirty = 1;
int is_terminal_ui = 1;

struct terminal_size {
  int rows;
  int cols;
};

struct terminal_size get_terminal_size() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  struct terminal_size size = {w.ws_row, w.ws_col};
  return size;
}

void clear_terminal() {
    system("clear");
    // printf("\033[H\033[J");
    // struct terminal_size size = get_terminal_size();
    //printf("\033[3J"); // clear the screen and the scrollback buffer
    //printf("\033[0;0H"); // move the cursor to the top left
    //printf("\033[%d;1H", size.rows); // move the cursor to the bottom of the screen
    // fflush(stdout); // flush the output buffer
}

void save_terminal_state() {
  printf("\033[s"); // save the cursor position
  printf("\033[?1049h"); // save the terminal attributes and switch to alternate buffer
  printf("\033[1;1r"); // set the scrolling region to the entire screen
}

void restore_terminal_state() {
  printf("\033[2J"); // clear the screen
  printf("\033[?1049l"); // restore the terminal attributes and switch back to normal buffer
  printf("\033[u"); // restore the cursor position
}
// printf("\033[2J\033[1;1H"); // clear the screen and move the cursor to the top-left corner

#define LINE_SIZE 100

void add_text(char *text, char *line, ...) {
    // strcat(text, line); // add the line to the text
    va_list args;
    va_start(args, line);
    vsnprintf(text + strlen(text), LINE_SIZE, line, args);
    va_end(args);
}

void display_centered_text(char *text) {
    struct terminal_size size = get_terminal_size();
    int row = (size.rows / 2); //  - 1;
    int col = size.cols / 2;
    int text_len = strlen(text);
    int i = 0;
    while (i < text_len) {
        // Find the next newline character
        int j = i;
            while (text[j] != '\n' && text[j] != '\0') {
            j++;
        }
        // Calculate the position to display the line
        int line_len = j - i;
        int line_col = col - line_len / 2;
        // Display the line
        printf("\033[%d;%dH%.*s", row, line_col, line_len, text + i);
        fflush(stdout); // flush the output buffer
        // Move to the next line
        row++;
        i = j + 1;
    }
}