#include "hero.h"
#include "monster.h"
#include "player.h"

unsigned Hero::next_id = 0;

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

int Hero::get_id() {
    return id;
}

bool Hero::fight(Monster& m) {
    while (current_hp > 0 && !m.is_dead()) {
        unsigned damage = level * std::max_element(abilities.begin(), abilities.end(),
                                                  [](const auto& a, const auto& b) { return a.second < b.second; })->second;
        m.take_damage(damage);
        if (!m.is_dead()) {
            take_damage(m.attack);
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

