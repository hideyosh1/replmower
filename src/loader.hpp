#pragma once
#include <iostream>
#include <vector>
#include <string>

struct map
{
  int id;
  std::vector<std::string> data;
  std::vector<std::string> tips;
};
map loader(int mid)
{
	std::vector<std::string> map0 = {"44444444",
																	 "42111134",
																	 "44444444"};
	std::vector<std::string> tip0 = {"welcome to super mower!", // box characters cover it up                                           // up
          "to move around, use the arrow keys or WASD.",		
          "to win, mow all green tiles and get to the blue tile."};


	std::vector<std::string> map1 = {"44444", 
																	 "41124", 
																	 "41114", 
																	 "43444", 
																	 "44444"};
	std::vector<std::string> tip1 = {"you can't move on red tiles.", 
	"when you move, you can't go back, so choose wisely!",
	"press r to reset the map."};


	std::vector<std::string> map2 = {"44444444", 
																	 "41112314", 
																	 "41111114", 
																	 "41144444", 
																	 "44444444"};
	std::vector<std::string> tip2 = {"this one is a little more tricky!"};


	std::vector<std::string> map3 = {"4444444444", 
									 "4111111124", 
									 "4111111114", 
									 "4114441114", 
									 "4113111114",
									 "4444444444"};
	std::vector<std::string> tip3 = {"don't rush through this one."};

	std::vector<std::string> map4 = {"444444444",
																	 "421151154",
																	 "411111134"}; // 5 = dogs
	std::vector<std::string> tip4 = {"this map features dogs. be careful not to mow around them!"};
	
	std::vector<std::string> tip5 = {"this map features grass grenades that will reset your progress."};
	
	map rmap;
  rmap.id = mid;
  //maybe use tmx?
	//for now we'll just set the maps up in this here file
	switch(mid){
		case 0:
			rmap.data = map0;
			rmap.tips = tip0;
		break;
		case 1:
			rmap.data = map1;
			rmap.tips = tip1;
		break;
		case 2:
			rmap.data = map2;
			rmap.tips = tip2;
			break;
		case 3:
			rmap.data = map3;
			rmap.tips = tip3;
		break;
		case 4:
			rmap.data = map4;
			rmap.tips = tip4;
		break;
		default:
			rmap.data = map0;
			rmap.tips = tip0;
	}

  // return stuff
  
  return rmap;
}


