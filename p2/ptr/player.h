#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>
#include <memory>
#include "hero.h"
#include "campaign.h"

class Player {
public:
    Player(const std::string& first_name, const std::string& last_name);

    unsigned create_hero(const std::string& name, Hero_Class hero_class, Hero_Species hero_species, unsigned max_hp, const std::map<std::string, unsigned>& abilities);
    void create_campaign(const std::string& name, unsigned min_level, unsigned id);
    void join_friends_campaign(Player& pfriend, unsigned id);
    void transfer_campaign(Player& pfriend);
    unsigned remove_dead();

    std::ostream& print_campaign(std::ostream& o) const;
    friend std::ostream& operator<<(std::ostream& o, const Player& p);

private:
    std::string first_name;
    std::string last_name;
    std::map<unsigned, std::shared_ptr<Hero>> heroes;
    std::unique_ptr<Campaign> campaign;
};

#endif // PLAYER_H

