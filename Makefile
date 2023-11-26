INCLUDES = -I/opt/homebrew/include -Iexternal

LDFLAGS = -L/opt/homebrew/lib
LIBS = -lSDL2

CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Ofast

CXX_SRCS := $(shell find src -name "*.cpp")
CXX_OBJS := ${patsubst src/%.cpp,build/%.o,${CXX_SRCS}}

.PHONY: run clean

run: main ../LLM-responses/LLM-responses.json

main: $(CXX_OBJS)
	@echo "Building executable..."
	${CXX} $(INCLUDES) ${CXXFLAGS} $(LIBS) $(LDFLAGS) ${CXX_OBJS} -o main

../LLM-responses/LLM-responses.json: ../LLM-responses/generate.py
	@echo "Generating LLM-responses.json..."
	cd ../LLM-responses && python3 generate.py

build/%.o: src/%.cpp
	mkdir -p ${dir $@}
	@echo "Building $@..."
	${CXX} -o $@ $< $(INCLUDES) ${CXXFLAGS} -c

clean:
	rm -rf build
