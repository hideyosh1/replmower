#pragma once
#include <iostream>
#include <vector>
#ifndef CURSES_INCLUDED
#include <curses.h>
#endif
class observer{
  public:
  virtual void update(std::string msg) = 0;
};
class subject{
  private:
  std::vector<observer*> obslist;
  public:
  void addob(observer* obsv){
    obslist.push_back(obsv);
  }
  void remob(observer* obsv){
    for(unsigned int i = 0; i < obslist.size(); i++){
      if(obslist[i] == obsv) obslist.erase(obslist.begin() + i + 1); //istg it pulls the index by 1234
    }
  }
  void update(std::string msg, WINDOW* gamewin){
    for(unsigned int i = 0; i < obslist.size(); i++) obslist[i]->update(msg);
  }

};
