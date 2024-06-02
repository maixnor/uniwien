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
#include"tasks.h"

using namespace std;

int main() {
  // Der Vektor v_objects wird definiert und mit Daten befüllt.
  try {
// AUFGABE 1
  std::cout << " ------------ Aufgabe 1 ---------- \n";
  {
    cout << "Test Aufgabe 1\n";
    try {
      Vector<Adventurer> big_V;
      pair<Adventurer,size_t> res{task1(big_V)};
      std::cout << res.first << "\n" << res.second << "\n";
    }
    catch (runtime_error& e) {
      cout << "runtime_error wurde geworfen\n";
    }
    try {
      Vector<Adventurer> big_V;
      std::copy(v_objects.begin(), v_objects.end(), big_V.begin());
      pair<Adventurer,size_t> res{task1(big_V)};
      std::cout << res.first << "\n" << res.second << "\n";
    }
    catch (runtime_error& e) {
      cout << "runtime_error wurde geworfen\n";
    }
    try {
      Vector<Adventurer> big_V{v_objects[5],v_objects[6]};
      pair<Adventurer,size_t> res{task1(big_V)};
      std::cout << res.first << "\n" << res.second << "\n";
    }
    catch (runtime_error& e) {
      cout << "runtime_error wurde geworfen\n";
    }
    try {
      Vector<Adventurer> big_V{v_objects[2],v_objects[3],v_objects[4]};
      pair<Adventurer,size_t> res{task1(big_V)};
      std::cout << res.first << "\n" << res.second << "\n";
    }
    catch (runtime_error& e) {
      cout << "runtime_error wurde geworfen\n";
    }
    try {
      Vector<Adventurer> big_V{v_objects[8]};
      pair<Adventurer,size_t> res{task1(big_V)};
      std::cout << res.first << "\n" << res.second << "\n";
    }
    catch (runtime_error& e) {
      cout << "runtime_error wurde geworfen\n";
    }
  }
  std::cout << " ------------ Ende Aufgabe 1 ---------- \n\n";
// ENDE AUFGABE 1

/*
// AUFGABE 2
  std::cout << " ------------ Aufgabe 2 ---------- \n";
  {
    Vector<int> v;
    Vector<int>::IteratorY it{v.begin_y()};
    for(;it!=v.end_y();++it)
      std::cout << *it <<  " ";
    std::cout << std::endl;
  }
  {
    Vector<int> v{1,2,3,4,5};
    Vector<int>::IteratorY it{v.begin_y()};
    for(;it!=v.end_y();++it)
      std::cout << *it <<  " ";
    std::cout << std::endl;
  }
  {
    Vector<Adventurer> tmp;
    for(auto it{v_objects.begin()};it!=v_objects.end() && tmp.size()<45;++it){
      tmp.push_back(*it);
    }
    Vector<Adventurer> v{tmp};
    for(const auto& x : v)
      std::cout << x << "\n";
    Vector<Adventurer>::IteratorY it{v.begin_y()};
    std::cout << "Now Reverse...................\n";
    for(;it!=v.end_y();++it)
      std::cout << *it <<  "\n";
    std::cout << std::endl;
    for(;it!=v.end_y();++it)
      std::cerr << *it <<  "\n";
    std::cerr << std::endl;
  }
  std::cout << " ------------ Ende Aufgabe 2 ---------- \n\n";
// ENDE AUFGABE 2
*/


/*
// AUFGABE 3
  cout << " ------------ Aufgabe 3 ---------- \n";
  {
    Vector<Adventurer> big_V;
    copy(v_objects, big_V);
    auto tl{task3(big_V,9999)};
    std::cout << "size: " << tl.size() << "\n";
    check_make_set(big_V,9999,tl);
  }
  cout << " ---------------------------------------------- \n\n";
  {
    Vector<Adventurer> big_V;
    copy(v_objects, big_V);
    auto tl{task3(big_V,10)};
    std::cout << "size: " << tl.size() << "\n";
    check_make_set(big_V,10,tl);
  }
  cout << " ------------ Ende Aufgabe 3 ---------- \n\n";
// ENDE AUFGABE 3
*/

/*
// AUFGABE 4

  cout << " ------------ Aufgabe 4 ---------- \n";
  {
    Vector<Adventurer> big_V;
    copy(v_objects, big_V);
    auto tl{task4(big_V)};
    for(const auto& x : tl){
      if(x.second.empty()){
        std::cout << "There shouldn't be an empty list\n" << "Key: "  << x.first << "\n";
      }else{
        cout << x.first << ", First: (" << x.second[0].first <<  ", " << x.second[0].second << "), Last: (" << x.second[x.second.size()-1].first << ", " << x.second[x.second.size()-1].second << "), Adventurers: " << x.second.size() << " " << std::endl;
      }
    }
  }
  cout << " ------------ Mid Aufgabe 4 ---------- \n\n";
  {
    Vector<Adventurer> big_V;
    for(size_t i{0};i<13;++i){
      big_V.push_back(v_objects[i]);
    }
    auto tl{task4(big_V)};
    for(const auto& x : tl){
      if(x.second.empty()){
        std::cout << "There shouldn't be an empty list\n" << "Key: "  << x.first << "\n";
      }else{
        cout << x.first << ", First: (" << x.second[0].first <<  ", " << x.second[0].second << "), Last: (" << x.second[x.second.size()-1].first << ", " << x.second[x.second.size()-1].second << "), Adventurers: " << x.second.size() << " " << std::endl;
      }
    }
  }
*/
// ENDE AUFGABE 4
  }
  catch (exception &e) {
    cout << "Unerwartete Exception: " << e.what() << '\n';
  }
  return 0;
}

