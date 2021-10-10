#pragma once
#include "json.hpp"
#include <iostream>
#include <vector>
#include <fstream>
enum{
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
struct map{
  int id;
  std::vector<std::string> data;
};
map loader(int mid){
  std::ifstream i("maps.json");
  nlohmann::json j;
  i >> j;
  //load from the json file

  char temp = mid + 48;
  std::string tmp;
  tmp.push_back(temp);

  std::vector<std::string> tmap = j["maps"]["tmp"]; //data

  //return stuff
  return (mid, tmap);
}