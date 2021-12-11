#pragma once
#include <fstream>
#include <iostream>
#include <vector>

struct map
{
  int id;
  std::vector<std::string> data;
};
map loader(int mid)
{
	std::vector<std::string> map0 = {"43124"};
	std::vector<std::string> map1 = {"44444", 
																	 "41124", 
																	 "41114", 
																	 "43444", 
																	 "44444"};
	std::vector<std::string> map2 = {"44444444", 
																	 "41112314", 
																	 "41111114", 
																	 "41144444", 
																	 "44444444"};
	std::vector<std::string> map3 = {"4444444444", 
																	 "4111111124", 
																	 "4431441444", 
																	 "4111111114", 
																	 "4114111114"};
	map rmap;
  rmap.id = mid;
  //maybe use tmx?
	//for now we'll just set the maps up in this here file
	switch(mid){
		case 0:
			rmap.data = map0;
		case 1:
			rmap.data = map1;
		case 2:
			rmap.data = map2;
		default:
			rmap.data = map0;
	}

  // return stuff
  
  return rmap;
}