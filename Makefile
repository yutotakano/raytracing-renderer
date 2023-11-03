INCLUDES = -I/opt/homebrew/include -Iexternal

LDFLAGS = -L/opt/homebrew/lib
LIBS = -lSDL2

CXX = clang++
CXXFLAGS = -std=c++17 $(LIBS)

CXX_SRCS := $(shell find src -name "*.cpp")
CXX_OBJS := ${patsubst %.cpp,build/%.o,${CXX_SRCS}}

main: $(CXX_OBJS)
	@echo "Building executable..."
	${CXX} $(INCLUDES) ${CXXFLAGS} $(LDFLAGS) ${CXX_OBJS} -o main

build/%.o : %.cpp
	mkdir -p ${dir $@}
	@echo "Building $@..."
	${CXX} -o $@ $< $(INCLUDES) ${CXXFLAGS} -c

clean :
	rm -rf build
