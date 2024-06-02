#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <ostream>

class Monster {
public:
    Monster(const std::string& name, unsigned health, unsigned attack);
    virtual ~Monster() = default;

    virtual unsigned calculate_damage(unsigned dmg) const = 0;
    void take_damage(unsigned dmg);
    bool is_dead() const;
    virtual std::string additional_information() const = 0;

    friend std::ostream& operator<<(std::ostream& o, const Monster& h);

protected:
    std::string name;
    unsigned health;
    unsigned attack;
};

#endif // MONSTER_H

