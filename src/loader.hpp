#pragma once
#include <fstream>
#include <iostream>
#include <vector>
enum
{
  map0,
  map1,
  map2,
  map3,
  map4,
  map5,
  map6,
  map7,
  map8
};
struct map
{
  int id;
  std::vector<std::string> data;
};
map loader(int mid)
{
	std::vector<std::string> map0 = {"44444", "43124", "44444"};
  std::vector<std::string> map1 = {"4444444", "4311114", "4111114", "4111114", "4111124"};//lets have the play area be 5 by 5 now
  std::vector<std::string> map2 = {"2111111111111", "1111111111111", "1111111111111", "1111111111111", "1111111111113"};

  //10ish levels?
  //4444444
  //4311114
  //4111114
  //4111114
  //4111124
	map rmap;
  rmap.id = mid;
  //maybe use tmx?
	//for now we'll just set the maps up in this here file
	switch(mid){
		case 0:
			rmap.data = map0;
    case 1:
      rmap.data = map1;
		default:
			rmap.data = map0;
	}

  // return stuff
  
  return rmap;
}