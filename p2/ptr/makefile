CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
OBJS = main.o

all: HeroGame

HeroGame: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o HeroGame
