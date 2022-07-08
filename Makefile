CC = g++
LFLAGS = -lX11
SRC = src/main.cpp src/keys.cpp
OBJ = $(SRC:.c=.o)

eza: $(OBJ)
	$(CC) $(LFLAGS) -o eza $(OBJ)

clean:
	rm -rf eza $(OBJ)

main.o: main.cpp
	$(CC) -c main.cpp

keys.o: keys.cpp
	$(CC) -c keys.cpp
