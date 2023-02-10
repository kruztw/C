#include <curses.h>

int main() {
    // initial screen
    initscr();

    // no input buffer
    cbreak();

    // don't echo user input
    noecho();

    // move(0, 0) and addch('+')
    // move: move cursor
    // addch: add char
    mvaddch(0, 0, '+'); // (0, 0) is top left
    mvaddch(LINES - 1, COLS - 1, '-'); // (LINES-1, COLS-1) is bottom right

    // addstr: add string
    mvaddstr(10, 30, "press any key to quit");

    
    refresh();

    // get a character from user
    getch();

    // end windows
    endwin();

    return 0;
}
