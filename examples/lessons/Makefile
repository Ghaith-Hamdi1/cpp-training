# Builds every program under examples/lessons into build/.
#   make            build all
#   make clean      remove build/
# One file by hand:  g++ -std=c++20 -Wall -Wextra -pthread 07-multithreading/02_race_mutex_atomic.cpp -o race && ./race
CXX ?= g++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -pthread

SRCS := $(wildcard */*.cpp)
BINS := $(SRCS:%.cpp=build/%)

all: $(BINS)

build/%: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf build

.PHONY: all clean
