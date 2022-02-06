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

std::vector<std::string> default_levelgen(int lvl){
	std::vector<std::string> map;
	std::random_device seed;
	std::mt19937 gen(seed());
	
	std::uniform_int_distribution<std::mt19937::result_type> ydist(1, 8);
	std::uniform_int_distribution<std::mt19937::result_type> xdist(1, 10);
	std::uniform_int_distribution<std::mt19937::result_type> direction(1, 4);
	std::uniform_int_distribution<std::mt19937::result_type> walklength(1, 7);
	
	const int y = ydist(gen);
	const int x = xdist(gen);
	
	for(int i = 0; i < y; i++){
		for(int j = 0; j < x; j++){
			map[i].push_back('4');
		}
	}
	
	const int starty = ydist(gen);
	const int startx = xdist(gen);

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
				cursy = lasty;
				break;
			}
			if (cursx < 0){
				cursx = lastx;
				break;
			}
			if(cursy > y){
				cursy = lasty;
				break;
			}if(cursx > x){
				cursx = lastx;
				break;
			}if(map[cursy][cursx] != '4') break;
			map[cursy].at(cursx) = '1';
			//still som-e stuff to smooth out
		}
		return map;
	}
