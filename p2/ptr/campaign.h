#ifndef CAMPAIGN_H
#define CAMPAIGN_H

#include <string>
#include <map>
#include <memory>
#include <stdexcept>

class Campaign {
public:
    Campaign(const std::string& name, unsigned min_level);

    void add_hero(std::shared_ptr<Hero> h);
    void encounter_monster(unsigned id, Monster& m);
    unsigned remove_dead_and_expired();

    friend std::ostream& operator<<(std::ostream& o, const Campaign& p);

private:
    std::string name;
    std::map<unsigned, std::weak_ptr<Hero>> heroes;
    unsigned min_level;
};

#endif // CAMPAIGN_H

