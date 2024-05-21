#ifndef ADS_SET_H
#define ADS_SET_H

// ADS_set.h Double Hashing
// 
// VU Algorithmen und Datenstrukturen 1 - SS 2024 Universitaet Wien
// https://cewebs.cs.univie.ac.at/algodat/ss24/
//
// Beispielimplementierung mit "Double Hashing - Linear Probing" 
// Erstellt in der Lehrveranstaltung im SS 2022 
// 29.04.2022 (1. Abgabe)
//
// Nicht optimiert und eventuell fehlerhaft (Fehler bitte melden)
//
// Die Zurverfügungstellung des Programmes oder Teilen davon auf anderen Plattformen,
// Repositories, etc. ist nicht zulässig.
//
// Dringende Empfehlung: Verwenden Sie diese Implementierung NICHT als 
// Kopiervorlage für Ihre eigene Implementierung! Entwickeln Sie Ihre eigene 
// Implementierung von Grund auf neu.

#include <functional>
#include <algorithm>
#include <iostream>
#include <stdexcept>

template <typename Key, size_t N = 7>
class ADS_set {
public:
  //class /* iterator type (implementation-defined) */;
  using value_type = Key;
  using key_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using difference_type = std::ptrdiff_t;
  //using const_iterator = /* iterator type */;
  //using iterator = const_iterator;
  //using key_compare = std::less<key_type>;                         // B+-Tree
  using key_equal = std::equal_to<key_type>;                       // Hashing
  using hasher = std::hash<key_type>;                              // Hashing

private:
  enum class Mode {free, used, freeagain};
  struct Element {
    key_type key;
    Mode mode {Mode::free};
  };
  Element *table {nullptr};
  size_type table_size {0};
  size_type current_size {0};
  float max_lf {0.7};
  
  void add(const key_type &key);
  Element *locate(const key_type &key) const;
  size_type h(const key_type &key) const { return hasher{}(key) % table_size; }
  size_type g(const key_type &) const { return 1; }
  void reserve(size_type n);
  void rehash(size_type n);
public:
  ADS_set(): table{new Element[N]}, table_size{N}, current_size{0} {}
  ADS_set(std::initializer_list<key_type> ilist): ADS_set{} { insert(ilist); }
  template<typename InputIt> ADS_set(InputIt first, InputIt last): ADS_set{} { insert(first,last); }
  //ADS_set(const ADS_set &other);

  //~ADS_set();

  //ADS_set &operator=(const ADS_set &other);
  //ADS_set &operator=(std::initializer_list<key_type> ilist);

  size_type size() const { return current_size; }
  bool empty() const { return current_size == 0; }

  void insert(std::initializer_list<key_type> ilist) { insert(ilist.begin(), ilist.end()); }
  //std::pair<iterator,bool> insert(const key_type &key);
  template<typename InputIt> void insert(InputIt first, InputIt last);

  //void clear();
  //size_type erase(const key_type &key);

  size_type count(const key_type &key) const { return locate(key) != nullptr; }
  //iterator find(const key_type &key) const;

  //void swap(ADS_set &other);

  //const_iterator begin() const;
  //const_iterator end() const;

  void dump(std::ostream &o = std::cerr) const;

  //friend bool operator==(const ADS_set &lhs, const ADS_set &rhs);
  //friend bool operator!=(const ADS_set &lhs, const ADS_set &rhs);
};

template <typename Key, size_t N>
void ADS_set<Key,N>::add(const key_type &key) {
  size_type idx {h(key)}, start_idx{idx};
  while (table[idx].mode == Mode::used) {
    if ((idx = (idx + g(key)) % table_size) == start_idx) throw std::runtime_error{"ADS_set::add: loop detected"};
  }
  table[idx] = {key, Mode::used};
  ++current_size;
}

template <typename Key, size_t N>
typename ADS_set<Key,N>::Element *ADS_set<Key,N>::locate(const key_type &key) const {
  size_type idx {h(key)}, start_idx{idx};
  do {
    switch (table[idx].mode) {
      case Mode::free:
        return nullptr;
      case Mode::used:
        if (key_equal{}(table[idx].key, key)) return table+idx; // return &table[idx];
        break;
      case Mode::freeagain:
        break; 
    }
    idx = (idx + g(key)) % table_size;
  } while (idx != start_idx);
  return nullptr;
}

template <typename Key, size_t N>
template<typename InputIt> void ADS_set<Key,N>::insert(InputIt first, InputIt last) {
  for (auto it {first}; it != last; ++it) {
    if (!count(*it)) {
      reserve(current_size+1);
      add(*it);
    }
  }
}

template <typename Key, size_t N>
void ADS_set<Key,N>::dump(std::ostream &o) const {
  o << "table_size = " << table_size << ", current_size = " << current_size << "\n";
  for (size_type idx {0}; idx < table_size; ++idx) {
    o << idx << ": ";
    switch (table[idx].mode) {
      case Mode::free:
        o << "--FREE";
        break;
      case Mode::used:
        o << table[idx].key;
        break;
      case Mode::freeagain:
        o << "--FREEAGAIN";
        break;
    }
    o << "\n";
  }
}

template <typename Key, size_t N>
void ADS_set<Key,N>::reserve(size_type n) {
  if (table_size * max_lf >= n) return;
  size_type new_table_size {table_size};
  while (new_table_size * max_lf < n) ++(new_table_size *=2);
  rehash(new_table_size);
}

template <typename Key, size_t N>
void ADS_set<Key,N>::rehash(size_type n) {
  size_type new_table_size {std::max(N,std::max(n,size_type(current_size/max_lf)))};
  Element *new_table {new Element [new_table_size]};
  Element *old_table {table};
  size_type old_table_size {table_size};
  
  current_size = 0;
  table = new_table;
  table_size = new_table_size;
  
  for (size_type idx {0}; idx < old_table_size; ++idx) {
    if (old_table[idx].mode == Mode::used) add(old_table[idx].key);
  }
  delete[] old_table;
}

#if 0
template <typename Key, size_t N>
class ADS_set<Key,N>::/* iterator type */ {
public:
  using value_type = Key;
  using difference_type = std::ptrdiff_t;
  using reference = const value_type &;
  using pointer = const value_type *;
  using iterator_category = std::forward_iterator_tag;

  explicit /* iterator type */(/* implementation-dependent */);
  reference operator*() const;
  pointer operator->() const;
  /* iterator type */ &operator++();
  /* iterator type */ operator++(int);
  friend bool operator==(const /* iterator type */ &lhs, const /* iterator type */ &rhs);
  friend bool operator!=(const /* iterator type */ &lhs, const /* iterator type */ &rhs);
};

template <typename Key, size_t N>
void swap(ADS_set<Key,N> &lhs, ADS_set<Key,N> &rhs) { lhs.swap(rhs); }
#endif

#endif // ADS_SET_H
