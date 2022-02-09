#include <iostream>
#ifndef CURSES_INCLUDED
#include <ncurses.h> 
#define CURSES_INCLUDED
#endif
#include "loader.hpp"
#include "player.hpp"
#include <string>
#include <chrono>
#include <memory>
//#include <filesystem>

void ending(std::vector<WINDOW*> windows);

int main() {
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, true);
  curs_set(0);

  int sx, sy, ch; // screen size and current character
  int lvl = 0;
	int lastlvl;

  bool playin = true;
  bool movin = false;
  bool complete = false;
	bool random_maps = false;

  getmaxyx(stdscr, sy, sx);
  std::chrono::steady_clock::time_point starttime;
  std::chrono::steady_clock::time_point endtime;

  // the keyboard subject and yeah it's a raw pointer but see the delete lmao

  map curmap;
	int sc = 1;
	
   /* we should change the size of sc depending on size of scy, scx in relation to the map
	but that would kinda suck and just be exactly like how it used to be so i have this amazing system which is divide\
	sy by a magic number decided upon by the map pack developer */
  int mx, my, qlastx, qlasty; // map x, y, quick lastx, quick last y,

  WINDOW *pwin = newwin(5, sx, sy - 5, 0);
  WINDOW *playwin = newpad(85, 61); // x 10 y 14
	WINDOW *boxwin = newwin(sy - 5, sx, 0, 0);
	

  notimeout(stdscr, TRUE);

  // nlines ncols starty startx
  player *mainc = new player(1, 0, sy - 7, sx - 2); // delete at the edn!!!

  subject keyb;
  keyb.addob(mainc);

  // hate raw pointers so....
 

  if (!has_colors()) {
    mvaddstr(0, 0,
             "hey there. we'd like to inform you that your terminal doesn't "
             "support color. thus, we will use black and white graphics "
             "characters. thank you!");
  } else {
    start_color();                       
    // foreground, background

    if (!can_change_color()) {
      mvaddstr(1, 0,
              "your terminal doesn't support changing colors. thus, we will use "
              "the eight default color characters. thank you!");
    }else{
        init_color(COLOR_GREEN, 137, 431, 1); //rgb
    }

    init_pair(1, COLOR_GREEN, COLOR_BLACK);  // gress
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); // player
    init_pair(3, COLOR_BLUE, COLOR_BLACK);   // end
    init_pair(4, COLOR_RED, COLOR_RED);      // death zone
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    // if you use black for the death zone it looks really bad because it jsut
    // blends into the background
  } // declare color pairs and stuff etc
  //"macros"
  const int GRASS = 1;
  const int PLAYER = 2;
  const int ENDINGPOINT = 3;
  const int DEATHZONE = 4;
  const int DOGS = 5;



  mvaddstr(2, 0, "press any key.");
  ch = getch();
  clear();
  refresh();

  mvaddstr(0, (sx - 13) / 2, "SUPERMOWER");
  mvaddstr(1, (sx - 10) / 2, "a game???");
  mvaddstr(10, (sx - 26) / 2, "by afureru/hideyosh1 2021");
	mvaddstr(6, (sx - 8) / 2, "campaign");
	mvaddstr(7, (sx - 12) / 2, "random maps");
	bool selected = false;
	do{ //honestly i need to make a separate header for this type of menu stuff
		
		ch = getch();

		switch(ch){
			case KEY_UP:
			case KEY_LEFT:
			case 'w':
			case 'a':
				random_maps = false;
				break;
			case KEY_DOWN:
			case KEY_RIGHT:
			case 'd':
			case 's':
				random_maps = true;
				break;
			case KEY_ENTER:
				selected = true;
				break;
			default:
				random_maps = false;
				break;

		}

		attron(A_REVERSE);
		if(!random_maps){
			mvaddstr(6, (sx - 8) / 2, "campaign");
			attroff(A_REVERSE);
			mvaddstr(7, (sx - 12) / 2, "random maps");
		}else{
			mvaddstr(7, (sx - 12) / 2, "random maps");
			attroff(A_REVERSE);
			mvaddstr(6, (sx - 8) / 2, "campaign");
		}
		
	}while(!selected);
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


  while (playin) {
    while (!movin) {
      
      
      starttime = std::chrono::steady_clock::now();
      
			//int scaley, scalex;
			box(boxwin, 0, 0);
			wrefresh(boxwin);
      complete = false;
      // loading
      // map size
      curmap = loader(lvl);
			!random_maps ? curmap = loader(lvl) : curmap = generatemap(lvl);
      my = curmap.data.size();
      mx = curmap.data[0].size();
			if(lvl + 1 == curmap.lastmap){
				//do ending sequence:
				ending({pwin, playwin, boxwin});
				clear();
				mvaddstr(0, (sx - 17) / 2, "you won the game!");
				mvaddstr(1, (sx - 24) / 2, "press any key to close.");

				refresh();

				ch = getch();
				endwin();
				return 0;
			}
      mainc->scy = my - 1; // because yk it starts at 0 but size starts at 1
      mainc->scx = mx - 1;

      // tips
      wclear(pwin);

      for (unsigned int i = 0; i < curmap.tips.size(); i++) {
				mvwaddstr(pwin, i + 1, 1, curmap.tips[i].c_str());
      }
			
      box(pwin, 0, 0);

      // getmaxyx(pwin, py, px);
		  //it's math time
			 //the amount of vertical whitespace is equal to my + 1
      //therefore we should subtract my + 1 from ply to get
  	   //the "true" value of scaley, same goes for horiz whitespace 
			 /*
			scaley = (ply - 2 - (my + 1)) / my; 
			scalex = (plx - 2 - (mx+ 1)) / mx; 
			scalex >= scaley ? sc = scaley : sc = scalex;*/

      for (int i = 0; i < my; i++) {
        for (int j = 0; j < mx; j++) {
          char rcoord = curmap.data[i].at(j);
          int tempint = rcoord - '0';
					chtype pchar;
          switch (tempint) {
          case GRASS:
            pchar = ACS_CKBOARD;
            break;
          case PLAYER:
            pchar = ACS_PI; //3blue1brown lol
						mainc->y = i;
            mainc->x = j;
            break;
          case ENDINGPOINT:
            pchar = '@';
            break;
          case DEATHZONE:
            pchar = ACS_BLOCK;
            break;
          case DOGS:
            pchar = '!';
            break;
          default:
            pchar = '@';
          }

          wattron(playwin, COLOR_PAIR(tempint));
          for (int k = 0; k < sc; k++) {
            for (int l = 0; l < sc; l++) {
              mvwaddch(
                  playwin, k + sc * i + 1 + i, sc * j + l + 1 + j,
                  pchar); // sc times the j which is the map x plus the current
                          // rendering coordinate plus one for the box
            }
            // alright
          }
          wattroff(playwin, COLOR_PAIR(tempint));
        } // given that i do use mvwaddch instead of the "simpler" waddch it
          // becomes more difficult for me to add extra lines but i can do it but
          // i also have to fix the one for rerendering the player which becomes
          // a little more challenging
      }
      movin = true;
    } // i literally put the end of the while(!moving) at the end of the program
      // so that's why it broke

		//math time(again)

		//we want the coordinate sc + 1 * mainc->gety(), sc + 1 * mainc->getx() to appear at the center so take those coordinates and subtract sy/2 and sx/2
		
    prefresh(playwin, // the playwin
                      // here are the pad coordinates
             (sc + 1) * mainc->gety() - (sy - 5) / 2,                 // upper left
             (sc + 1) * mainc->getx() - sx / 2, // upper left
             // here are the screen dimensions
             1,       // minimum row
             1,       // minimum col
             sy - 7,  // max row
             sx - 2); // max col also - 10 for minimap
						 // -1 each for box
		wrefresh(pwin);
    refresh();


    ch = getch();

    char msg;

    qlastx = mainc->getx();
    qlasty = mainc->gety();

    if (ch == 'e')
      break;
    switch (ch) { // direction movement
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
    case 'r':
      wclear(playwin);
      movin = false;
      complete = true;
      break;
    }
    keyb.update(msg);
				// level complete
			if (curmap.data[mainc->gety()].at(mainc->getx()) == '3') {
				// first check if there are green tiles left
				bool grasscleared = true;
				for (unsigned int i = 0; i < curmap.data.size(); i++) {
					for (unsigned int j = 0; j < curmap.data[0].length(); j++) {
						if (curmap.data[i][j] == '1') {
							grasscleared = false;
						}
					}
				}
				if (grasscleared) {
          
          endtime = std::chrono::steady_clock::now();
					wclear(pwin);
          wclear(playwin);
					
					box(pwin, 0, 0);
          mvwaddstr(pwin, 1, (sx - 16 - 2) / 2, "level complete!");
          mvwprintw(pwin, 2, (sx - 28 - 5) / 2, "you took %.2f seconds to complete.", //28 for "regular characters" and then 5 for the time (i.e. x.xx)
          std::chrono::duration_cast<std::chrono::duration<float>>(endtime - starttime).count());

					mvwprintw(pwin, 3, 1, "any key.");

					wrefresh(pwin);

          ch = getch();


					lvl++;
					lastlvl = lvl;

					movin = false;
					complete = true;
				}
			}
			if (!complete) {
				bool dogged = false;
				if (curmap.data[mainc->gety()].at(mainc->getx()) == '5') { // dogged
					movin = false;
					dogged =
							true; // ok so it'll skip rerendering and go back to the beginning
				} // originally i had it so dogged would appear after collision detection
					// which is bad because it'll never
				// actually work because collision only checks for '4'
				// weird but whatever

				// collision
				bool collided = false;
				if (curmap.data[mainc->gety()].at(mainc->getx()) == '4') {
					mainc->y = qlasty;
					mainc->x = qlastx; // so if you're not in the right place, go back
					collided = true;
				} else {
					curmap.data[qlasty][qlastx] = '4';
					curmap.data[mainc->gety()][mainc->getx()] = '2';
				}

				if ((!dogged) && (!collided)) { //originally checked for collided multiple times
					for (int i = 0; i < sc; i++) {
						for (int j = 0; j < sc; j++) {
								// void
								wattron(playwin, COLOR_PAIR(DEATHZONE));
								mvwaddch(playwin, qlasty * sc + 1 + i + qlasty,
												qlastx * sc + 1 + j + qlastx,
												'@'); // plus i the current rendering coordinate plus the
															// qlasty plus the sc plus 1 for box then plus
															// qlast(thing) which is the number of previous
															// vertical whitespaces i finaly understand
								wattroff(playwin, COLOR_PAIR(DEATHZONE));
							 // if we encounter void then it will render void first and then
								// itll render the player it's inefficient but oh well
							// player
							wattron(playwin, COLOR_PAIR(PLAYER));
							mvwaddch(playwin, mainc->gety() * sc + 1 + i + mainc->gety(),
											mainc->getx() * sc + 1 + j + mainc->getx(),
											ACS_PI); // y coordinate times scale plus 1 for box plus i for
							wattroff(playwin, COLOR_PAIR(PLAYER));

							// at this point y = qlasty and x = qlastx so skip rerendering the
							// void
						}
					}
				}
				// we still kinda need to reiterate but only slightly because of scaling
    }
  }
  ending({pwin, playwin, boxwin});
	endwin();
  return 0;
}

void ending(std::vector<WINDOW*> windows){
	for(WINDOW* selectwin : windows){
		wclear(selectwin);
		wrefresh(selectwin);
		wborder(selectwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
		delwin(selectwin);
	}
  // delthewins
  
	return;
}