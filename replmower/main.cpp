#include <iostream>
#ifndef CURSES_INCLUDED
#include <curses.h>
#endif
#include <memory>
#include <popl.hpp>
#include <map>
#include "player.hpp"
#include "loader.hpp"
#include "obsvsbj.hpp"

int checksc(int x, int y, int sx, int sy, int scale);
//nice and clean
int main() {
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, true);

  int sx, sy, ch;
  int lvl = 0;
  bool loading = false;
  const char block = (char) 219;
  getmaxyx(stdscr, sy, sx);

  WINDOW* pwin = newwin(5, sx, sy-5, 0); 
  WINDOW* playwin = newwin(sy-5, sx, 0, 0);
  
  //nlines ncols starty startx
  player* mainc = new player; //delete at the edn!!!
  //hate raw pointers so....
  
  if(!has_colors()){
    mvaddstr(0, 0, "hey there. we'd like to inform you that your terminal doesn't support color. thus, we will use black and white graphics characters. thank you!";
  }else{
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK); // player
    init_pair(2, COLOR_GREEN, COLOR_BLACK); //gress
    init_pair(3, COLOR_RED, COLOR_BLACK); //endpoint
  }
  if(!can_change_color()){
    mvaddstr(1, 0, "your terminal doesn't support changing colors. thus, we will use the eight default color characters. thank you!");
  }
  mvaddstr(2, 0, "press any key.");
  ch = getch();
  clear();
  refresh();

  mvaddstr(0, (sx-13)/2, "SUPERMOWERMAN");
  mvaddstr(1, (sx-10)/2, "a game???");
  mvaddstr(2, (sx-7)/2, "any key");
  ch = getch();
  clear();
  refresh();
    std::cout<< sx << sy << ch << block;
    box(pwin, 0, 0);
    box(playwin, 0, 0);
    wrefresh(pwin);
    wrefresh(playwin);

    mvwaddstr(pwin, 1, 1, "welcome to super mower!"); //box characters cover it up

    

    subject* keyb = new subject;
    keyb->addob(mainc);
    //the keyboard subject and yeah it's a raw pointer but see the delete lmao
    bool movin = false;
    while (playin) {
        int mx, my; //map size
        while(!movin){
          //loading
          map curmap = loader(lvl);
          my = map.data.size();
          mx = map.data[0].size();
          int sc = checksc(mx, my, sx, sy, 5);
          //rendering
          
          move(0, 0);
          /**for(int s = 0; s < sc; s++){
            for(int i = 0; i < mx; i++){
                for(int j = 0; j < my; j++){
                  //take a look at the specified coordinate
                  char specoord = map.data[j].at(i);


                  switch(specoord){
                    case '0':
                      //print green
                      attron(COLOR_PAIR(1));
                      waddch(playwin, block);
                      attron(COLOR_PAIR(1));
                      break;
                    case '1':
                      //print brown for player
                      attron(COLOR_PAIR(2));
                      waddch(playwin, block);
                      attron(COLOR_PAIR(2));
                      break;
                    case '2':
                      //print endpoint
                      attron(COLOR_PAIR(3));
                      waddch(playwin, block);
                      attroff(COLOR_PAIR(3));
                      break;
                      /**reminder to print it by the amount of the goddamn scale**/
                  }
                }
              }
            }**/
             //new functional version also pyramid of doom :(
             for(int i = 0; i < my; i++){
              for(int j = 0; j < mx; j++){
                char specoord = map.data[i].at(j);
                for(int s = 0; s < sc; s++{
                  switch(specoord){
                    case '0':
                      //print green
                      prblock(1, playwin);
                      break;
                    case '1':
                      //print brown for player
                      prblock(2, playwin);
                      break;
                    case '2':
                      //print endpoint
                      prblock(3, playwin);
                      break;
                }
                waddch(playwin, '\n);
               }
             }
          
          movin = true;
        }
        
        ch = getch();
        switch (ch) {
        case 'e':
            goto del;
            break;
        case 'w':
            keyb->update("u");
            break;
        case 'a':
            keyb->update("l");
            break;
        case 's':
            keyb->update("d");
            break;
        case 'd':
            keyb->update("r");
            break;
        }

  }
del:
    wborder(pwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wborder(playwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    delwin(pwin);
    delwin(playwin);
    delete keyb;
    delete mainc;
    //delthewins
    endwin();
    exit(0);
//yeah it's an archaic goto and bad practice and silly but it's getting out of the endless loop so

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
}void prblock(int cpair, WINDOW* prwin){
  wattron(prwin, COLOR_PAIR(cpair));
  waddch(prwin, (char) 219);
  wattroff(prwin, COLOR_PAIR(cpair));
}
