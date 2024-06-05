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
    std::string get_name() const;
    unsigned get_attack() const;
  	unsigned get_health() const;
    virtual std::string additional_information() const = 0;

    friend std::ostream& operator<<(std::ostream& o, const Monster& h);

private:
    std::string name;
    unsigned health;
    unsigned attack;
};

class Elite_Monster : public Monster {
public:
    Elite_Monster(const std::string& name, unsigned health, unsigned attack, unsigned defense);

    unsigned calculate_damage(unsigned dmg) const override;
    std::string additional_information() const override;

private:
    unsigned defense;
};

class Standard_Monster : public Monster {
public:
    Standard_Monster(const std::string& name, unsigned health, unsigned attack);

    unsigned calculate_damage(unsigned dmg) const override;
    std::string additional_information() const override;
};

// Deklaration von Task3
class Task3 : public Elite_Monster {
public:
    Task3(const std::string& name, unsigned health, unsigned attack, unsigned defense);

    unsigned calculate_damage(unsigned dmg) const override;
};

#endif // MONSTER_H

