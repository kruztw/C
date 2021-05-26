#include <curses.h>
#include <unistd.h>

#define GameWinWidth 40
#define GameWinHeight 10
#define BtnWidth 10
#define BtnHeight 3

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

void refreshBtnWin(WINDOW *win)
{
    for (int i = 0; i < BtnHeight; i++)
        for (int j = 0; j < BtnWidth; j++) {
            if (i == 0 && j == 0)
                mvwaddstr(win, i, j, "X");
            else if (i == BtnHeight-1 && j == 0)
                mvwaddstr(win, i, j, "X");
            else if (i == 0 && j == BtnWidth-1)
                mvwaddstr(win, i, j, "X");
            else if (i == BtnHeight-1 && j == BtnWidth-1)
                mvwaddstr(win, i, j, "X");
            else if (i == 0 || i == BtnHeight-1)
                mvwaddstr(win, i, j, "-");
            else if (j == 0 || j == BtnWidth-1)
                mvwaddstr(win, i, j, "|");
            else
                mvwaddstr(win, i, j, " ");
        }
   
    wrefresh(win);
}

void pressAnime(WINDOW *win)
{
    for (int i = 0; i < BtnHeight; i++)
        for (int j = 0; j < BtnWidth; j++)
            mvwaddstr(win, i, j, "@");
    
    wrefresh(win);
    usleep(50*1000);

    refreshBtnWin(win);
}


int main() 
{
    int currX = 1;
    int currY = 1;
    initCurses();
    WINDOW *gameWin = newwin(GameWinHeight, GameWinWidth, LINES/2-15, COLS/2-20);
    WINDOW *btnD = newwin(BtnHeight, BtnWidth, LINES/2, COLS/2-10);
    box(btnD, '|', '-');
    refreshBtnWin(btnD);
    wmove(gameWin, currY, currX);
    
    while (1) {
        wrefresh(gameWin);
        int ch = getch();
        switch (ch) {
        case 'd':
            pressAnime(btnD);
            currX ++;
            break;
        }

        wmove(gameWin, currY, currX);
    }
}
