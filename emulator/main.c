#include <stdio.h>
#include <curses.h>

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}

WINDOW *w_help;

void HelpWindow()
{
  int L,C;
  L=LINES;
  C=COLS;
  // Malloc's windows
  const char* title = " HELP ";
  if(C>90) C=90;
  if(L>30) L=30;

  w_help = newwin(L, C, 0, 0);
  box(w_help, 0, 0);

  // TITLE
  wmove(w_help,0,C/2-sizeof(title));
  wprintw(w_help, title);

  // INFO
  wmove(w_help,1,3);
  wprintw(w_help, "Space -- One shot");
  
  wmove(w_help,2,3);
  wprintw(w_help, "a     -- hit me");

  wrefresh(w_help);
  delwin(w_help);
}

void InitIt()
{
  // Init curcess
  initscr();  
  noecho();
  raw();
  cbreak();
  //curs_set(2);
  keypad(stdscr, TRUE);// F1, F2...
  printw("COLS,LINES: %i,%i\n", COLS, LINES);
  refresh();

  // Malloc's windows
  w_help = newwin(3, 10, 10, 30);
  box(w_help, 0, 0);
  wborder(w_help, '|', '|', '-', '-', '+','+', '+','+');
  wrefresh(w_help);
  delwin(w_help);
  move(30,0);

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
 // wprintw(stdscr, "Win");
  //refresh();
  //setxy(20,20);
  while(true)
  {
    HelpWindow();
   //create_newwin(10,40,10,10);
    //PrintHelp();
    int kcode=getch();

    switch(kcode){
      case 3: goto ExitProg; // Ctrl+C on raw mode
      default:
              printw("It key(code:%i) don't support, sorry\n", kcode);
    }
    refresh();
  }

ExitProg:
  CloseIt();
  return 0;
}
