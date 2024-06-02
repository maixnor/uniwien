#ifndef ELITE_MONSTER_H
#define ELITE_MONSTER_H

#include "monster.h"

class Elite_Monster : public Monster {
public:
    Elite_Monster(const std::string& name, unsigned health, unsigned attack, unsigned defense);

    unsigned calculate_damage(unsigned dmg) const override;
    std::string additional_information() const override;

private:
    unsigned defense;
};

#endif // ELITE_MONSTER_H

