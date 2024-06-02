CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
OBJS = campaign.o elite_monster.o hero.o monster.o player.o standard_monster.o tasks.o main.o

all: HeroGame

HeroGame: $(OBJS)
    $(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp %.h
    $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
    rm -f *.o HeroGame