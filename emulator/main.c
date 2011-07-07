#include <stdio.h>
#include <curses.h>

int X,Y;
WINDOW *w_help;

void InitIt()
{
  // Init curcess
  initscr();  
  noecho();
  raw();
  keypad(stdscr, TRUE);// F1, F2...

  getmaxyx(stdscr, X, Y);

  // Malloc's windows
  w_help = newwin(20, 20, 1, 1);
  box(w_help, 0, 0);
  wprintw(w_help, "Win");
  wrefresh(w_help);

}

void CloseIt()
{
  endwin();
}


void PrintFace()
{
  
}

int main(void)
{
  InitIt();
  while(true)
  {
    //PrintHelp();
    int kcode=getch();

    switch(kcode){
      case 3: goto ExitProg; // Ctrl+C on raw mode
      default:
              printw("It key(code:%i) don't support, sorry\n", kcode);
    }
  }

ExitProg:
  CloseIt();
  return 0;
}
