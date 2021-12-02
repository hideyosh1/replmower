#include <iostream>
#ifndef CURSES_INCLUDED
#include <ncurses.h>
#endif
#include "loader.hpp"
#include "player.hpp"
#include <string>
#include <locale>
// #include <boost/dll/runtime_symbol_info.hpp>
//#include <filesystem>

// nice and clean
int checksc(int x, int y, int sx, int sy, int scale = 1);
int main() {
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, true);

  int sx, sy, ch; //screen size and current character
  int lvl = 0;
  bool playin = true;
  getmaxyx(stdscr, sy, sx);
	int sc;

  WINDOW *pwin = newwin(5, sx, sy - 5, 0);
  WINDOW *playwin = newwin(sy - 5, sx, 0, 0);

  // nlines ncols starty startx
  player *mainc = new player(1, 0, sy - 7, sx - 2); // delete at the edn!!!
	
  // hate raw pointers so....

  if (!has_colors()) {
    mvaddstr(0, 0,
             "hey there. we'd like to inform you that your terminal doesn't "
             "support color. thus, we will use black and white graphics "
             "characters. thank you!");
  } else {
    start_color(); //foreground, background
    init_pair(1, COLOR_GREEN, COLOR_BLACK ); // gress
    init_pair(2, COLOR_YELLOW, COLOR_BLACK );  // player
    init_pair(3, COLOR_CYAN, COLOR_BLACK);    // end 
    init_pair(4, COLOR_RED, COLOR_BLACK);  // death zone
		//if you use black for the death zone it looks really bad because it jsut blends into the background
  }//declare color pairs and stuff etc 
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
		map curmap;
    int mx, my; // map size
    while (!movin) {
      // loading
			curmap = loader(lvl);
      my = curmap.data.size();
      mx = curmap.data[0].size();
      mainc->scy = my;
			mainc->scx = sx;
			
			int* scaley = new int;
			int* scalex = new int;

			*scaley = (sy - 7) / my;
			*scalex = (sx - 7) / mx;
			if(*scalex >= *scaley){
				sc = *scaley;
			}else{
				sc = *scalex;
			}

			delete scaley;
			delete scalex;

			int* rendery = new int;
			*rendery = 0;
			for(int i = 0; i < my; i++){
				for(int j = 0; j < mx; j++){
					char rcoord = curmap.data[i].at(j);
					int tempint = rcoord - '0';
					if(rcoord == '2'){
						mainc->y = i;
						mainc->x = j;
					}
					wattron(playwin, COLOR_PAIR(tempint));
					for(int k = 0; k < sc; k++){
						++rendery;
						for(int l = 0; l < sc; l++){
								mvwaddch(playwin, *rendery, sc * j + l, '@'); //sc times the j which is the map x plus the current rendering coordinate
						}
					}
					wattroff(playwin, COLOR_PAIR(tempint));
				}
			}
			
      /*// rendering
			int *rendery = new int;
			*rendery = 0;
      // new functional version also pyramid of doom :(
      for (int i = 0; i < my; i++) { //this is really dumb also it renders vertically instead of horizontally
        std::string curstr = curmap.data[i];
				wmove(playwin, 1, ++*rendery); 
        for (int j = 0; j < mx; j++) {
          char specoord = curstr.at(j);
          int tempint = specoord - '0';
					if(specoord == '2'){
						mainc->y = i;
						mainc->x = j;
					}
					wattron(playwin, COLOR_PAIR(tempint));
          for (int s = 0; s < sc; s++) {
            waddch(playwin, '@');
          }
					wattroff(playwin, COLOR_PAIR(tempint));
          
        }waddch(playwin, '\n');//im very stupid bc i thought id actually implemented color but it turns out i didn't like all of the colors are the same which is why i was having trouble with seing if my collision stuff worked	
      }
			*/
			delete rendery; 
      movin = true;
		} //i literally put the end of the while(!moving) at the end of the program so that's why it broke
      wrefresh(playwin);
      refresh();

      ch = getch();

      char msg;

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
        // delthewins
        endwin();
        exit(0);
        break;
			case KEY_UP:
      case 'w':
        msg = ('u');
        break;
			case KEY_LEFT: // i didn't even know you could do this
      case 'a':
        msg = ('l');
        break;
			case KEY_DOWN:
      case 's':
        msg = ('d');
        break;
			case KEY_RIGHT:
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
			
      curmap.data[mainc->gety()].at(mainc->getx()) = '2';



      // we shouldn't redraw/reiterate because that is for children only we need to only update the player
			//add 1 for box
			for(int i = 0; i < sc; sc++){
				for(int j = 0; j < sc; sc++){
					//player
					wattron(playwin, COLOR_PAIR(2));
					mvwaddch(playwin, mainc->gety() + 1 + i, mainc->getx() + 1 + j, '@');
					wattroff(playwin, COLOR_PAIR(2));

					//grass
					wattron(playwin, COLOR_PAIR(4));
					mvwaddch(playwin, *qlasty + 1 + i, *qlastx + 1 + j, '@');
					wattroff(playwin, COLOR_PAIR(4));
				}
			}

			//we still kinda need to reiterate but only slightly because of scaling
			delete qlasty;
			delete qlastx; //using raw pointers is stupid but because we delete them it's probably fine
			
      wrefresh(playwin);
      refresh();
    
  }
}
int checksc(int x, int y, int sx, int sy, int scale) { //if scale isn't optimal, return correct scale; otherwise, 
														//return
	if (x == 0 || y == 0 || sx == 0 || sy == 0) {
		exit(1);
	}
	if (((x * scale > sx) && (x * (scale - 1) < sx)) || ((y * scale > sy) && (y * (scale - 1) < sy))) {
		return scale - 1;
	}
	if ((x * scale > sx) || (y * scale > sy)) {
		return checksc(x, y, sx, sy, scale - 1);
	}
	else if ((x * scale < sx) || (y * scale < sy)) {
		return checksc(x, y, sx, sy, scale + 1);
	}
	return 0;
}
