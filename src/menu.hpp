#pragma once
#include <iostream>
#include <vector>
#ifndef CURSES_INCLUDED
#include <ncurses.h>
#define CURSES_INCLUDED
#endif
//no highlight logic bec boring
class item{
private:
	std::string name;

public:
	item(std::string itemname){
		name = itemname;
		selected = false;
	}
	bool acceptselection(){
		return true;
	}
	
}
class menu{
private:
	int sizex, sizey, posx, posy;
	unsigned short choice;
	std::vector<item> items;
public:
	menu(int x, int y, int px, int py){
		sizex = x;
		sizey = y;
		px = posx;
		py = posy;
	}
	void render(WINDOW* inputwin){
		inputwin = newwin(sizey, sizex, py, px);
		box(inputwin, 0, 0);
		wrefresh(inputwin);
	}
	bool select(char dir){
		do{
			switch(dir){
				case 'u':
					choice = 0 ? choice = 0 : choice--;
				case 'd':
					choice >= items.size() - 1 ? choice = items.size();
			}
		}while(!items[choice].acceptselection());
	}
}