 // VU Algorithmen und Datenstrukturen 1 - SS 2024 Universitaet Wien
 // https://cewebs.cs.univie.ac.at/algodat/ss24/
 //
 // Simples Testprogramm zur Ueberpruefung der ADS_set-Funktionalitaet
 //
 static constexpr char version[] {"20230523"};
 // 
 // Die Zurverfügungstellung des Programmes oder Teilen davon auf anderen Plattformen,
 // Repositories, etc. ist nicht zulässig.
 //
 // BEACHTEN:
 // (1) Der Elementdatentyp muss mit Compileroption -DETYPE=<typ> festgelegt werden,
 //     also zb -DETYPE=std::string. <typ> muss zum Testen Ein- und -Ausgabe über Streams 
 //     mittels >> bzw << unterstützen.
 // (2) Der zweite Templateparameter kann mit Compileroption -DSIZE=<n> festgelegt
 //     werden, also zb -DSIZE=13, andernfalls wird der Defaultwert verwendet. Es wird
 //     empfohlen, jedenfalls auch mit -DSIZE=1 zu testen (das macht auch der Unit-Test)
 // (3) Das Testprogramm testet nicht alle ADS_set-Methoden/Funktionen, es kann aber 
 //     entsprechend erweitert werden.
 // 
 // 1. Projektphase:
 //
 // g++ -Wall -Wextra -Werror -O3 -std=c++17 -pedantic-errors -DPH1 -DETYPE=std::string simpletest.cpp -o simpletest
 // g++ -Wall -Wextra -Werror -O3 -std=c++17 -pedantic-errors -DPH1 -DETYPE=std::string -DSIZE=1 simpletest.cpp -o simpletest
 // g++ -Wall -Wextra -Werror -O3 -std=c++17 -pedantic-errors -DPH1 -DETYPE=Person simpletest.cpp -o simpletest
 // g++ -Wall -Wextra -Werror -O3 -std=c++17 -pedantic-errors -DPH1 -DETYPE=Person -DSIZE=1 simpletest.cpp -o simpletest
 // g++ -Wall -Wextra -Werror -O3 -std=c++17 -pedantic-errors -DPH1 -DETYPE=SafeUnsigned simpletest.cpp -o simpletest
 // g++ -Wall -Wextra -Werror -O3 -std=c++17 -pedantic-errors -DPH1 -DETYPE=SafeUnsigned -DSIZE=1 simpletest.cpp -o simpletest
 // g++ -Wall -Wextra -Werror -O3 -std=c++17 -pedantic-errors -DPH1 -DETYPE=unsigned simpletest.cpp -o simpletest
 // g++ -Wall -Wextra -Werror -O3 -std=c++17 -pedantic-errors -DPH1 -DETYPE=unsigned -DSIZE=1 simpletest.cpp -o simpletest
 // 
 // 2. Projektphase:
 //
 // g++ -Wall -Wextra -Werror -O3 -std=c++17 -pedantic-errors -DPH2 -DETYPE=std::string simpletest.cpp -o simpletest
 // g++ -Wall -Wextra -Werror -O3 -std=c++17 -pedantic-errors -DPH2 -DETYPE=std::string -DSIZE=1 simpletest.cpp -o simpletest
 // g++ -Wall -Wextra -Werror -O3 -std=c++17 -pedantic-errors -DPH2 -DETYPE=Person simpletest.cpp -o simpletest
 // g++ -Wall -Wextra -Werror -O3 -std=c++17 -pedantic-errors -DPH2 -DETYPE=Person -DSIZE=1 simpletest.cpp -o simpletest
 // g++ -Wall -Wextra -Werror -O3 -std=c++17 -pedantic-errors -DPH2 -DETYPE=SafeUnsigned simpletest.cpp -o simpletest
 // g++ -Wall -Wextra -Werror -O3 -std=c++17 -pedantic-errors -DPH2 -DETYPE=SafeUnsigned -DSIZE=1 simpletest.cpp -o simpletest
 // g++ -Wall -Wextra -Werror -O3 -std=c++17 -pedantic-errors -DPH2 -DETYPE=unsigned simpletest.cpp -o simpletest
 // g++ -Wall -Wextra -Werror -O3 -std=c++17 -pedantic-errors -DPH2 -DETYPE=unsigned -DSIZE=1 simpletest.cpp -o simpletest
 
 #include <iostream>
 #include <sstream>
 #include <fstream>
 #include <string>
 #include <vector>
 #include <iomanip>
 #include <iterator>
 #include <stdexcept>
 #include <set>
 #include <algorithm>
 #include <random>
 #include <numeric>
 #include "ADS_set.h"
 #include <type_traits>
 
 #ifndef ETYPE
 #error ETYPE not defined - compile with option -DETYPE=type
 #else
 
 #if !defined PH1 && !defined PH2
 #define PH2
 #endif

 class Person;
 class SafeUnsigned;
 using Key = ETYPE;
 using reference_set = std::set<Key>; 

 #ifdef SIZE
   using ads_set = ADS_set<Key,SIZE>;
 #else
   using ads_set = ADS_set<Key>;
 #endif

 enum class Code {quit = 0, new_set, delete_set, insert, erase, find, count, size, empty, dump, trace, finsert, ferase, rinsert, rerase, help, clear, iterator, list, iinsert, fiinsert, riinsert};  

 struct Command {
   Code code;
   std::string name, info;
   bool need_set, key_args, do_trace {false};
 };
 std::vector<Command> commands = {
   {Code::new_set, "new", "create new set", false, false, true},
   {Code::delete_set, "DELETE", "delete set", true, false},
   {Code::count, "count [<keys>]", "call count() for all keys (no output) or <keys>", true, true},
 #ifdef PH2
   {Code::find, "find [<keys>]", "call find() for all keys (no output) or <keys>", true, true},
 #endif
   {Code::size, "size", "call size()", true, false},
   {Code::empty, "empty", "call empty()", true, false},
   {Code::iinsert, "iinsert <keys>", "insert <keys>, call insert(InputIt, InputIt)", true, true, true},
   {Code::riinsert, "riinsert [<n> [<seed>]]", "insert <n> random values, call insert(InputIt, InputIt), optionally reset generator to <seed>", true, false, true},
   {Code::fiinsert, "fiinsert <filename>", "insert values from file <filename>, call insert(InputIt, InputIt)", true, false, true},
 #ifdef PH2
   {Code::insert, "insert <keys>", "insert <keys>, call insert(const key_type&)", true, true, true},
   {Code::rinsert, "rinsert [<n> [<seed>]]", "insert <n> random values, call insert(const key_type&), optionally reset generator to <seed>", true, false, true},
   {Code::finsert, "finsert <filename>", "insert values from file <filename>, call insert(const key_type&)", true, false, true},
   {Code::erase, "erase [<keys>]", "erase all keys (no output) or <keys>", true, true, true},
   {Code::rerase, "rerase [<n> [<seed>]]", "erase <n> random values, optionally reset generator to <seed>", true, false, true},
   {Code::ferase, "ferase <filename>", "erase values from file <filename>", true, false, true},
   {Code::clear, "clear", "call clear()", true, false, true},
   {Code::iterator, "iterator", "iterator/find test", true, false},
 #endif
   {Code::dump, "dump", "call dump()", true, false},
   {Code::trace, "trace", "toggle tracing on/off", false, false},
   {Code::list, "list", "list all intended elements (sorted)", true, false},
   {Code::help, "help", "list of commands", false, false},
   {Code::help, "?", "like 'help'", false, false},
   {Code::quit, "quit (or EOF)", "quit program (deletes set)", false, false},
 };
 
 class Person {
   std::string vn;
   std::string nn;
   bool is_valid;
 public:
   Person(): is_valid{false} { }
   Person(const std::string &vn, const std::string &nn) : vn{vn}, nn{nn}, is_valid{true} { }
   friend struct std::hash<Person>;
   friend struct std::equal_to<Person>;
   friend struct std::less<Person>;
   friend std::ostream &operator<<(std::ostream &o, const Person &p) { 
     if (p.is_valid) return o << '[' << p.nn << ", " << p.vn << ']'; 
     return o << "UNDEFINED";
   }
   friend std::istream &operator>>(std::istream &i, Person &p) { 
     i >> p.vn >> p.nn;
     p.is_valid = true;
     return i;
   }
 };
 
 namespace std {
   template <> struct hash<Person> {
     size_t operator()(const Person &p) const {
       if (!p.is_valid) throw std::runtime_error{"std::hash<Person>: undefined argument"};
       return std::hash<std::string>{}(p.vn) ^ std::hash<std::string>{}(p.nn) << 1;
     }
   };
   template <> struct equal_to<Person> {
     bool operator()(const Person &lhs, const Person &rhs) const {
       if (!lhs.is_valid && !rhs.is_valid) throw std::runtime_error{"std::equal_to<Person>: undefined arguments"};
       if (!lhs.is_valid) throw std::runtime_error{"std::equal_to<Person>: undefined first argument"};
       if (!rhs.is_valid) throw std::runtime_error{"std::equal_to<Person>: undefined second argument"};
       return lhs.vn == rhs.vn && lhs.nn == rhs.nn; 
     }
   };
   template <> struct less<Person> {
     bool operator()(const Person &lhs, const Person &rhs) const { 
       if (!lhs.is_valid && !rhs.is_valid) throw std::runtime_error{"std::equal_to<Person>: undefined arguments"};
       if (!lhs.is_valid) throw std::runtime_error{"std::equal_to<Person>: undefined first argument"};
       if (!rhs.is_valid) throw std::runtime_error{"std::equal_to<Person>: undefined second argument"};
       return lhs.nn < rhs.nn || (lhs.nn == rhs.nn && lhs.vn < rhs.vn); 
     }
   };
 }

 class SafeUnsigned {
   unsigned u;
   enum State {undefined = 1234, defined = 4711, deallocated = 6666};
   State state {undefined};
 public:
   SafeUnsigned() { }
   SafeUnsigned(unsigned u) : u{u}, state{defined} { }
   ~SafeUnsigned() { state = deallocated; }
   friend struct std::hash<SafeUnsigned>;
   friend struct std::equal_to<SafeUnsigned>;
   friend struct std::less<SafeUnsigned>;
   friend std::ostream &operator<<(std::ostream &o, const SafeUnsigned &p) { 
     switch (p.state) {
       case defined: return o << p.u;
       case undefined: return o << "UNDEFINED"; 
       default: return o << "NOT ALLOCATED";
     }
   }
   friend std::istream &operator>>(std::istream &i, SafeUnsigned &p) { 
     if (p.state != undefined && p.state != defined) throw std::runtime_error{"SafeUnsigned::operator>>(): object NOT ALLOCATED"};
     i >> p.u;
     p.state = defined;
     return i;
   }
 };
 
 namespace std {
   template <> struct hash<SafeUnsigned> {
     size_t operator()(const SafeUnsigned &p) const {
       switch (p.state) {
         case SafeUnsigned::defined: return p.u & (~0U>>1); // provoke collisions
         case SafeUnsigned::undefined: throw std::runtime_error{"std::hash<SafeUnsigned>: argument is UNDEFINED"}; 
         default: throw std::runtime_error{"std::hash<SafeUnsigned>: argument is NOT ALLOCATED"};
       }
     }
   };
   template <> struct equal_to<SafeUnsigned> {
     bool operator()(const SafeUnsigned &lhs, const SafeUnsigned &rhs) const {
#if defined(DEBUG)
       std::cerr << "equal_to<SafeUnsigned>::operator()(" << lhs << "," << rhs << ")\n";
#endif
       std::string errmsg;
       switch (lhs.state) {
         case SafeUnsigned::defined: break;
         case SafeUnsigned::undefined: errmsg += " first (lhs) argument is UNDEFINED"; break; 
         default: errmsg += " first (lhs) argument is NOT ALLOCATED"; break;
       }
       switch (rhs.state) {
         case SafeUnsigned::defined: break;
         case SafeUnsigned::undefined: errmsg += " second (rhs) argument is UNDEFINED"; break; 
         default: errmsg += " second (rhs) argument is NOT ALLOCATED"; break;
       }
       if (!errmsg.empty()) throw std::runtime_error{std::string{"std::equal_to<SafeUnsigned>:"} +  errmsg}; 
       return lhs.u == rhs.u; 
     }
   };
   template <> struct less<SafeUnsigned> {
     bool operator()(const SafeUnsigned &lhs, const SafeUnsigned &rhs) const { 
       std::string errmsg;
       switch (lhs.state) {
         case SafeUnsigned::defined: break;
         case SafeUnsigned::undefined: errmsg += " first (lhs) argument is UNDEFINED"; break; 
         default: errmsg += " first (lhs) argument is NOT ALLOCATED"; break;
       }
       switch (rhs.state) {
         case SafeUnsigned::defined: break;
         case SafeUnsigned::undefined: errmsg += " second (rhs) argument is UNDEFINED"; break; 
         default: errmsg += " second (rhs) argument is NOT ALLOCATED"; break;
       }
       if (!errmsg.empty()) throw std::runtime_error{std::string{"std::less<SafeUnsigned>:"} +  errmsg}; 
       return lhs.u < rhs.u; 
     }
   };
 }

 struct Rand {
   std::default_random_engine re;
   std::uniform_int_distribution<uint32_t> dist;
   void seed(unsigned s) { re.seed(s); }
   template <typename T> T next() { return static_cast<T>(dist(re)); }
 };
 template <> std::string Rand::next() {
   std::string rc;
   for (auto i {dist(re)}; i; i /= 26) rc += 'a' + i%26;
   return rc;
 }
 template <> Person Rand::next() {
   return Person(next<std::string>(), next<std::string>());
 }
 template <> SafeUnsigned Rand::next() {
   return SafeUnsigned(next<unsigned>());
 }


 template <typename C1, typename It1, typename C2, typename It2>
 bool it_equal(const C1 &c1, const It1 &it1, const C2 &c2, const It2 &it2) {
   return (it1 == c1.end() && it2 == c2.end()) || (it1 != c1.end() && it2 != c2.end() && std::equal_to<Key>{}(*it1, *it2));
 }
 template <typename C, typename It>
 std::string it2str(const C &c, const It &it) {
   if (it == c.end()) return std::string{"end()"};
   std::stringstream buf;
   buf << '&' << *it;
   return buf.str(); 
 } 
 #ifdef PH2
 void test_insert(const Key &k, ads_set *c, reference_set *r, bool verbose = false) {
   auto r_rc {r->insert(k)};
   auto c_rc {c->insert(k)};
   if (!(c_rc.first == c->find(k))) 
     std::cout << "\n ERROR for " << k << ", returned iterator not equal (==) to iterator returned by find(" << k << ")\n";
   else if (!it_equal(*r, r_rc.first, *c, c_rc.first) || r_rc.second != c_rc.second) 
     std::cout << "\n ERROR for " << k << ", returns {" << it2str(*c, c_rc.first) << ", " << c_rc.second
       << "}, should be {" << it2str(*r, r_rc.first) << ", " << r_rc.second << "}\n";
   else if (verbose)
     std::cout << " {" << it2str(*r, r_rc.first) << ", " << c_rc.second << "}";
 }
 void test_erase(const Key &k, ads_set *c, reference_set *r = nullptr, bool verbose = false) {
   size_t r_rc {r ? r->erase(k) : 1}; 
   size_t c_rc {c->erase(k)};
   if (r_rc != c_rc) 
     std::cout << "\n ERROR for " << k << ", returns " << c_rc << ", should be " << r_rc << '\n';
   else if (verbose) 
     std::cout << ' ' << c_rc;
 }
 void test_find(const Key &k, const ads_set *c, const reference_set *r, bool verbose = false) {
   auto c_rc {c->find(k)};
   auto r_rc {r->find(k)};
   if (!it_equal(*c, c_rc, *r, r_rc))
     std::cout << "\n ERROR for " << k << ", returns " << it2str(*c, c_rc) << ", should be " << it2str(*r, r_rc) << '\n';
   else if (verbose)
     std::cout << ' ' << it2str(*c, c_rc);
 }
 #endif
 void test_count(const Key &k, const ads_set *c, const reference_set *r = nullptr, bool verbose = false) {
   size_t r_rc {r ? r->count(k) : 1}; 
   size_t c_rc {c->count(k)};
   if (r_rc != c_rc) 
     std::cout << "\n ERROR for " << k << ", returns " << c_rc << ", should be " << r_rc << '\n';
   else if (verbose)
     std::cout << ' ' << c_rc;
 }
 
 int main() {
   Rand random;
   ads_set *c {nullptr};
   const ads_set *const_c {c};
   reference_set *r {nullptr};
   bool do_trace {false};
   std::cout.setf(std::ios_base::boolalpha);
 #ifdef PH2
   ads_set::const_iterator default_constructed_iterator; // check existence of iterator's default constructor
 #endif
   std::string line;

   std::cout << "\nsimpletest " << version << "\n";
   while (std::cout << "\nsimpletest> ", std::getline(std::cin, line)) {
     std::istringstream line_stream(line);
     std::string cmd;
     line_stream >> cmd;

     if (!cmd.size()) continue;
     auto cmd_it {find_if(commands.begin(), commands.end(), [&cmd](const Command &cm) {return !cm.name.find(cmd);})};
     if (cmd_it == commands.end()) {
       std::cout << cmd << "? ERROR - try 'help'";
       continue;
     }
     if (cmd_it->code == Code::quit) break;
     if (cmd_it->need_set && !c) {
       std::cout << "ERROR - no container (use 'new')";
       continue;
     }
     
     try {
       std::vector<Key> key_v;
       if (cmd_it->key_args) {
         for (Key key; line_stream >> key; ) key_v.push_back(key);
       }
       switch (cmd_it->code) {
         case Code::new_set:
           if (c) {
             std::cout << "ERROR - container exists, 'delete' it first";
             continue;
           }
           const_c = c = new ads_set;
           r = new reference_set;
           break;
         case Code::help: {
           std::cout << "\nsimpletest " << version << "\n";
           std::cout << '\n' << std::right << std::setfill('.');
           size_t maxw {std::accumulate(commands.begin(), commands.end(), size_t{0}, [](const size_t &m, const Command &c) { return std::max(m,c.name.size()); })};
           for (const auto &x: commands)
             std::cout << x.name << ' ' << std::setw(maxw-x.name.size()+3) << ' ' << x.info << '\n';
           std::cout << std::setfill(' ') << "\narguments surrounded by [] are optional\n";
           break;
         }
         case Code::trace:
           std::cout << "trace " << ((do_trace = !do_trace) ? "on" : "off");
           break;
         case Code::delete_set:
           delete c, const_c = c = nullptr;
           delete r, r = nullptr;
           break;
         case Code::iinsert:
           r->insert(key_v.begin(), key_v.end()); 
           c->insert(key_v.begin(), key_v.end());
           break;
         case Code::count:
           if (key_v.size()) for (const Key &k: key_v) test_count(k, const_c, r, true);
           else for (const auto &k: *r) test_count(k, const_c);
           break;
         case Code::size:
           std::cout << " " << const_c->size();
           if (const_c->size() != r->size()) std::cout << " ERROR, should be " << r->size();
           break;
         case Code::empty:
           std::cout << " " << const_c->empty();
           if (const_c->empty() != r->empty()) std::cout << " ERROR, should be " << r->empty();
           break;
         case Code::dump:
           const_c->dump(std::cout);
           break;
         case Code::fiinsert: {
           std::string filename;
           line_stream >> filename;
           std::ifstream is(filename);
           r->insert(std::istream_iterator<Key>{is}, std::istream_iterator<Key>{});
           is.clear(); is.seekg(0);
           c->insert(std::istream_iterator<Key>{is}, std::istream_iterator<Key>{});
           break;
         }
         case Code::riinsert: {
           unsigned seed, count{1};
           line_stream >> count;
           if (line_stream >> seed) random.seed(seed);
           std::vector<Key> v;
           while (count-- > 0) v.push_back(random.next<Key>());
           r->insert(v.begin(), v.end());
           c->insert(v.begin(), v.end());
           break;
         }
         case Code::list:
           for (const Key &k: *r) std::cout << ' ' << k;
           break;
 #ifdef PH2
         case Code::finsert: {
           std::string filename;
           line_stream >> filename;
           std::ifstream is(filename);
           for (Key k; is >> k; ) test_insert(k, c, r);
           break;
         }
         case Code::clear:
           r->clear();
           c->clear();
           break;
         case Code::ferase: {
           std::string filename;
           line_stream >> filename;
           std::ifstream is(filename);
           for (Key k; is >> k; ) test_erase(k, c, r);
           break;
         }
         case Code::rinsert: {
           unsigned seed, count{1};
           line_stream >> count;
           if (line_stream >> seed) random.seed(seed);
           while (count-- > 0) test_insert(random.next<Key>(), c, r);
           break;
         }
         case Code::rerase: {
           unsigned seed, count{1};
           line_stream >> count;
           if (line_stream >> seed) random.seed(seed);
           while (count-- > 0) test_erase(random.next<Key>(), c, r);
           break;
         }
         case Code::insert:
           for (const Key &k: key_v) test_insert(k, c, r, true);
           break;
         case Code::erase:
           if (key_v.size()) for (const Key &k: key_v) test_erase(k, c, r, true);
           else {
             for (const Key &k: *r) test_erase(k, c);
             r->clear();
           }
           break;
         case Code::find:
           if (key_v.size()) for (const Key &k: key_v) test_find(k, const_c, r, true);
           else for (const auto &k: *r) test_find(k, const_c, r);
           break;
         case Code::iterator: {
           std::vector<Key> v;
           for (auto c_it {const_c->begin()}; !(c_it == const_c->end());) v.push_back(*c_it++.operator->());
           if (v.size() != r->size()) {
             std::cout << " ERROR - vector fill failed (wrong size)";
             break;
           }
           if (!std::is_permutation(v.begin(), v.end(), r->begin(), std::equal_to<Key>{})) {
             std::cout << " ERROR - vector fill failed (duplicate/missing elements)";
             break;
           }
           for (auto v_it {v.begin()}; v_it != v.end(); ++v_it) {
             auto c_it {const_c->find(*v_it)};
             if (!std::equal_to<Key>{}(*c_it, *v_it)) {
               std::cout << " ERROR - iterator returned by find";
               break;
             }
             if (!std::equal(v.begin(), v_it, const_c->begin(), c_it, std::equal_to<Key>{}) || !std::equal(v_it, v.end(), c_it, const_c->end(), std::equal_to<Key>{})) {
               std::cout << " ERROR - ranges";
               break;
             }
           }
           break;
         }
 #endif // PH2
         default:
           throw std::runtime_error("ERROR - unknown command code");
       }
       if (do_trace && cmd_it->do_trace && c) {
         std::cout << "\n";
         const_c->dump(std::cout);
       }
     } catch (std::exception &e) {
       std::cout << "ERROR - caught std::exception \"" << e.what() << "\"";
     } catch (...) {
       std::cout << "ERROR - caught something else";
     }
   }
   delete c;
   delete r;
   return 0;
 }
 #endif // ETYPE	

