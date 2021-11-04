#pragma once
#include <iostream>
#include <vector>
//no highlight logic bec boring
class menuopt{
private:
    int id;
    std::string name;
    int lastid;
public:
    menuopt(int acid = lastid, std::string acname){
				lastid = 0;
        id = acid;
        name = acname;
				lastid++;
    }
};
class menu{
private:
    std::vector<menuopt*> options;
		int id;
public:
		menu(int newid){
			id = newid;
		}
    ~menu(){
        for(menuopt* i : options){
            delete i;
        }
    }
		bool attach(menuopt* input){
			options.push_back(input);
		}
    bool changesel(char input){
			switch (input) {
      case 'u':
        id <= 0 ? id = 0 : id--;
        break;
      case 'd':
        id >= options.size() ? id = options.size() : id++;
        break;
    	}
		}
		int getid(){ return id; }
};