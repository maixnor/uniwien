#include "standard_monster.h"

Standard_Monster::Standard_Monster(const std::string& name, unsigned health, unsigned attack)
    : Monster(name, health, attack) {}

unsigned Standard_Monster::calculate_damage(unsigned dmg) const {
    return dmg;
}

std::string Standard_Monster::additional_information() const {
    return "";
}

