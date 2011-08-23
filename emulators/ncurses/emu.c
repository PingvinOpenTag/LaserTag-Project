#include <stdio.h>
#include <curses.h>

//##include "../logick/gun.h"
#include <gun.h>

/*! Hitting overlay
 */
int ovr_hitstatclear(void *arg){
  hitstat_clean();
	return 0;
}
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
	{shoot,   97,  "Shoot from GUN"},
	{ovr_hitting, 115,  "Hitting from Player"},
	{ovr_hitstatclear, 100,  "Clear status"},
};

char* keynumtochar(int key)
{
  char result;
  switch(key){
    case 32:  return "space";
    case 97:  return "a";
    case 98:  return "b";
    case 99:  return "c";
    case 100:  return "d";
    case 101:  return "e";
    case 102:  return "f";
    case 103:  return "g";
    case 104:  return "h";
    case 105:  return "i";
    case 106:  return "j";
    case 107:  return "k";
    case 108:  return "l";
    case 109:  return "m";
    case 110:  return "n";
    case 111:  return "o";
    case 112:  return "p";
    case 113:  return "q";
    case 114:  return "r";
    case 115:  return "s";
    case 116:  return "t";
  }

  return NULL;
}

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
  C=COLS/2;
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
    char* keychar = keynumtochar(o->key);
    if(keychar!=NULL)
      wprintw(w_help, "%s -- %s", keychar, o->descript);
    else
      wprintw(w_help, "%i -- %s", o->key , o->descript);
	}
  
  wrefresh(w_help);
  delwin(w_help);

  return WL;
}

WINDOW *w_status;
extern int hitstat_cur;

int StatusWindow(int line)
{
  int L,C, start_C;
	int i;
	int optsize = sizeof(optlist)/sizeof(struct option);
  L=LINES;
  start_C=COLS/2;
  C=COLS/2;
	int WL=optsize+2+line;

  // Malloc's windows
  const char* title = " STATUS ";
  if(C>90) C=90;
  if(L>WL) L=WL;

  w_status = newwin(L, C, 0, start_C);
  box(w_status, 0, 0);

  // TITLE
  wmove(w_status,0,C/2-sizeof(title));
  wprintw(w_status, title);

  // INFO
  i=1;
#define MSG(arg) \
  	wmove(w_status,i++,3); \
		wprintw(w_status, #arg" -- %i", gun_status.arg);
    MSG(ammons);
    MSG(health);
    MSG(life);
#undef MSG
  wmove(w_status,i++,3);
	wprintw(w_status, "statru -- %i", hitstat_cur);


  wrefresh(w_status);
  delwin(w_status);
  return WL;
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
  
  //WINDOW *w_log;
  while(true)
  {
    int line;
    line = HelpWindow();
    line = StatusWindow(line);
    int kcode=getch();
  
	  int optsize = sizeof(optlist)/sizeof(struct option);
    int keydecode=0;
    while(optsize--!=0){
      if(kcode == optlist[optsize].key){
        printw("%s...\n", optlist[optsize].descript);
        optlist[optsize].func(NULL);
        keydecode=1;
      }
    }
    if(!keydecode){
      if(kcode == 3)
        goto ExitProg; // Ctrl+C on raw mode
      else
        printw("It key(code:%i) don't support, sorry\n", kcode);
    }
    refresh();
  }

ExitProg:
  CloseIt();
  return 0;
}
