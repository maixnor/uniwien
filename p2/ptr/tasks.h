#ifndef TASKS_H
#define TASKS_H

#include "player.h"
#include "hero.h"
#include "hero_info.h"
#include "player.h"
#include "monster.h"
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <numeric>
#include <cctype>
#include <iostream>

using namespace std;

std::vector<std::shared_ptr<Monster>> task1(const std::vector<std::shared_ptr<Monster>>& v) {
    if (v.empty()) {
        return {};
    }

    // Berechne die Summe aller health-Werte
    unsigned total_health = std::accumulate(v.begin(), v.end(), 0, [](unsigned sum, const std::shared_ptr<Monster>& m) {
        return sum + m->get_health();
    });

    // Berechne den maximalen Angriffswert
    unsigned max_attack = std::max_element(v.begin(), v.end(), [](const std::shared_ptr<Monster>& a, const std::shared_ptr<Monster>& b) {
        return a->get_attack() < b->get_attack();
    })->get()->get_attack();

    std::vector<std::shared_ptr<Monster>> result;
    for (const auto& monster : v) {
        std::string upper_name = monster->get_name();
        std::transform(upper_name.begin(), upper_name.end(), upper_name.begin(), ::toupper);
        result.push_back(std::make_shared<Standard_Monster>(upper_name, total_health, max_attack));
    }

    return result;
}

class Super_Task {
private:
    std::vector<std::weak_ptr<Hero>> heroes;

public:
    Super_Task(const std::vector<std::shared_ptr<Hero>>& heroes) {
        this->heroes = std::vector<std::weak_ptr<Hero>>(heroes.begin(), heroes.end());
    }

    std::vector<std::shared_ptr<Hero>> filtering(const std::vector<Hero_Class>& cl) const {
        std::vector<std::shared_ptr<Hero>> result;

        for (const auto& weak_hero : heroes) {
            if (auto hero = weak_hero.lock()) {
                if (std::find(cl.begin(), cl.end(), hero->get_class()) != cl.end()) {
                    result.push_back(hero);
                }
            }
        }

        return result;
    }
};

#endif
