#include <iostream>
#ifndef CURSES_INCLUDED
#include <ncurses.h>
#endif
#include "loader.hpp"
#include "player.hpp"
#include <string>
#include <chrono>
// #include <boost/dll/runtime_symbol_info.hpp>
//#include <filesystem>

// nice and clean
int main() {
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

  WINDOW *pwin = newwin(5, sx, sy - 5, 0);
  WINDOW *playwin = newwin(sy - 5, sx, 0, 0);

  // nlines ncols starty startx
  player *mainc = new player(0, 0, sy - 7, sx - 2); // delete at the edn!!!
  // hate raw pointers so....

  if (!has_colors()) {
    mvaddstr(0, 0,
             "hey there. we'd like to inform you that your terminal doesn't "
             "support color. thus, we will use black and white graphics "
             "characters. thank you!");
  } else {
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_YELLOW); // gress
    init_pair(2, COLOR_BLACK, COLOR_GREEN);  // player
    init_pair(3, COLOR_BLACK, COLOR_RED);    // end
    init_pair(4, COLOR_BLACK, COLOR_BLACK);  // death zone
  }
  if (!can_change_color()) {
    mvaddstr(1, 0,
             "your terminal doesn't support changing colors. thus, we will use the eight default color characters. thank you!");
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
  wrefresh(pwin);
  refresh();
  ch = getch();

  subject *keyb = new subject;
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

      // because box
      if ((int)(sy - 7) / my >=
          (sx - 2) / mx) { // i forgot that playwin size is smaller than stdscr
        sc = (sy - 7) / my;
      } else {
        sc = (sx - 7) / mx;
      }
      // rendering

      wmove(playwin, 1, 1);
      // new functional version also pyramid of doom :(
      for (int i = 0; i < my; i++) {
        std::string curstr = curmap.data[i];
        for (int j = 0; j < mx; j++) {
          char specoord = curstr.at(j);
          int tempint = specoord - '0' + 1;
          for (int s = 0; s < sc; s++) {
            wattron(playwin, COLOR_PAIR(1));
            waddch(playwin, 219);
            wattroff(playwin, COLOR_PAIR(1));
          }
          waddch(playwin, '\n');
        }

        movin = true;
      }
      wrefresh(playwin);
      refresh();

      ch = getch();

      char msg;
      curmap.data[mainc->gety()].at(mainc->getx()) = '4';

      int *qlastx = new int;
      int *qlasty = new int; // quick last player coordinates
      *qlastx = mainc->getx();
      *qlasty = mainc->gety();

      switch (ch) { // direction movement
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
        msg = ('u');
        break;
      case 'a':
        msg = ('l');
        break;
      case 's':
        msg = ('d');
        break;
      case 'd':
        msg = ('r');
        break;
      }

      keyb->update(msg);

      // level complete
      if (curmap.data[mainc->gety()].at(mainc->getx()) == '3') {
        lvl++;
        movin = false;
      }
			//collision
      if (curmap.data[mainc->gety()].at(mainc->getx()) == '4') {
        int tempy = *qlasty - mainc->gety();
        int tempx = *qlastx - mainc->getx();

        switch (tempx) {
        case -1:
          msg = 'r';
          break;
        case 1:
          msg = 'l';
          break;
        }
        switch (tempy) {
        case 1:
          msg = 'd';
          break;
        case -1:
          msg = 'u';
          break;
        }
        keyb->update(msg);
      }
      curmap.data[mainc->gety()].at(mainc->getx()) = '1';
      wmove(playwin, 0, 0);

      // we shouldn't redraw/reiterate because that is for children only we need to only update the player
			mvwaddch(playwin, mainc->gety() + 1, mainc->getx() + 1, (char)219);
			mvwaddch(playwin, *qlasty + 1, *qlastx + 1, (char) 219);//add 1 for box
			delete qlasty;
			delete qlastx; //using raw pointers is stupid but because we delete them it's probably fine
			
      wrefresh(playwin);
      refresh();
    }
  }
}
