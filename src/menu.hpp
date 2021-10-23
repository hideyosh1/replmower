#pragma once
#include <iostream>
#include <vector>
class menuopt{
private:
    int id;
    std::string name;
    int lastid;
public:
    menuopt(int acid, std::string acname){
        id = acid;
        name = acname;
    }
    bool newopt(std::string optname){
        
        lastid++;
    }
};
class menu{
private:
    std::vector<menuopt*> options;
public:
    ~menu(){
        for(menuopt* i : options){
            delete i;
        }
    }
    
};