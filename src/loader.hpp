#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "json.hpp"

struct map
{
  int id;
  std::vector<std::string> data;
  std::vector<std::string> tips;
};
map loader(int mid)
{
	
	map rmap;
	try{
		nlohmann::json thej;
		std::ifstream file("maps.json");
		std::ostringstream sstr;
		sstr << file.rdbuf();

		std::string thing = sstr.str();

		thej = nlohmann::json::parse(thing);
		file.close();

		

		rmap.tips = thej["maps"][mid]["tips"].get<std::vector<std::string>>();
		rmap.data = thej["maps"][mid]["map"].get<std::vector<std::string>>();
		rmap.id = mid;
	}catch(...){
		rmap.tips ={"THIS IS AN ERROR MAP. PLEASE CONTACT THE DEVELOPER FOR HELP."};
		rmap.data = {"42444"};
	}
	
 
  
  return rmap;
}
int getmagic(){
	std::ifstream ifile("maps.json"); // i'll probably turn maps file into a map.pak so people can't tell what it is without probing
}
