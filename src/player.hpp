#pragma once
#include "obsvsbj.hpp"
#include <iostream>
#include <vector>
#include <list>
class player : public observer
{
private:
  int x, y, scy, scx;
public:
  player(int stx, int sty, int sy, int sx)
  {
    x = stx;
    y = sty;
		scy = sy;
		scx = sx;
  }
	void update(char arg) override //tbh if you have a screen size > 255 then you have a problem
  {
    // need to dissect the mesage - character 1 defines the direction and c2-3
    // the y and c4-5 the x
    switch (arg) {
      case 'u':
        y <= 0 ? y = 0 : y--;
        break;
      case 'l':
        x <= 0 ? x = 0 : x--;
        break;
      case 'r':
        x >= scx ? x = scx : x++;
        break;
      case 'd':
        y >= scy ? y = scy : y++;
        break;
			//forcefully change xys 
			case '0':
				y = 2;
				x = 2;
				break;
    }
  }

  int gety() { return y; }
  int getx() { return x; }
};
