CC = g++ -std=c++17
CFLAGS = -Wall -Werror -pedantic -g
INCLUDE_PATH = -I/opt/homebrew/Cellar/sfml/2.6.1/include
LIBRARY_PATH = -L/opt/homebrew/Cellar/sfml/2.6.1/lib

all: photomagic photomagicdecrypt

photomagic: photomagic.o LFSR.o
	$(CC) $(CFLAGS) $(INCLUDE_PATH) $(LIBRARY_PATH) -o photomagic photomagic.o LFSR.o -lsfml-graphics -lsfml-window -lsfml-system

photomagicdecrypt: photomagicdecrypt.o LFSR.o
	$(CC) $(CFLAGS) $(INCLUDE_PATH) $(LIBRARY_PATH) -o photomagicdecrypt photomagicdecrypt.o LFSR.o -lsfml-graphics -lsfml-window -lsfml-system

photomagic.o: photomagic.cpp LFSR.hpp
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -c photomagic.cpp

photomagicdecrypt.o: photomagicdecrypt.cpp LFSR.hpp
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -c photomagicdecrypt.cpp

LFSR.o: LFSR.cpp LFSR.hpp
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -c LFSR.cpp

clean:
	rm -rf photomagic photomagicdecrypt *.o *.dSYM
