CC = clang++

INCLUDES = -I/opt/homebrew/include -Iexternal
LDFLAGS = -L/opt/homebrew/lib
LIBS = -lSDL2

run:
	$(CC) -std=c++17 src/main.cpp $(INCLUDES) $(LDFLAGS) $(LIBS) -o main
