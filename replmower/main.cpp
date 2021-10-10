#include <iostream>
#ifndef CURSES_INCLUDED
#include <curses.h>
#endif
#include <memory>
#include <popl.hpp>
#include "player.hpp"
#include "loader.hpp"
#include "obsvsbj.hpp"

int checksc(int x, int y, int sx, int sy, int scale);
//nice and clean
int main() {
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, true);

  enum{
    UP,
    DOWN,
    LEFT,
    RIGHT
  };
  enum {
      map0,
      map1,
      map2,
      map3,
      map4,
      map5,
      map6,
      map7,
      map8
  };
  int sx, sy, ch, lvl;
  bool playin = false;
  const char block = (char) 219;
  getmaxyx(stdscr, sy, sx);

  WINDOW* pwin = newwin(5, sx, sy-5, 0); 
  WINDOW* playwin = newwin(sy-5, sx, 0, 0);
  
  //nlines ncols starty startx
  player* mainc = new player; //delete at the edn!!!
  //hate raw pointers so....

  mvaddstr(0, (sx-13)/2, "SUPERMOWERMAN");
  mvaddstr(1, (sx-10)/2, "a game???");
  mvaddstr(2, (sx-7)/2, "any key");
  ch = getch();
  clear();
  refresh();
    std::cout<< sx << sy << ch << block;
    box(pwin, 0, 0);
    box(playwin, 0, 0);
    wrefresh(pwin);
    wrefresh(playwin);

    mvwaddstr(pwin, 1, 1, "welcome to super mower!");

    

    subject* keyb = new subject;
    keyb->addob(mainc);
    //the keyboard subject and yeah it's a raw pointer but see the delete lmao
    

    while (playin) {
        ch = getch();
        switch (ch) {
        case 'e':
            goto del;
            break;
        case 'w':
            keyb->update("u");
            break;
        case 'a':
            keyb->update("l");
            break;
        case 's':
            keyb->update("d");
            break;
        case 'd':
            keyb->update("r");
            break;
        }

  }
del:
    wborder(pwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wborder(playwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    delwin(pwin);
    delwin(playwin);
    delete keyb;
    delete mainc;
    //delthewins
    endwin();
    exit(0);


}
int checksc(int x, int y, int sx, int sy, int scale) { //if scale isn't optimal, return correct scale; otherwise, 
                                                        //return
    if (x == 0 || y == 0 || sx == 0 || sy == 0) {
        exit(1);
    }
    if (((x * scale > sx) && (x * (scale - 1) < sx)) || ((y * scale > sy) && (y * (scale - 1) < sy))) {
        return scale - 1;
    }
    if ((x * scale > sx) || (y * scale > sy)) {
        return checksc(x, y, sx, sy, scale - 1);
    }
    else if ((x * scale < sx) || (y * scale < sy)) {
        return checksc(x, y, sx, sy, scale + 1);
    }
    return 0;
}