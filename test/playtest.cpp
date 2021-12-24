/*#include <iostream>
#include <fstream>
#include <vector>
#include <random>

int main(){
	//pick a random value between 3 and 14 and 3 and 10 for x and y
	//then fill in the whole screen with void
	//place the player coordinate at the top left
	//the rule is that every tile must have two adjacent tiles otherwise it's impossible for the player to move
	std::default_random_engine nice;
	std::uniform_int_distribution<int> disty(3, 14);
	std::uniform_int_distribution<int> distx(3, 10);
	int mapy = disty(nice);
	int mapx = distx(nice);

	std::vector<std::string> map;
	map.resize(mapy, "");
	for(int i = 0; i < mapy; i++){
		for(int j = 0; j < mapx; j++){
			map[i].push_back('4');
		}
	}
	std::ofstream out("out.txt");
	for(int i = 0; i < map.size(); i++){
		out << map[i] << "\n";
	}
	out.close();
}*/

#include <iostream>
#include <vector>
#include <random>
int main(){ //this is an idea on how tog enerate a map.
//111
//441
//1111
//maps should be "chunky": no separated floating parts are allowed. so we can define
//several "chunk" variants like 
//44
//44 and
//44
//41 and go from there.

//chunks
/*
44
41

44
44

14
44

41
44 etc
*/

	std::vector<std::string> map; //level number determines the map size
	std::vector<std::string> chunk;

	std::default_random_engine rand;
	std::uniform_int_distribution<int> distribution(1, 14);
	switch(distribution(rand)){
		case 1:
			chunk = {"44", "44"};
			break;
		case 2:
			chunk = {"44", "41"};
			break;
		case 3:
			chunk = {"44", "14"};
			break;
		case 4:
			chunk = {"14", "44"};
			break;
		case 5:
			chunk = {"41", "44"};
			break;
		case 6:
			chunk = {"11", "44"};
			break;
		case 7:
			chunk = {"44", "11"};
			break;
		case 8:
			chunk = {"14", "14"};
			break;
		case 9:
			chunk = {"41", "41"};
			break;
		case 10:
			chunk = {"11", "14"};
			break;
		case 11:
			chunk = {"11", "41"};
			break;
		case 12:
			chunk = {"14", "11"};
			break;
		case 13:
			chunk = {"41", "11"};
			break;
		case 14:
			chunk = {"11, 11"};
			break;
		default:
			chunk = {"44", "44"};
	}
	std::cout << chunk[0] << chunk[1];
	char nice;
	std::cin >> nice;
}