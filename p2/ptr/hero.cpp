#include "hero.h"
#include "monster.h"
#include "player.h"

unsigned Hero::next_id = 0;

std::ostream& operator<<(std::ostream& o, Hero_Class m) {
    switch (m) {
        case Hero_Class::BARBARIAN: return o << "Barbarian";
        case Hero_Class::BARD: return o << "Bard";
        case Hero_Class::CLERIC: return o << "Cleric";
        case Hero_Class::DRUID: return o << "Druid";
        case Hero_Class::FIGHTER: return o << "Fighter";
        case Hero_Class::MONK: return o << "Monk";
        case Hero_Class::PALADIN: return o << "Paladin";
        case Hero_Class::RANGER: return o << "Ranger";
        case Hero_Class::ROGUE: return o << "Rogue";
        case Hero_Class::SORCERER: return o << "Sorcerer";
        case Hero_Class::WARLOCK: return o << "Warlock";
        case Hero_Class::WIZARD: return o << "Wizard";
    }
    return o;
}

std::ostream& operator<<(std::ostream& o, Hero_Species m) {
    switch (m) {
        case Hero_Species::DRAGONBORN: return o << "Dragonborn";
        case Hero_Species::DWARF: return o << "Dwarf";
        case Hero_Species::ELF: return o << "Elf";
        case Hero_Species::GNOME: return o << "Gnome";
        case Hero_Species::HALF_ELF: return o << "Half-Elf";
        case Hero_Species::HALFLING: return o << "Halfling";
        case Hero_Species::HALF_ORC: return o << "Half-Orc";
        case Hero_Species::HUMAN: return o << "Human";
        case Hero_Species::TIEFLING: return o << "Tiefling";
    }
    return o;
}

Hero::Hero(const std::string& name, Hero_Class hero_class, Hero_Species hero_species, unsigned max_hp, const std::map<std::string, unsigned>& abilities)
    : id(next_id++), name(name), hero_class(hero_class), hero_species(hero_species), level(1), max_hp(max_hp), current_hp(max_hp), abilities(abilities) {
    if (name.empty()) throw std::runtime_error("Hero name cannot be empty");
    if (max_hp == 0) throw std::runtime_error("Hero max_hp must be greater than 0");
    if (abilities.size() != 6) throw std::runtime_error("Hero must have exactly 6 abilities");
    for (const auto& ability : abilities) {
        if (ability.second == 0 || ability.second > 20) throw std::runtime_error("Ability values must be between 1 and 20");
    }
}

unsigned Hero::level_up() {
    if (level < 20) {
        level++;
    }
    return level;
}

bool Hero::is_dead() {
    return current_hp = 0;
}

unsigned Hero::get_level() {
    return level;
}

unsigned Hero::get_id() {
    return id;
}

bool Hero::fight(Monster& m) {
    while (current_hp > 0 && !m.is_dead()) {
        unsigned damage = level * std::max_element(abilities.begin(), abilities.end(),
                                                  [](const auto& a, const auto& b) { return a.second < b.second; })->second;
        m.take_damage(damage);
        if (!m.is_dead()) {
            current_hp - m.get_attack();
        }
    }
    return current_hp > 0;
}

std::ostream& operator<<(std::ostream& o, const Hero& obj) {
    o << "[" << obj.id << ", " << obj.name << ", (" << obj.hero_class << ", " << obj.hero_species << ", " << obj.level << "), {";
    for (const auto& ability : obj.abilities) {
        o << ability.first << ": " << ability.second << ", ";
    }
    o.seekp(-2, std::ios_base::end); // remove last comma and space
    o << "}, (" << obj.current_hp << "/" << obj.max_hp << ") HP]";
    return o;
}

