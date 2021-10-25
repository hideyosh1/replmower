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
  std::vector<std::string> map1 = {{"44444", "43124", "44444"};
  //maybe use tmx?
	//for now we'll just set the maps up in this here file
	

  // return stuff
  map rmap;
  rmap.id = mid;
  rmap.data = map1;
  return rmap;
}