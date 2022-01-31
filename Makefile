
SOURCE	= src/main.cpp
HEADER	= src/json.hpp src/loader.hpp src/obsvsbj.hpp src/player.hpp
OUT	= bin/supermower.exe
CC	 = g++
FLAGS	 = -g -Wall -I/../proj/msys/mingw64/include/ncurses #use o3 for releasze
RFLAGS = -Wall -o3 -I/../proj/msys/mingw64/include/ncurses
LFLAGS	 = -lncurses

all: 
	$(CC) $(FLAGS) $(SOURCE) -o $(OUT) $(LFLAGS)

fastdebug:
	$(CC) $(FLAGS) -o2 $(SOURCE) -o $(OUT) $(LFLAGS) # i dont use o3 because it's too annoying

release:
	$(CC) $(RFLAGS) $(SOURCE) -o $(OUT) $(LFLAGS)

clean:
	rm -f $(OBJS) $(OUT)
  
