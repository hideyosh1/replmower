OBJS	= main.o
SOURCE	= src/main.cpp
HEADER	= src/json.hpp src/loader.hpp src/obsvsbj.hpp src/player.hpp
OUT	= supermower.exe
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lncurses
INCLUDES = D:\proj\libs\boost_1_77_0

all: $(OBJS)
	$(CC) -I $(INCLUDES) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: src/main.cpp
	$(CC) -I $(INCLUDES) $(FLAGS) src/main.cpp $(LFLAGS)


clean:
	rm -f $(OBJS) $(OUT)
  
