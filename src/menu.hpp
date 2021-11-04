#pragma once
#include <iostream>
#include <vector>
#include "obsvsbj.hpp"
//no highlight logic bec boring

class menu : observer{
private:
    std::vector<std::string>* options;
		int id;
public:
		menu(int newid){
			id = newid;
		}
    ~menu(){
				delete options;
    }
		bool attach(const std::string& input){
			options.push_back(input);
		}
		int getid(){ return id; }
		void update(char args) override{
			switch (args) {
      case 'u':
        id <= 0 ? id = 0 : id--;
        break;
      case 'd':
        id >= options.size() ? id = options.size() : id++;
        break;
    	}
		}
};