#pragma once
#include "obsvsbj.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <sstream>
class player : public observer
{
private:
  int x, y;

public:
  player(int stx = 0, int sty = 0)
  {
    x = stx;
    y = sty;
  }
  virtual void update(std::vector<std::string>& args) //i want to have like variadic ish arguments but oh well
  {
    // need to dissect the mesage - character 1 defines the direction and c2-3
    // the y and c4-5 the x
  
    
    
    ss2 << msg.substr(3, 4);
    int sy;
    ss1 >> sy;
    int sx;
    ss2 >> sx;
    switch (args[0].at(0)) {
      case 'u':
        y <= 0 ? y = 0 : y--;
        break;
      case 'l':
        x <= 0 ? x = 0 : x--;
        break;
      case 'r':
        x >= sx ? x = sx : x++;
        break;
      case 'd':
        y >= sy ? y = sy : y++;
        break;
    }
  }

  int gety() { return y; }
  int getx() { return x; }
};
