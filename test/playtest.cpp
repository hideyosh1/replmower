#include <iostream>
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
}