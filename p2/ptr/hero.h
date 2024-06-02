#ifndef HERO_H
#define HERO_H

#include <string>
#include <map>
#include <iostream>
#include <stdexcept>
#include "monster.h"

enum class Hero_Class { BARBARIAN, BARD, CLERIC, DRUID, FIGHTER, MONK, PALADIN, RANGER, ROGUE, SORCERER, WARLOCK, WIZARD };
enum class Hero_Species { DRAGONBORN, DWARF, ELF, GNOME, HALF_ELF, HALFLING, HALF_ORC, HUMAN, TIEFLING };

class Hero {
public:
    Hero(const std::string& name, Hero_Class hero_class, Hero_Species hero_species, unsigned max_hp, const std::map<std::string, unsigned>& abilities);
    
    unsigned level_up();
    bool fight(Monster& m);
    bool is_dead();
    unsigned get_level();
    unsigned get_id();
    
    friend std::ostream& operator<<(std::ostream& o, const Hero& obj);

    friend std::ostream& operator<<(std::ostream& o, const Hero_Class& obj);
    friend std::ostream& operator<<(std::ostream& o, const Hero_Species& obj);

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

