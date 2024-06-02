#include "elite_monster.h"

Elite_Monster::Elite_Monster(const std::string& name, unsigned health, unsigned attack, unsigned defense)
    : Monster(name, health, attack), defense(defense) {
    if (defense == 0) {
        throw std::runtime_error("Invalid Elite Monster defense");
    }
}

unsigned Elite_Monster::calculate_damage(unsigned dmg) const {
    if (dmg <= defense) {
        return 0;
    }
    return dmg - defense;
}

std::string Elite_Monster::additional_information() const {
    return ", defense " + std::to_string(defense);
}

