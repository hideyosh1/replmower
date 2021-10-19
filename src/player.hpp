#pragma once
#include <iostream>
#include "obsvsbj.hpp"
#include <sstream>

class player : public observer{
private:
int x, y;
public:
 player(int stx = 0, int sty = 0){
   x = stx;
   y = sty;
 }
virtual void update(std::string msg){
  //need to dissect the mesage - character 1 defines the direction and c2-3 the y and c4-5 the x
 std::stringstream ss1;
 ss1 << msg.substr(1, 2);
 std::stringstream ss2;
 ss2 << msg.substr(3, 4); 
 int sy;
 ss1 >> sy;
 int sx;
 ss2 >> sx;
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
