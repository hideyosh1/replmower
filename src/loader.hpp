#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "json.hpp"
#include "levelgen.hpp"

struct map
{
  int id;
  std::vector<std::string> data;
  std::vector<std::string> tips;
	int lastmap;
};
inline map loader(int mid)
{
	
	std::ifstream file("maps.json");
	map rmap;
	try{
		std::string thing;
		if(!file.is_open()) throw std::runtime_error("map file not found");
		nlohmann::json thej;
		std::ostringstream sstr;
		sstr << file.rdbuf();

		thing = sstr.str();

		thej = nlohmann::json::parse(thing);
		file.close();

		

		rmap.tips = thej["maps"][mid]["tips"].get<std::vector<std::string>>();
		rmap.data = thej["maps"][mid]["map"].get<std::vector<std::string>>();
		rmap.id = mid;
		rmap.lastmap = thej["end"].get<int>();

	}catch(nlohmann::json::parse_error& ex){
		rmap.tips ={"MAP PARSING ERROR!",
		ex.what()};
		rmap.data = {"42444"};
	}catch(std::runtime_error& ex){
		rmap.tips ={"FILE OPEN ERROR!",
		ex.what()};
		rmap.data = {"42444"};
	}
	

  
  return rmap;
}
map generatemap(int lvl){
	map outmap;
	outmap.data = default_levelgen(lvl);
	outmap.id = lvl;
	outmap.tips = {"this is a random level.", "level generation is under construction,", "so it may be broken."};
	outmap.lastmap = -2; //it'll never get to this value
	return outmap;
}
/*int getmagic(){
	std::ifstream ifile("maps.json"); // i'll probably turn maps file into a map.pak so people can't tell what it is without probing
}
*/
