#include <stdio.h>
#include <curses.h>

#define DESKRSIZE 100

int test1(void* parms){

	return 0;
}
int test2(void* parms){

	return 0;
}

struct option{
	int (*func)(void* parms);
	int key;
	char* descript;
	//char* descript[DESKRSIZE];
};

struct option optlist[] = {
	{test1, 10, "Test"},
	{test2, 2, "Test 3"},
	{test2, 3, "Test 4"},
	{test2, 4, "Test 5"}
};

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
	int i;
	int optsize = sizeof(optlist)/sizeof(struct option);
  L=LINES;
  C=COLS;
	int WL=optsize+2;

  // Malloc's windows
  const char* title = " HELP ";
  if(C>90) C=90;
  if(L>WL) L=WL;

  w_help = newwin(L, C, 0, 0);
  box(w_help, 0, 0);

  // TITLE
  wmove(w_help,0,C/2-sizeof(title));
  wprintw(w_help, title);

  // INFO
	for(i=0;i<optsize;i++){
		struct option *o=&optlist[i];
  	wmove(w_help,i+1,3);
		wprintw(w_help, "%i -- %s", o->key, o->descript);
	}
  
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

int main(void)
{

  InitIt();
  while(true)
  {
    HelpWindow();
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
