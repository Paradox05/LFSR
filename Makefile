CC = g++ -std=c++0x
CFLAGS = -Wall -Werror -ansi -pedantic -g

all: photomagic

photomagic: photomagic.o LFSR.o
		$(CC) $(FLAGS) -o photomagic photomagic.o LFSR.o -lsfml-graphics -ls fml-window -lsfml-system
photomagic.o: photomagic.cpp LFSR.cpp LFSR.hpp
		$(CC) $(FLAGS) -c photomagic.cpp

LFSR.o: LFSR.cpp LFSR.hpp
		$(CC) $(FLAGS) -c LFSR.cpp

clean:
		rm -rf photomagic *.o *.