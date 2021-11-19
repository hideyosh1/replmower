#pragma once
#include <iostream>
#include <vector>
#include <list>
class player
{
private:
  int x, y, scy, scx;
public:
  player(int stx, int sty, unsigned short sy, unsigned short sx)
  {
    x = stx;
    y = sty;
		scy = sy;
		scx = sx;
  }
	void update(char arg) //tbh if you have a screen size > 255 then you have a problem
  {
    // need to dissect the mesage - character 1 defines the direction and c2-3
    // the y and c4-5 the x
		std::cout << y;
		std::cout << x;

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
    }std::cout << x;
		std::cout << y;
  }

  int gety() { return y; }
  int getx() { return x; }
};

int main(){
	player* np = new player(3, 3, 0, 0);
	std::string nice;
	std::cin >> nice;
	np->update(nice.at(0));
}