//the algorithm now:
//start a new map with random size (constrained by pad size)
//set start point at random place
//for the "difficulty level" determined by the level number:
	//set a random direction (up, down, left right)
	//set a random moving distance
	//move in the direction for the moving distance
	//if it collides with a previous path restart from the last valid direction.
	//if it collides with the level boundaries don't restart and just break moving and start anew.
//at the final step mark it as '3'.
#include <random>
#include <vector>
#include <iostream>
#include <cmath>

std::vector<std::string> default_levelgen(int lvl){
	
	const double pi = 3.14159265359;
	std::random_device seed;
	std::mt19937 gen(seed());
	
	std::uniform_int_distribution<std::mt19937::result_type> ydist(1, 8);
	std::uniform_int_distribution<std::mt19937::result_type> xdist(3, 10);
	std::uniform_int_distribution<std::mt19937::result_type> direction(1, 4);
	std::uniform_int_distribution<std::mt19937::result_type> walklength(1, 7);
	
	const int y = round((atan(lvl - 3) + pi / 2) * 3.1); //check in desmos 
	const int x = xdist(gen); //difficulty (map size) increases linearly but can never exceed map size, use arctan
	
	std::string line = "";
	for(int i = 0; i < x; i++){
		line.push_back('4');
	}
	std::vector<std::string> map(y, line); //idk why it segfaults (woops deja vu)
	
	
	
	const int starty = y - 1; 
	const int startx = x - 1; //forgot we do starting from 0 right

  map[starty][startx] = '2';
	
	int cursy = starty;
	int cursx = startx;
	
	for(int i = 0; i < lvl % 5 + 5; i++){ //SORRY for using modulos i just want a nice curve yk
		int dir = direction(gen);
		int walkl = walklength(gen);
		
		for(int j = 0; j < walkl; j++){
			int lasty = cursy;
			int lastx = cursx;
			switch(dir){
				case 1:
					//up
					cursy--;
					break;
				case 2:
					//down
					cursy++;
					break;
				case 3:
					//left
					cursx--;
					break;
				case 4:
					//right
					cursx++;
					break;
				default:
					//up
					cursy--;
					break;
					
			}
			if(cursy < 0){
				cursy = 0;
				break;
			}
			if (cursx < 0){
				cursx = 0;
				break;
			}
			if(cursy > y - 1){
				cursy =y - 1;
				break;
			}if(cursx > x - 1){
				cursx = x - 1;
				break;
			}
      if(map[cursy].at(cursx) != '4'){
				cursx = lastx;
				cursy = lasty;
				break;
			} 
			map[cursy].at(cursx) = '1';
			//still som-e stuff to smooth out
		}
		
	}
	map[cursy].at(cursx) = '3';
	return map;
}