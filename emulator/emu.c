#include <stdio.h>
#include <curses.h>

#include "../logick/gun.h"

/*! Hitting overlay
 */
int ovr_hitting(void *arg){
  hitting(0,0,1,0);
	return 0;
}
/*! Init overlay
 */
int ovr_init(void *arg){
  init();
	return 0;
}
/*! Shoot overlay
 */
int ovr_shoot(void *arg){
  shoot();
	return 0;
}
/////// END OVERLAYS /////////
//////////////////////////////

struct option{
	int (*func)(void* parms);
	int key;
	char* descript;
};

struct option optlist[] = {
	{init,    32, "Init GUN"},
	{shoot,   2,  "Shoot from GUN"},
	{ovr_hitting, 3,  "Hitting from Player"},
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

int HelpWindow()
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

  return WL;
}

WINDOW *w_status;

void StatusWindow(int line)
{
  int L,C;
	int i;
	int optsize = sizeof(optlist)/sizeof(struct option);
  L=LINES;
  C=COLS;
	int WL=optsize+2+line;

  // Malloc's windows
  const char* title = " STATUS ";
  if(C>90) C=90;
  if(L>WL) L=WL;

  w_status = newwin(L, C, line, 0);
  box(w_status, 0, 0);

  // TITLE
  wmove(w_status,0,C/2-sizeof(title));
  wprintw(w_status, title);

  // INFO
  i=1;
#define MSG(arg) \
  	wmove(w_status,i++,3); \
		wprintw(w_status, #arg" -- %i", gun_status.arg);
    MSG(amons);
    MSG(health);
    MSG(life);
#undef MSG
  
  wrefresh(w_status);
  delwin(w_status);
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
    int line = HelpWindow();
    StatusWindow(line);
    int kcode=getch();

    switch(kcode){
      case 32: init();
               break;
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
