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
		std::string thing;
		if(!file) throw std::runtime_error;
		nlohmann::json thej;
		std::ostringstream sstr;
		sstr << file.rdbuf();

		thing = sstr.str();

		thej = nlohmann::json::parse(thing);
		file.close();

		

		rmap.tips = thej["maps"][mid]["tips"].get<std::vector<std::string>>();
		rmap.data = thej["maps"][mid]["map"].get<std::vector<std::string>>();
		rmap.id = mid;
	}catch(json::parse_error& ex){
		rmap.tips ={"ERROR!",
		ex.what()};
		rmap.data = {"42444"};
	}catch(std::runtime_error& ex){
		rmap.tips ={"ERROR!",
		ex.what()};
		rmap.data = {"42444"};
	}catch(...){
		std::cerr << "fatal error!";
		exit(-1);
	}
	

  
  return rmap;
}
int endloader(std::string mapfile){
	std::ifstream file(mapfile);
	
	file.close();
}
/*int getmagic(){
	std::ifstream ifile("maps.json"); // i'll probably turn maps file into a map.pak so people can't tell what it is without probing
}
*/
