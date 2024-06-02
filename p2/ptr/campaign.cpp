#include "campaign.h"
#include "hero.h"
#include "monster.h"

Campaign::Campaign(const std::string& name, unsigned min_level) : name(name), min_level(min_level) {
    if (name.empty()) throw std::runtime_error("Campaign name cannot be empty");
    if (min_level == 0) throw std::runtime_error("Campaign min_level must be greater than 0");
}

void Campaign::add_hero(std::shared_ptr<Hero> h) {
    if (!h || h->get_level() < min_level || heroes.count(h->get_id()) > 0) {
        throw std::runtime_error("Cannot add hero to campaign");
    }
    heroes[h->get_id()] = h;
}

void Campaign::encounter_monster(unsigned id, Monster& m) {
    auto it = heroes.find(id);
    if (it != heroes.end()) {
        if (auto hero = it->second.lock()) {
            if (hero->fight(m)) {
                hero->level_up();
            }
        }
    }
}

unsigned Campaign::remove_dead_and_expired() {
    unsigned removed = 0;
    for (auto it = heroes.begin(); it != heroes.end();) {
        if (auto hero = it->second.lock()) {
            if (hero->is_dead()) {
                it = heroes.erase(it);
                removed++;
            } else {
                ++it;
            }
        } else {
            it = heroes.erase(it);
            removed++;
        }
    }
    return removed;
}

std::ostream& operator<<(std::ostream& o, const Campaign& p) {
    o << "[" << p.name << " Campaign, Min_Level " << p.min_level << ", {";
    for (const auto& entry : p.heroes) {
        if (auto hero = entry.second.lock()) {
            o << *hero << ", ";
        }
    }
    o.seekp(-2, std::ios_base::end); // remove last comma and space
    o << "}]";
    return o;
}

