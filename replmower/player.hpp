#pragma once
#ifndef CURSES_INCLUDED
#include <curses.h>
#endif
#include "obsvsbj.hpp"

class player : public observer{
private:
int x, y;
public:
 player(int stx = 0, int sty = 0){
   x = stx;
   y = sty;
 }
virtual void update(std::string msg, WINDOW* mwin){
  int mvx, mvy;
  getmaxyx(mwin, mvy, mvx);
  
  //need to dissect the mesage - character 1 defines the direction and character 2 the units.
  switch(msg.at(0)){
    case 'u':
          y <= 0 ? y = 0 : y --;
    break;
    case 'l':
          x <= 0 ? x = 0 : x--;
    break;
    case 'r':
        x >= mvx ? x = mvx : x++;
    break;
    case 'd':
        y >= mvy ? y = mvy : y++;
    break;
  }
}

int gety(){return y;}
int getx(){return x;}
};
