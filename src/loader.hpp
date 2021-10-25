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
  
  //maybe use tmx?

  char temp = mid + 48;
  std::string tmp;
  tmp.push_back(temp);

  std::vector<std::string> tmap = j["maps"]["0"]; // data

  // return stuff
  map rmap;
  rmap.id = mid;
  rmap.data = tmap;
  return rmap;
}