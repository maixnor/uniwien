#ifndef HERO_H
#define HERO_H

#include <string>
#include <map>
#include <iostream>
#include <stdexcept>

class Monster; // Forward declaration

class Hero {
public:
    Hero(const std::string& name, Hero_Class hero_class, Hero_Species hero_species, unsigned max_hp, const std::map<std::string, unsigned>& abilities);
    
    unsigned level_up();
    bool fight(Monster& m);
    int get_id();
    
    friend std::ostream& operator<<(std::ostream& o, const Hero& obj);

private:
    unsigned id;
    std::string name;
    Hero_Class hero_class;
    Hero_Species hero_species;
    unsigned level;
    unsigned max_hp;
    unsigned current_hp;
    std::map<std::string, unsigned> abilities;

    static unsigned next_id;
};

#endif // HERO_H

