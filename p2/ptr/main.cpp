#include "campaign.h"
#include "player.h"
#include "hero.h"
#include "monster.h"
#include "tasks.h"
#include<cstdlib>
#include<iostream>

std::map<std::string,unsigned> abilities(){
    std::map<std::string,unsigned> abilities;
    abilities["Strength"] = rand() % 6 + 8;
    abilities["Dexterity"] = rand() % 6 + 8;
    abilities["Constitution"] = rand() % 6 + 8;
    abilities["Intelligence"] = rand() % 6 + 8;
    abilities["Wisdom"] = rand() % 6 + 8;
    abilities["Charisma"] = rand() % 6 + 8;
    return abilities;
}

using std::shared_ptr;
using std::weak_ptr;
using std::unique_ptr;
using std::make_shared;
int main(){
    std::srand(42);
    std::cout << std::boolalpha;

    std::cout << Hero_Class::BARBARIAN << std::endl;
    std::cout << Hero_Species::HUMAN << std::endl;
    {
        //Ctor
        try{
            Standard_Monster monster{"", 100, 100};
        }catch(const std::runtime_error& e){
            std::cout << "Error Monster 1" << std::endl;
        }
        try{
            Standard_Monster monster{"Monster", 0, 100};
        }catch(const std::runtime_error& e){
            std::cout << "Error Monster 2" << std::endl;
        }
        try{
            Standard_Monster monster{"Monster", 100, 0};
        }catch(const std::runtime_error& e){
            std::cout << "Error Monster 3" << std::endl;
        }
        try{
            Elite_Monster monster{"Monster", 100, 0,0};
        }catch(const std::runtime_error& e){
            std::cout << "Error Monster 4" << std::endl;
        }
        {
            Standard_Monster m{"Goblin Archer",110,5};
            std::cout << m << std::endl;
            std::cerr << m << std::endl;
            m.take_damage(std::rand() % 10 + 5);
            std::cout << m.is_dead() << std::endl;
        }
        {
            Standard_Monster m{"Goblin Archer",110,5};
            std::cout << m.is_dead() << std::endl;
            for(int i=0;i<20;i++){
                m.take_damage(std::rand() % 10 + 5);
                std::cout << m << std::endl;
            }
            std::cout << m.is_dead() << std::endl;
        }
        {
            Elite_Monster m{"Goblin Archer",110,5,5};
            std::cout << m.is_dead() << std::endl;
            for(int i=0;i<20;i++){
                m.take_damage(std::rand() % 20 + 5);
                std::cout << m << std::endl;
            }
            std::cout << m.is_dead() << std::endl;
        }

    }
// Hero Checks
    {
        {
            try{
                Hero h{"",Hero_Class::BARBARIAN,Hero_Species::HUMAN,9000,abilities()};
            }catch(const std::runtime_error& e){
                std::cout << "Error Hero 1" << std::endl;
            }
            try{
                auto ab = abilities();
                ab["unknown"] = 1;
                Hero h{"x",Hero_Class::BARBARIAN,Hero_Species::HUMAN,9000,ab};
            }catch(const std::runtime_error& e){
                std::cout << "Error Hero 2" << std::endl;
            }
            try{
                auto ab = abilities();
                ab.erase("Strength");
                Hero h{"x",Hero_Class::BARBARIAN,Hero_Species::HUMAN,9000,ab};
            }catch(const std::runtime_error& e){
                std::cout << "Error Hero 3" << std::endl;
            }
            try{
                auto ab = abilities();
                ab["Strength"] = 0;
                Hero h{"x",Hero_Class::BARBARIAN,Hero_Species::HUMAN,9000,ab};
            }catch(const std::runtime_error& e){
                std::cout << "Error Hero 4" << std::endl;
            }
            try{
                auto ab = abilities();
                ab["Charisma"] = 21;
                Hero h{"x",Hero_Class::BARBARIAN,Hero_Species::HUMAN,9000,ab};
            }catch(const std::runtime_error& e){
                std::cout << "Error Hero 5" << std::endl;
            }
        }
        {
            Hero h{"Jaina Proudmoore",Hero_Class::WIZARD,Hero_Species::HALF_ELF,9000,abilities()};
            std::cout << h << std::endl;
            std::cerr << h << std::endl;
            for(size_t i{0};i<25;i++){
                std::cout << h.level_up() << std::endl;
            }
            std::cout << h << std::endl;
        }
        {
            for(size_t i{0};i<10;++i){
                Hero h{"Jaina Proudmoore",Hero_Class::WIZARD,Hero_Species::HALF_ELF,69,abilities()};
                h.level_up();
                h.level_up();
                for(size_t j{0};j<10;j++){
                    Elite_Monster m{"Goblin Archer",static_cast<unsigned>(rand()%20+70),static_cast<unsigned>(rand()%6+1),static_cast<unsigned>(rand()%3+1)};
                    std::cout << h.fight(m) << std::endl;
                    std::cout << m << std::endl;
                }
                std::cout << h << std::endl;
            }
        }
    }
    // Campaign Checks
    {
        {
            try{
                Campaign c{"sss",0};
            }catch(const std::runtime_error& e){
                std::cout << "Error Campaign 1" << std::endl;
            }
            try{
                Campaign c{"",1};
            }catch(const std::runtime_error& e){
                std::cout << "Error Campaign 2" << std::endl;
            }
            try{
                Campaign c{"c1",1};
                std::cout << c << std::endl;
                std::cerr << c << std::endl;
            }catch(const std::runtime_error& e){
                std::cout << "Error Campaign 3" << std::endl;
            }
        }
        {
            Campaign c{"Tir nag",5};
            shared_ptr<Hero> h1 = make_shared<Hero>("Jaina Proudmoore",Hero_Class::WIZARD,Hero_Species::HALF_ELF,400,abilities());
            shared_ptr<Hero> h2 = make_shared<Hero>("Arthas",Hero_Class::PALADIN,Hero_Species::HUMAN,1000,abilities());
            shared_ptr<Hero> h3 = make_shared<Hero>("Thrall",Hero_Class::WARLOCK,Hero_Species::HALF_ORC,20,abilities());
            shared_ptr<Hero> h4 = make_shared<Hero>("Sylvanas",Hero_Class::ROGUE,Hero_Species::ELF,100,abilities());
            Elite_Monster m1 = Elite_Monster{"Goblin Archer",110,5,1};
            Elite_Monster m2 = Elite_Monster{"Goblin Elite Archer",500,50,1};
            try{
                c.add_hero(h1);
            }catch(const std::runtime_error& e){
                std::cout << "Error Campaign 4" << std::endl;
            }
            for(size_t i{0};i<5;++i){
                h1->level_up();
                h2->level_up();
                h3->level_up();
                h4->level_up();
            }
            c.add_hero(h1);
            c.add_hero(h2);
            c.add_hero(h3);
            c.add_hero(h4);
            std::cout << c << std::endl;
            c.encounter_monster(h2->get_id(),m1);
            c.encounter_monster(h3->get_id(),m2);
            c.encounter_monster(h4->get_id(),m2);
            c.encounter_monster(h4->get_id(),m2);
            h2.reset();
            std::cout << c << std::endl;
            std::cout << c.remove_dead_and_expired() << std::endl;
            std::cout << c << std::endl;
        }
    }
    //Player Checks
    {
        {
            try{
                Player p1{"","Smith"};
            }catch(const std::runtime_error& e){
                std::cout << "Error Player 1" << std::endl;
            }
            try{
                Player p1{"Smithz",""};
            }catch(const std::runtime_error& e){
                std::cout << "Error Player 2" << std::endl;
            }
        }
        {
            Player p1{"John","Smith"};
            std::cout << p1 << std::endl;
            std::cerr << p1 << std::endl;
            auto h1p1{p1.create_hero("Jaina Proudmoore",Hero_Class::WIZARD,Hero_Species::HALF_ELF,400,abilities())};
            auto h2p1{p1.create_hero("Arthas",Hero_Class::PALADIN,Hero_Species::HUMAN,1000,abilities())};
            std::cout << p1 << std::endl;
            p1.print_campaign(std::cout) << std::endl;
            Player p2{"Jane","Doe"};
            auto h1p2{p2.create_hero("Thrall",Hero_Class::WARLOCK,Hero_Species::HALF_ORC,20,abilities())};
            try{
                p1.join_friends_campaign(p2,h1p1);
            } catch (std::runtime_error& e){
                std::cout << "Error Player 5" << std::endl;
            }
            try{
                p2.create_campaign("Tir nag",5,h1p1+20);
            } catch(std::runtime_error& e){
                std::cout << "Error Player 3" << std::endl;
            }
            try{
                p2.create_campaign("Tir nag",5,h1p2);
            } catch(std::runtime_error& e){
                std::cout << "Error Player 4" << std::endl;
            }
            p2.create_campaign("Tir nag",1,h1p2);
            std::cout << p2 << std::endl;
            try{
                p1.join_friends_campaign(p2,h1p1+10);
            } catch(std::runtime_error& e){
                std::cout << "Error Player 6" << std::endl;
            }
            p1.join_friends_campaign(p2,h1p1);
            p1.join_friends_campaign(p2,h2p1);
            try{
                p1.join_friends_campaign(p2,h1p1);
            } catch(std::runtime_error& e){
                std::cout << "Error Player 7" << std::endl;
            }
            std::cout << p2 << std::endl;
            try{
                p1.transfer_campaign(p2);
            } catch(std::runtime_error& e){
                std::cout << "Error Player 8" << std::endl;
            }
            p2.transfer_campaign(p1);
            std::cout << p2 << std::endl;
            std::cout << p1 << std::endl;

            // to test remove_dead(), the following method in Player can be implemented
            // is is available in the reference implementation
            //void campaign_encounter_monster(unsigned id,Monster& m);
            // throws error if no campaign available, otherwise calls encounter_monster of campaign
            /*
            {
                Elite_Monster m{"Goblin Archer",11000,50,1};
                try{
                    p2.campaign_encounter_monster(h1p2,m);
                } catch(std::runtime_error& e){
                    std::cout << "Error Player 9" << std::endl;
                }
                p1.campaign_encounter_monster(h1p1,m);
                p1.campaign_encounter_monster(h2p1,m);
                p1.campaign_encounter_monster(h1p2,m);
                std::cout << p1 << std::endl;
                std::cout << p1.remove_dead() << std::endl;
                std::cout << p1 << std::endl;
            }
            */
        }
    }
    /*
    std::cout << "-------------------Task 1-------------------" << std::endl;

    {
        vector<shared_ptr<Monster>> vm;
        {
            auto x{task1(vm)};
            for(auto& m:x){
                std::cout << *m << std::endl;
            }
        }
        vm.push_back(make_shared<Standard_Monster>("Goblin Archer",110,5));
        vm.push_back(make_shared<Elite_Monster>("Goblin Elite Archer",110,99,2));
        vm.push_back(make_shared<Standard_Monster>("Blue Dragon",2420,22));
        vm.push_back(make_shared<Elite_Monster>("Young Adult Blue Dragon",24200,222,100));
        {
            auto x{task1(vm)};
            for(auto& m:x){
                std::cout << *m << std::endl;
            }
        }
    }
    */
    /*
    std::cout << "-------------------Task 2-------------------" << std::endl;
    {
        Task3 t1{"Goblin Archer",110,5,1};
        Task3 t2{"Goblin Archer",110,5,3};
        for(size_t i{0};i<10;++i){
            auto x{rand()%10};
            t1.take_damage(x);
            t2.take_damage(x);
            std::cout << t1 << std::endl;
            std::cout << t2 << std::endl;
        }
    }
    */
    /*
    std::cout << "-------------------Task 3-------------------" << std::endl;
    {
        shared_ptr<Hero> h1 = make_shared<Hero>("Jaina Proudmoore",Hero_Class::WIZARD,Hero_Species::HALF_ELF,400,abilities());
        shared_ptr<Hero> h2 = make_shared<Hero>("Arthas",Hero_Class::PALADIN,Hero_Species::HUMAN,1000,abilities());
        shared_ptr<Hero> h3 = make_shared<Hero>("Thrall",Hero_Class::WARLOCK,Hero_Species::HALF_ORC,20,abilities());
        shared_ptr<Hero> h4 = make_shared<Hero>("Sylvanas",Hero_Class::ROGUE,Hero_Species::ELF,100,abilities());
        Super_Task st{{h1,h2,h3,h4}};
        {
            auto x{st.filtering({})};
            for(auto& h:x){
                std::cout << *h << std::endl;
            }
        }
        std::cout<<"-----------------------------------------------" << std::endl;
        {
            auto x{st.filtering({Hero_Class::WIZARD})};
            for(auto& h:x){
                std::cout << *h << std::endl;
            }
        }
        std::cout<<"-----------------------------------------------" << std::endl;
        {
            auto x{st.filtering({Hero_Class::WIZARD,Hero_Class::ROGUE})};
            for(auto& h:x){
                std::cout << *h << std::endl;
            }
        }
        h1.reset();
        std::cout<<"-----------------------------------------------" << std::endl;
        {
            auto x{st.filtering({Hero_Class::WIZARD,Hero_Class::ROGUE})};
            for(auto& h:x){
                std::cout << *h << std::endl;
            }
        }
        std::cout<<"-----------------------------------------------" << std::endl;

    }
    */






    return 0;
}

