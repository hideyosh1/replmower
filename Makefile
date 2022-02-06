
SOURCE	= src/main.cpp src/resources.res
HEADER	= src/json.hpp src/loader.hpp src/obsvsbj.hpp src/player.hpp
OUT	= bin/supermower.exe
CC	 = g++
FLAGS	 = -g -Wall -I/../proj/msys/mingw64/include/ncurses #use o3 for releasze
RFLAGS = -Wall -o3 -I/../proj/msys/mingw64/include/ncurses
LFLAGS	 = -lncurses

all: 
	$(CC) $(FLAGS) $(SOURCE) -o $(OUT) $(LFLAGS)
	cp src/maps.json bin

fastdebug:
	$(CC) $(FLAGS) -o2 $(SOURCE) -o $(OUT) $(LFLAGS) # i dont use o3 because it's too annoying
	cp src/maps.json bin

release:
	$(CC) $(RFLAGS) $(SOURCE) -o $(OUT) $(LFLAGS)

clean:
	rm -f $(OBJS) $(OUT)
	
