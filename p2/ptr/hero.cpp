#include "hero.h"
#include "monster.h"
#include "player.h"

unsigned Hero::next_id = 0;

Hero::Hero(const std::string& name, Hero_Class hero_class, Hero_Species hero_species, unsigned max_hp, const std::map<std::string, unsigned>& abilities)
    : id(next_id), name(name), hero_class(hero_class), hero_species(hero_species), level(1), max_hp(max_hp), current_hp(max_hp), abilities(abilities) {
    if (name.empty()) throw std::runtime_error("Hero name cannot be empty");
    if (max_hp == 0) throw std::runtime_error("Hero max_hp must be greater than 0");
    if (abilities.size() != 6) throw std::runtime_error("Hero must have exactly 6 abilities");
    for (const auto& ability : abilities) {
        if (ability.second == 0 || ability.second > 20) throw std::runtime_error("Ability values must be between 1 and 20");
    }
    ++next_id;
}

unsigned Hero::level_up() {
    if (level < 20) {
        level++;
    }
    return level;
}

bool Hero::is_dead() {
    return current_hp <= 0;
}

unsigned Hero::get_level() {
    return level;
}

unsigned Hero::get_id() {
    return id;
}

Hero_Class Hero::get_class() {
    return hero_class;
}

std::ostream& Hero::print(std::ostream& o) const{
    o << "[" << this->id << ", " << this->name << ", (";
    o << this->hero_class << ", ";
    o << this->hero_species << ", " << this->level << "), {";
    std::map<std::string, unsigned>help = abilities;
    auto it =  help.begin();
    while(it != help.end()) {
        o << it->second;
        it++;
        if(it != help.end()) {
            o << ", ";
        }
    }
    o << "}, (" << this->current_hp << "/" << this->max_hp << ") HP]";
    return o;
}

bool Hero::fight(Monster& m) {
    while (current_hp > 0 && !m.is_dead()) {
        unsigned damage = level * std::max_element(abilities.begin(), abilities.end(),
                                                  [](const auto& a, const auto& b) { return a.second < b.second; })->second;
        m.take_damage(damage);
        if (!m.is_dead()) {
          	if (m.get_attack() > current_hp) {
              	current_hp = 0;
            } else {
            		current_hp = current_hp - m.get_attack();
            }
        }
    }
    return current_hp > 0;
}

std::ostream& operator<<(std::ostream& o, const Hero& obj) {
    return obj.print(o);
}

std::ostream& operator<<(std::ostream& o, const Hero_Class& m) {
    switch (m) {
        case Hero_Class::BARBARIAN: o << "Barbarian"; break;
        case Hero_Class::BARD: o << "Bard"; break;
        case Hero_Class::CLERIC: o << "Cleric"; break;
        case Hero_Class::DRUID: o << "Druid"; break;
        case Hero_Class::FIGHTER: o << "Fighter"; break;
        case Hero_Class::MONK: o << "Monk"; break;
        case Hero_Class::PALADIN: o << "Paladin"; break;
        case Hero_Class::RANGER: o << "Ranger"; break;
        case Hero_Class::ROGUE: o << "Rogue"; break;
        case Hero_Class::SORCERER: o << "Sorcerer"; break;
        case Hero_Class::WARLOCK: o << "Warlock"; break;
        case Hero_Class::WIZARD: o << "Wizard"; break;
    }
    return o;
}

std::ostream& operator<<(std::ostream& o, const Hero_Species& m) {
    switch (m) {
        case Hero_Species::DRAGONBORN: o << "Dragonborn"; break;
        case Hero_Species::DWARF: o << "Dwarf"; break;
        case Hero_Species::ELF: o << "Elf"; break;
        case Hero_Species::GNOME: o << "Gnome"; break;
        case Hero_Species::HALF_ELF: o << "Half-Elf"; break;
        case Hero_Species::HALFLING: o << "Halfling"; break;
        case Hero_Species::HALF_ORC: o << "Half-Orc"; break;
        case Hero_Species::HUMAN: o << "Human"; break;
        case Hero_Species::TIEFLING: o << "Tiefling"; break;
    }
    return o;
}

