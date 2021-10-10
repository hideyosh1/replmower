#include <iostream>
#ifndef CURSES_INCLUDED
#include <curses.h>
#endif
#include <memory>
#include <boost/program_options.hpp>
#include "player.hpp"
#include "loader.hpp"
#include "obsvsbj.hpp"


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
  int sx, sy, ch;
  const char block = (char) 219;
  getmaxyx(stdscr, sy, sx);

  WINDOW* pwin = newwin(5, sx, sy-5, 0); 
  WINDOW* playwin = newwin(sy-5, sx, 0, 0);
  
  //nlines ncols starty startx
  std::unique_ptr<player> mainc = std::make_unique<player>();
  //hate raw pointers so....

  mvaddstr(0, (sx-13)/2, "SUPERMOWERMAN");
  mvaddstr(1, (sx-10)/2, "a game???");
  mvaddstr(2, (sx-7)/2, "any key");
  ch = getch();
  clear();
  refresh();
std::cout<< sx << sy << ch << block;

  delwin(pwin);
  delwin(playwin);
  //delthewins
  endwin();


}