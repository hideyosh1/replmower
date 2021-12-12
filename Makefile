OBJS	= main.o
SOURCE	= src/main.cpp
HEADER	= src/json.hpp src/loader.hpp src/obsvsbj.hpp src/player.hpp
OUT	= bin/supermower.exe
CC	 = g++
FLAGS	 = -g -Wall -I/../msys/mingw64/include/ncurses
LFLAGS	 = -lncurses

all: $(OBJS)
	$(CC) $(FLAGS) $(SOURCE) -o $(OUT) $(LFLAGS)


clean:
	rm -f $(OBJS)
  
