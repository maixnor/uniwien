#ifndef STANDARD_MONSTER_H
#define STANDARD_MONSTER_H

#include "monster.h"

class Standard_Monster : public Monster {
public:
    Standard_Monster(const std::string& name, unsigned health, unsigned attack);

    unsigned calculate_damage(unsigned dmg) const override;
    std::string additional_information() const override;
};

#endif // STANDARD_MONSTER_H

