CC = clang++

INCLUDES = -I/opt/homebrew/include -Iexternal
LDFLAGS = -L/opt/homebrew/lib
LIBS = -lSDL2

run:
	$(CC) main.cpp $(INCLUDES) $(LDFLAGS) $(LIBS) -o main
