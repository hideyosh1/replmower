OBJS	= main.o
SOURCE	= main.cpp
HEADER	= json.hpp loader.hpp obsvsbj.hpp player.hpp
OUT	= supermower
CC	 = g++
FLAGS	 = -g -c -Wall -lncurses
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 


clean:
	rm -f $(OBJS) $(OUT)