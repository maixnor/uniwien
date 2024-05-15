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
#include"adventurer.h"

using namespace std;

// AUFGABE 1
pair<Adventurer, size_t> task1(const Vector<Adventurer>& v) {
    Adventurer result;

    // filter
    std::vector<Adventurer> class_matches;
    std::copy_if(
        v.begin(),
        v.end(),
        std::back_inserter(class_matches),
        [](const auto& x) { return x.get_a_class() == A_class::CLERIC || x.get_a_class() == A_class::MONK; }
      );

    // reduce
    std::vector<pair<Adventurer, size_t>> eCounts;
    std::transform(
        class_matches.begin(),
        class_matches.end(),
        std::back_inserter(eCounts),
        [] (const auto& x) { make_pair(x,  count(x.get_name().begin(), x.get_name().end(), 'e')); }
      );

    // sort + first
    pair<Adventurer, size_t> highestECount;
    highestECount = 
      (* std::max_element(
          eCounts.begin(),
          eCounts.end(),
          [] (const auto& a, const auto& b) { return a.second < b.second; }
        ));
    
    // count
    size_t wealth = highestECount.first.get_wealth();
    size_t countHigherWealth = std::count_if(
        v.begin(),
        v.end(),
        [&wealth] (const Adventurer& x) { return x.get_wealth() > wealth; }
      );
    

    return make_pair(highestECount.first, countHigherWealth);
}
// AUFGABE 2


// AUFGABE 3
//using sorted_set = ;
//sorted_set task3(const Vector<Adventurer>& v, size_t x) {
//}

// AUFGABE 4
//map<A_group,vector<pair<string,size_t>>> task4(const Vector<Adventurer>& v) {
//}

