#ifndef ADVENTURER_H
#define ADVENTURER_H

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<stdexcept>
using namespace std;

enum class A_class {BARBARIAN,CLERIC,FIGHTER,SORCERER,ROGUE,DRUID,MONK,WIZARD,WARLOCK,BARD,PALADIN,RANGER};
const vector<string> enum_names{"BARBARIAN","CLERIC","FIGHTER","SORCERER","ROGUE","DRUID","MONK","WIZARD","WARLOCK","BARD","PALADIN","RANGER"};
enum class A_group {HUMAN,ELF,HALFELF,HALFORC,DWARF,HALFLING,TIEFLING,DRAGONSPAWN,GNOME};
const vector<string> enum_names2{"HUMAN","ELF","HALFELF","HALFORC","DWARF","HALFLING","TIEFLING","DRAGONSPAWN","GNOME"};

class Adventurer{
  string name;
  A_class a_class;
  A_group a_group;
  vector<size_t> stats; // Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma
  size_t wealth;
  set<string> proficiencies;
public:
  Adventurer();
  Adventurer(string,A_class,A_group,const vector<size_t>&,size_t,const set<string>&);
  const string& get_name() const{return name;}
  A_class get_a_class() const{return a_class;}
  A_group get_a_group() const{return a_group;}
  const vector<size_t>& get_stats() const{return stats;}
  size_t get_wealth() const{return wealth;}
  const set<string>& get_proficiencies() const{return proficiencies;}
  ostream& print(ostream& o) const;
  static vector<Adventurer> read(ifstream&);
  friend bool operator==(const Adventurer&,const Adventurer&);
  friend bool operator!=(const Adventurer&,const Adventurer&);
  friend bool operator<(const Adventurer&,const Adventurer&);
};
  
std::string to_s(A_class);
std::string to_s(A_group);
ostream& operator<<(ostream&, const Adventurer&);
ostream& operator<<(ostream&, const A_class&);
ostream& operator<<(ostream&, const A_group&);
  
vector<string> split(string s,char del);
extern const vector<Adventurer> v_objects;

#include"check.hr"  //Enthaelt Testroutinen, deren Kenntnis nicht zum Verstaendnis oder zum
                    //
                    //Loesen der Pruefungsaufgaben noetig ist

#endif

