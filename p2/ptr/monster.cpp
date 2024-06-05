#include "monster.h"

Monster::Monster(const std::string& name, unsigned health, unsigned attack)
    : name(name), health(health), attack(attack) {
    if (name.empty() || health == 0 || attack == 0) {
        throw std::runtime_error("Invalid Monster parameters");
    }
}

void Monster::take_damage(unsigned dmg) {
    unsigned calculated_damage = calculate_damage(dmg);
    if (calculated_damage > health) {
        health = 0;
    } else {
        health -= calculated_damage;
    }
}

bool Monster::is_dead() const {
    return health == 0;
}

unsigned Monster::get_attack() const {
	return attack;
}

std::ostream& operator<<(std::ostream& o, const Monster& h) {
  	if (h.additional_information() != "") {
		    o << "[" << h.name << ", " << h.health << " HP, " << h.attack << " ATK" << ", " << h.additional_information() << "]";
    }
  	else {
      	o << "[" << h.name << ", " << h.health << " HP, " << h.attack << " ATK" << "]";
    }
    return o;
}

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
    return std::to_string(defense) + " DEF";
}

Standard_Monster::Standard_Monster(const std::string& name, unsigned health, unsigned attack)
    : Monster(name, health, attack) {}

unsigned Standard_Monster::calculate_damage(unsigned dmg) const {
    return dmg;
}

std::string Standard_Monster::additional_information() const {
    return "";
}

