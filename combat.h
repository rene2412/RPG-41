#pragma once
#include "actors.h"
#include "linked_list.h"
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;
void begin_combat(linkedList &list, Hero_linkedList &list2, Monster_linkedList& list3, vector<shared_ptr<Actor>> &all, vector<shared_ptr<Hero>> &heroes, vector<shared_ptr<Monster>> &monsters) {
    int curHero = 0;//RECIEVER
    int curMonster = 0;//IS THE ONE WHO TAKES DAMAGE
    int turn = 0;
    int curOrder = 0;
    int recHero = 0;//SHOULD OF NAMED AS ATTACKER
    int recMonster = 0;//not rec but ATTACKER
    cout << "Turn order: " << endl;
    list.printLL();
    cin.get();
    cout << "Your Crew: " << endl;
    // We need to sort via heroes and monsters SEPERATELY or else the combat will not ordered
    list2.printLL();
    cin.get();
    cout << "Enemies: " << endl;
    list3.printLL();
    cin.get();
    cout << "WELCOME TO THE FIGHT ZONE" << endl;
    cin.get();
    cout << "Hero: " << heroes.at(curHero)->getName() << " VS Monster: " << monsters.at(curMonster)->getName() << endl;
    cin.get();
    cout << heroes.at(curHero)->getName() << " HP: " << heroes.at(curHero)->getHp() << " | " << monsters.at(curMonster)->getName() << " HP: " << monsters.at(curMonster)->getHp() << endl;
    //if (heroes.at(curHero)->getSpeed() >= monsters.at(curMonster)->getSpeed()) {turn = 1; cout << heroes.at(curHero)->getName() << " is faster" << endl;}// TURN DECIDERS
    //else if (heroes.at(curHero)->getSpeed() < monsters.at(curMonster)->getSpeed()){ turn = 2; cout << monsters.at(curMonster)->getName()<< " is quick to strike!" << endl;}// TURN DECIDE
    while(curHero < heroes.size() and curMonster < monsters.size()){// will go throught the whole vector
        if (all.at(curOrder)->getName() == heroes.at(recHero)->getName()and heroes.at(recHero)->getHp() > 0){
            turn = 1;
            curOrder++;
            if(curOrder >= all.size()) curOrder = 0;
        }
else if (all.at(curOrder)->getName() == monsters.at(recMonster)->getName()and monsters.at(recMonster)->getHp() > 0){
            turn = 2;
            curOrder++;
            if(curOrder >= all.size()) curOrder = 0;
        }
        else if (all.at(curOrder)->getName() == monsters.at(recMonster)->getName()and monsters.at(recMonster)->getHp() <= 0){
            //cout << " recMonster " << recMonster << endl;
            //cout << " recHero " << recHero << endl;
            //cout << " curOrder " << curOrder << endl;
            recMonster++;
            if(recMonster >= monsters.size()) recMonster = 0;
            curOrder++;
            if(curOrder >= all.size()) curOrder = 0;
            continue;
        }
        else if (all.at(curOrder)->getName() == heroes.at(recHero)->getName()and heroes.at(recHero)->getHp() <= 0){
            //cout << " recMonster " << recMonster << endl;
            //cout << " recHero " << recHero << endl;
            //cout << " curOrder " << curOrder << endl;
            recHero++;
            if(recHero >= monsters.size()) recHero = 0;
            curOrder++;
            if(curOrder >= all.size()) curOrder = 0;
            continue;
        }
		 //else curOrder++;
        while (heroes.at(curHero)->getHp() > 0 and monsters.at(curMonster)->getHp() > 0) {
        //  list.printLL();
            if(turn == 1){
                //list.printLL();
                // hero attacks monster
                int hero_dmg = heroes.at(recHero)->getDmg() * 0.89;
                int monster_hp = monsters.at(curMonster)->getHp() - hero_dmg;
                cout << heroes.at(recHero)->getName() << " strikes " << monsters.at(curMonster)->getName() << " for " << hero_dmg << " damage!" << endl;
                monsters.at(curMonster)->setHp(monster_hp);
                cin.get();
                if(monster_hp < 0) cout << monsters.at(curMonster)->getName() << " health is now: " << 0 << endl;//HP bound check to 0
                else cout << monsters.at(curMonster)->getName() << " health is now: " << monster_hp << endl;//
                cin.get();
                // check if monster is still alive
                if (monsters.at(curMonster)->getHp() <= 0) {
                    cout << monsters.at(curMonster)->getName() << " has been defeated!" << endl;
                    for (const auto& x : all){
                        if (x->getName() == monsters.at(curMonster)->getName())x->setHp(0);
                    }
                curMonster++;
                    recHero = recHero + 1;
                    if(recHero >= heroes.size())recHero=0;
                    break;
                }
                recHero = recHero + 1;
                if(recHero >= heroes.size())recHero=0;
                break;
            }
            if (turn == 2){
                //list.printLL();
                // monster attacks hero
                int monster_dmg = monsters.at(recMonster)->getDmg() * 0.89;
                int hero_hp = heroes.at(curHero)->getHp() - monster_dmg;
                cout << monsters.at(recMonster)->getName() << " strikes " << heroes.at(curHero)->getName() << " for " << monster_dmg << " damage!" << endl;
                cin.get();
				heroes.at(curHero)->setHp(hero_hp);
                if(hero_hp < 0)cout << heroes.at(curHero)->getName() << " health is now: " << 0 << endl;//HP bound check to 0
                else cout << heroes.at(curHero)->getName() << " health is now: " << hero_hp << endl;//
                cin.get();
// check if hero is still alive
                if (heroes.at(curHero)->getHp() <= 0) {
                    cout << heroes.at(curHero)->getName() << " has been defeated!" << endl;
                    for (const auto& x : all){
                        if (x->getName() == heroes.at(curHero)->getName())x->setHp(0);
                    }
                    curHero++;
                    recMonster = recMonster+1;
                    if(recMonster >= monsters.size())recMonster=0;
                    break;
                }
                recMonster = recMonster+1;
                if(recMonster >= monsters.size())recMonster=0;
                break;
            }
        }
    }
}
