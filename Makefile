OBJS	= main.o
SOURCE	= src/main.cpp
HEADER	= src/json.hpp src/loader.hpp src/obsvsbj.hpp src/player.hpp
OUT	= supermower.exe
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lncurses

all: $(OBJS)
	$(CC) $(FLAGS) -o $(OUT) $(LFLAGS)


clean:
	rm -f $(OBJS) $(OUT)
  
