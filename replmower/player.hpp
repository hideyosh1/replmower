#pragma once
#ifndef CURSES_INCLUDED
#include <curses.h>
#endif

class player{
private:
int x, y;
public:
 player(int stx = 0, int sty = 0){
   x = stx;
   y = sty;
 }
void mv(int dir, int steps = 1){
  int mvx, mvy;
  getmaxyx(stdscr, mvy, mvx);
  enum{
    UP,
    DOWN,
    LEFT,
    RIGHT
  };
  switch(dir){
    case UP:
      if(y <= 0){
        y = 0;
      }else{
        y--;
      }
    break;
    case LEFT:
    if(x <= 0){
        x = 0;
      }else{
        x--;
      }
    break;
    case RIGHT:
    if(x >= mvx){
      x = mvx;
    }else{
      x++;
    }
    break;
    case DOWN:
    if(y >= mvy){
      y = mvy;
    }else{
      y++;
    }
    break;
  }
}
};