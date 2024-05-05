#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<set>
#include<map>
#include<stdexcept>
#include<functional>
#include<algorithm>
#include<numeric>
#include<memory>
#include"vector.h"
#include "adventurer.h"

using namespace std;

// AUFGABE 1
pair<Adventurer, size_t> task1(const Vector<Adventurer>& v) {
    Adventurer result;
    size_t maxE = 0;
    for (const auto& adventurer : v) {
        if (adventurer.get_a_class() == A_class::CLERIC || adventurer.get_a_class() == A_class::MONK) {
            size_t eCount = count(adventurer.get_name(), 'e');
            if (eCount > maxE) {
                result = adventurer;
                maxE = eCount;
            }
        }
    }
    
    if (result.get_a_class() != A_class::CLERIC && result.get_a_class() != A_class::MONK) {
        throw runtime_error("List does not contain a CLERIC or MONK");
    }
    
    size_t countHigherWealth = 0;
    for (const auto& adventurer : v) {
        if (adventurer.get_wealth() > result.get_wealth()) {
            ++countHigherWealth;
        }
    }
    
    return make_pair(result, countHigherWealth);
}

// AUFGABE 2


// AUFGABE 3
//using sorted_set = ;
//sorted_set task3(const Vector<Adventurer>& v, size_t x) {
//}

// AUFGABE 4
//map<A_group,vector<pair<string,size_t>>> task4(const Vector<Adventurer>& v) {
//}

