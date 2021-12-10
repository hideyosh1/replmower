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

	notimeout(stdscr, TRUE);


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
    init_pair(3, COLOR_GREEN, COLOR_BLACK);    // end 
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
	mvwaddstr(pwin, 2, 1, "to move around, use the arrow keys or WASD.");			
	mvwaddstr(pwin, 3, 1, "to win, mow all green tiles.");																					
  wrefresh(pwin);
  refresh();

  subject *keyb = new subject;
  keyb->addob(mainc);
  // the keyboard subject and yeah it's a raw pointer but see the delete lmao
  bool movin = false;
	bool complete = false;
	map curmap;
	int mx, my;
  while (playin) {
    while (!movin) {
			complete = false;
			box(playwin, 0, 0);
      // loading
			 // map size
			curmap = loader(lvl);
      my = curmap.data.size();
      mx = curmap.data[0].size();
      mainc->scy = my;
			mainc->scx = sx;
			
			int* scaley = new int;
			int* scalex = new int;

			*scaley = (sy - 7) / my; // magic numbers are muy stinky so i'll getmaxyx later
			*scalex = (sx - 7) / mx;
			if(*scalex >= *scaley){
				sc = *scaley;
			}else{
				sc = *scalex;
			}

			delete scaley;
			delete scalex;

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
						for(int l = 0; l < sc; l++){
								mvwaddch(playwin, k + sc * i + 1, sc * j + l + 1, '@'); //sc times the j which is the map x plus the current rendering coordinate plus one for the box
						}
					}
					wattroff(playwin, COLOR_PAIR(tempint));
				}
			}
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
				//first check if there are green tiles left
				bool grasscleared = true;
				for(int i = 0; i < curmap.data.size(); i++){
					for(int j = 0; j < curmap.data[0].length(); j++){
						if(curmap.data[i][j] == '1'){
							grasscleared = false;
						}
					}
				}
				if(grasscleared){
					lvl++;
					wclear(playwin);
					wrefresh(playwin);
					refresh();

					movin = false;
					complete = true;
				}
        
      }
			if(!complete){
					//collision
				bool collided = false;
				if (curmap.data[mainc->gety()].at(mainc->getx()) == '4') {
					mainc->y = *qlasty;
					mainc->x = *qlastx; // so if you're not in the right place, go back
					collided = true;
				}else{
					curmap.data[*qlasty][*qlastx] = '4';
					curmap.data[mainc->gety()][mainc->getx()] = '2';
				}
				
				// we shouldn't redraw/reiterate because that is for children only we need to only update the player
				//add 1 for box
				//idk why it crashes
				for(int i = 0; i < sc; i++){
					for(int j = 0; j < sc; j++){
						//player
						wattron(playwin, COLOR_PAIR(2));
						mvwaddch(playwin, mainc->gety() * sc + 1 + i, mainc->getx() * sc + 1 + j, '@');
						wattroff(playwin, COLOR_PAIR(2));
						//at this point y = qlasty and x = qlastx so skip rerendering the void

						if(!collided){
							//void
							wattron(playwin, COLOR_PAIR(4));
							mvwaddch(playwin, *qlasty * sc + 1 + i, *qlastx * sc + 1 + j, '@');
							wattroff(playwin, COLOR_PAIR(4));
						}
						
					}
				}

				//we still kinda need to reiterate but only slightly because of scaling
				delete qlasty;
				delete qlastx; //using raw pointers is stupid but because we delete them it's probably fine
				
				wrefresh(playwin);
				refresh();
				}
				
			
  }
	endwin();
	
}
