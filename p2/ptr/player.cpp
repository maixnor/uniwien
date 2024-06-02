#include "player.h"
#include "hero.h"
#include "campaign.h"

enum class Hero_Class { BARBARIAN, BARD, CLERIC, DRUID, FIGHTER, MONK, PALADIN, RANGER, ROGUE, SORCERER, WARLOCK, WIZARD };
enum class Hero_Species { DRAGONBORN, DWARF, ELF, GNOME, HALF_ELF, HALFLING, HALF_ORC, HUMAN, TIEFLING };

std::ostream& operator<<(std::ostream& o, Hero_Class m) {
    switch (m) {
        case Hero_Class::BARBARIAN: return o << "Barbarian";
        case Hero_Class::BARD: return o << "Bard";
        case Hero_Class::CLERIC: return o << "Cleric";
        case Hero_Class::DRUID: return o << "Druid";
        case Hero_Class::FIGHTER: return o << "Fighter";
        case Hero_Class::MONK: return o << "Monk";
        case Hero_Class::PALADIN: return o << "Paladin";
        case Hero_Class::RANGER: return o << "Ranger";
        case Hero_Class::ROGUE: return o << "Rogue";
        case Hero_Class::SORCERER: return o << "Sorcerer";
        case Hero_Class::WARLOCK: return o << "Warlock";
        case Hero_Class::WIZARD: return o << "Wizard";
    }
    return o;
}

std::ostream& operator<<(std::ostream& o, Hero_Species m) {
    switch (m) {
        case Hero_Species::DRAGONBORN: return o << "Dragonborn";
        case Hero_Species::DWARF: return o << "Dwarf";
        case Hero_Species::ELF: return o << "Elf";
        case Hero_Species::GNOME: return o << "Gnome";
        case Hero_Species::HALF_ELF: return o << "Half-Elf";
        case Hero_Species::HALFLING: return o << "Halfling";
        case Hero_Species::HALF_ORC: return o << "Half-Orc";
        case Hero_Species::HUMAN: return o << "Human";
        case Hero_Species::TIEFLING: return o << "Tiefling";
    }
    return o;
}

Player::Player(const std::string& first_name, const std::string& last_name)
    : first_name(first_name), last_name(last_name) {
    if (first_name.empty() || last_name.empty()) throw std::runtime_error("Player name cannot be empty");
}

unsigned Player::create_hero(const std::string& name, Hero_Class hero_class, Hero_Species hero_species, unsigned max_hp, const std::map<std::string, unsigned>& abilities) {
    auto hero = std::make_shared<Hero>(name, hero_class, hero_species, max_hp, abilities);
    unsigned id = hero->get_id();
    heroes[id] = hero;
    return id;
}

void Player::create_campaign(const std::string& name, unsigned min_level, unsigned id) {
    if (campaign) {
        campaign.reset();
    }
    campaign = std::make_unique<Campaign>(name, min_level);
    auto it = heroes.find(id);
    if (it == heroes.end() || it->second->get_level() < min_level) {
        throw std::runtime_error("Cannot create campaign with specified hero");
    }
    campaign->add_hero(it->second);
}

void Player::join_friends_campaign(Player& pfriend, unsigned id) {
    if (!pfriend.campaign) {
        throw std::runtime_error("Friend does not have a campaign");
    }
    auto it = heroes.find(id);
    if (it == heroes.end()) {
        throw std::runtime_error("Hero does not exist");
    }
    pfriend.campaign->add_hero(it->second);
}

void Player::transfer_campaign(Player& pfriend) {
    if (!campaign) {
        throw std::runtime_error("No campaign to transfer");
    }
    if (pfriend.campaign) {
        pfriend.campaign.reset();
    }
    pfriend.campaign = std::move(campaign);
}

unsigned Player::remove_dead() {
    unsigned removed = 0;
    for (auto it = heroes.begin(); it != heroes.end();) {
        if (it->second->is_dead()) {
            it = heroes.erase(it);
            removed++;
        } else {
            ++it;
        }
    }
    return removed;
}

std::ostream& Player::print_campaign(std::ostream& o) const {
    if (campaign) {
        o << *campaign;
    } else {
        o << "[]";
    }
    return o;
}

std::ostream& operator<<(std::ostream& o, const Player& p) {
    o << "[" << p.first_name << " " << p.last_name << ", {";
    for (const auto& entry : p.heroes) {
        o << *entry.second << ", ";
    }
    o.seekp(-2, std::ios_base::end); // remove last comma and space
    o << "}, ";
    p.print_campaign(o);
    o << "]";
    return o;
}

