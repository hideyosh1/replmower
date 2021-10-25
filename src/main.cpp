#include <iostream>
#ifndef CURSES_INCLUDED
#include <ncurses.h>
#endif
#include "loader.hpp"
#include "player.hpp"
#include <memory>
#include <sstream>
#include <string>
// #include <boost/dll/runtime_symbol_info.hpp>
//#include <filesystem>

void prblock(int cpair, WINDOW* prwin);
// nice and clean
int main()
{
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, true);

  int sx, sy, ch;
  int lvl = 0;
  bool loading = false;
  bool playin = true;
  const char block = (char)219;
  getmaxyx(stdscr, sy, sx);

  WINDOW* pwin = newwin(5, sx, sy - 5, 0);
  WINDOW* playwin = newwin(sy - 5, sx, 0, 0);

  // nlines ncols starty startx
  player* mainc = new player; // delete at the edn!!!
  // hate raw pointers so....

  if (!has_colors()) {
    mvaddstr(0,
             0,
             "hey there. we'd like to inform you that your terminal doesn't "
             "support color. thus, we will use black and white graphics "
             "characters. thank you!");
  } else {
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK); // player
    init_pair(2, COLOR_GREEN, COLOR_BLACK);  // gress
    init_pair(3, COLOR_RED, COLOR_BLACK);    // endpoint
    init_pair(4, COLOR_BLACK, COLOR_BLACK); //death zone
  }
  if (!can_change_color()) {
    mvaddstr(1,
             0,
             "your terminal doesn't support changing colors. thus, we will use "
             "the eight default color characters. thank you!");
  }
  mvaddstr(2, 0, "press any key.");
  ch = getch();
  clear();
  refresh();

  mvaddstr(0, (sx - 13) / 2, "SUPERMOWERMAN");
  mvaddstr(1, (sx - 10) / 2, "a game???");
  ch = getch();

  /*bool titling = false;
  std::filesystem::path savep = "options.json";
  do{
    if(std::filesystem::exists(savep)){
      mvaddstr(4, (sx - 9) / 2, "continue");
    }
    mvaddstr(5, (sx - 9) / 2, "new game");
  }while(!titling);*/
  
  clear();
	
  refresh();

  box(pwin, 0, 0);
  box(playwin, 0, 0);
  wrefresh(pwin);
  wrefresh(playwin);

  mvwaddstr(pwin, 1, 1, "welcome to super mower!"); // box characters cover it
                                                    // up

  subject* keyb = new subject;
  keyb->addob(mainc);
    // the keyboard subject and yeah it's a raw pointer but see the delete lmao
  bool movin = false;
  while (playin) {
    int mx, my; // map size
    while (!movin) {
      // loading
      map curmap = loader(lvl);
      my = curmap.data.size();
      mx = curmap.data[0].size();
      int sc;
      ((int)sy / my >= (int)sx / mx) ? sc = sy / my : sc = sx / mx;

      // rendering

      move(0, 0);
      // new functional version also pyramid of doom :(
      for (int i = 0; i < my; i++) {
        for (int j = 0; j < mx; j++) {
          char specoord = curmap.data[i].at(j);
          if ((specoord != '0') && (specoord != '1') && (specoord != '2'))
            return 1;
          for (int s = 0; s < sc; s++) {
            int tempint = specoord - '0';
            prblock(tempint + 1, playwin);
          }
          waddch(playwin, '\n');
        }

        movin = true;
	wrefresh(playwin);
	refresh();
      }

      ch = getch();

      std::string msg = "";
      curmap.data[mainc->gety()].at(mainc->getx()) = '4';
      
      int *qlastx = new int;
      int *qlasty = new int; //quick last player coordinates
      *qlastx = mainc->getx();
      *qlasty = mainc->gety();
      
      switch (ch) { //direction movement 
        case 'e':
          wborder(pwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
					wborder(playwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
					delwin(pwin);
					delwin(playwin);
					delete keyb;
					delete mainc;
					// delthewins
					endwin();
					exit(0);
          break;
        case 'w':
          msg.push_back('u');
          break;
        case 'a':
          msg.push_back('l');
          break;
        case 's':
          msg.push_back('d');
          break;
        case 'd':
          msg.push_back('r');
          break;
      }
      std::stringstream ss;
      ss << my << mx;
      msg.append(ss.str());
      keyb->update(msg);

      // level complete
      if (curmap.data[mainc->gety()].at(mainc->getx()) == '3') {
        lvl++;
        movin = false;
      }
      if(curmap.data[mainc->gety()].at(mainc->getx()) == '4'){
        std::string wcmsg = ""; //worst case msg
        int tempy = *qlasty - mainc->gety();
        int tempx = *qlastx - mainc->getx();
        std::stringstream s2;
        
        switch (tempx) {
        case -1:
          msg.push_back('r');
          break;
        case 1:
          msg.push_back('l');
          break;
        }
        switch(tempy) {
        case 1:
          msg.push_back('d');
          break;
        case -1:
          msg.push_back('u');
          break;
        }
        s2 << my << mx;
        
        wcmsg.append(s2.str());
        keyb->update(wcmsg);
      }
      curmap.data[mainc->gety()].at(mainc->getx()) = '1';
      wmove(playwin, 0, 0);

      // kinda good?

      int* thex = new int;
      int* they = new int;
      *they = 0;
			
      // may or mayn't be correct
      for (int i = 0; i < my; i++) {
        *thex = 0;
        for (int j = 0; j < mx; j++) {
          char specoord = curmap.data[i].at(j);
          if ((specoord != '0') && (specoord != '1') && (specoord != '2'))
            return 1;
          bool sptrue;
          for (int s = 0; s < sc; s++) {
            if (specoord == '1') {
              prblock(1, playwin);
            } else {
              wmove(playwin, *they, (*thex)++);
              (*thex)++;
            }
          }
          waddch(playwin, '\n');
          (*they)++;
        }
        delete thex;
        delete they;
      }
	    wrefresh(playwin);
	    refresh();
    }
  }
}
void prblock(int cpair, WINDOW* prwin)
{
  wattron(prwin, COLOR_PAIR(cpair));
  waddch(prwin, (char)219);
  wattroff(prwin, COLOR_PAIR(cpair));
}

// yeah it's an archaic goto and bad practice and silly but it's getting out of
// the endless loop so
