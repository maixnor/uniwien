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
    o << "[" << h.name << ", " << h.health << " HP, " << h.attack << " ATK" << h.additional_information() << "]";
    return o;
}

