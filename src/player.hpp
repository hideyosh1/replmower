#pragma once
#include "obsvsbj.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <variant>
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
  void update(std::vector<std::variant<char, int>>& args) //i want to have like variadic ish arguments but oh well
  {
    // need to dissect the mesage - character 1 defines the direction and c2-3
    // the y and c4-5 the x
		char inp;
		try{
				inp = std::get<char>(args[0]);
		}catch{
			std::cout << "BAD ARG 1";
		}
		int sy;
		try{
			sy = std::get<int>(args[1]);
		}catch{
			std::cout << "BAD SCREEN DIMENSION";
		}
		int sx;
		try{
				sx = std::get<int>(args[2]);
		}catch{
				std::cout << "BAD SCREEN DIMENSION";
		}
    switch (inp) {
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
