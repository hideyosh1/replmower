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
inline map loader(int mid)
{
	
	std::ifstream file("maps.json");
	map rmap;
	try{
		nlohmann::json thej;
		std::ostringstream sstr;
		sstr << file.rdbuf();

		std::string thing = sstr.str();

		thej = nlohmann::json::parse(thing);
		file.close();

		

		rmap.tips = thej["maps"][mid]["tips"].get<std::vector<std::string>>();
		rmap.data = thej["maps"][mid]["map"].get<std::vector<std::string>>();
		rmap.id = mid;
	}catch(nlohmann::json::parse_error& ex){
		rmap.tips ={"ERROR!",
		ex.what()};
		rmap.data = {"42444"};
	}catch(nlohmann::json::out_of_range& exc){
		
	}
	
 
  
  return rmap;
}
/*int getmagic(){
	std::ifstream ifile("maps.json"); // i'll probably turn maps file into a map.pak so people can't tell what it is without probing
}
*/
