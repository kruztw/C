#include <curses.h>

#define GameWinHeight 10
#define GameWinWidth 40

#define cls() printf("\e[1;1H\e[2J")

void initCurses()
{
    cls();
    initscr();
    cbreak();
    nonl();
    noecho();                  // 輸入不會輸出 (e.g. 按 a 不會顯示 a)
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);
    refresh();
}


int main() 
{
    int currX = 1, currY = 1;
    initCurses();
    WINDOW *gameWin = newwin(GameWinHeight, GameWinWidth, LINES/2-15, COLS/2-20);
    box(gameWin, '|', '-');
    wmove(gameWin, currY, currX);
    
    while (1) {
        wrefresh(gameWin);
        char ch = getch();
    }
}
