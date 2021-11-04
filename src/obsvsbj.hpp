#pragma once
#include <iostream>
#include <vector>
#ifndef CURSES_INCLUDED
#include <curses.h>
#endif
#include <tuple>
class observer
{
public:
  virtual void update(std::string msg) = 0;
	virtual void update(std::tuple<char, unsigned short, unsigned short>& args) = 0;
};
class subject
{
private:
  std::vector<observer*> obslist;

public:
  virtual void addob(observer* obsv) { obslist.push_back(obsv); }
  virtual void remob(observer* obsv)
  {
    for (unsigned int i = 0; i < obslist.size(); i++) {
      if (obslist[i] == obsv)
        obslist.erase(obslist.begin() + i +
                      1); // istg it pulls the index by 1234
    }
  }
  void update(std::string& msg)
  {
    for (unsigned int i = 0; i < obslist.size(); i++)
      obslist[i]->update(args);
  }
	void update(std::tuple<char, unsigned short, unsigned short>& args){
		for (unsigned int i = 0; i < obslist.size(); i++)
      obslist[i]->update(args);
  }
	void update(char args){
		for (unsigned int i = 0; i < obslist.size(); i++)
      obslist[i]->update(args);
  }
	}
};
