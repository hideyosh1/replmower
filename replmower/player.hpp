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
virtual void update(std::string msg){
  int mvx, mvy;
  getmaxyx(stdscr, mvy, mvx);

  //need to dissect the mesage - character 1 defines the direction and character 2 the units.
  switch(msg.at(0)){
    case 'u':
          if(y <= 0){
            y = 0;
          }else{
            y--;
          }
    break;
    case 'l':
        if(x <= 0){
            x = 0;
          }else{
            x--;
          }
    break;
    case 'r':
        if(x >= mvx){
          x = mvx;
        }else{
          x++;
        }
    break;
    case 'd':
        if(y >= mvy){
          y = mvy;
        }else{
          y++;
        }
    break;
  }
}

};