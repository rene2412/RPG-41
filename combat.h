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
	int curHero = 0;
	int curMonster = 0;
	int turn = 0;
	cout << "List of Actors: " << endl;
	list.printLL();
	cin.get();
	cout << "List of Heroes: " << endl;
	// We need to sort via heroes and monsters SEPERATELY or else the combat will not ordered 
	list2.printLL();
	cin.get();
	cout << "List of Monsters: " << endl;
	list3.printLL();
	cin.get();
	cout << "WELCOME TO THE FIGHT ZONE" << endl;
	cin.get();
	cout << "Hero: " << heroes.at(curHero)->getName() << " VS Monster: " << monsters.at(curMonster)->getName() << endl;
	cin.get();
	cout << heroes.at(curHero)->getName() << " HP: " << heroes.at(curHero)->getHp() << " | " << monsters.at(curMonster)->getName() << " HP: " << monsters.at(curMonster)->getHp() << endl;
while(curHero < heroes.size() and curMonster < monsters.size()){// will go throught the whole vector
	if (heroes.at(curHero)->getSpeed() >= monsters.at(curMonster)->getSpeed()) {turn = 1; cout << heroes.at(curHero)->getName() << " is faster" << endl;}// TURN DECIDERS
	else if (heroes.at(curHero)->getSpeed() < monsters.at(curMonster)->getSpeed()){ turn = 2; cout << monsters.at(curMonster)->getName()<< " is quick to strike!" << endl;}// TURN DECIDE
	while (heroes.at(curHero)->getHp() > 0 and monsters.at(curMonster)->getHp() > 0) {
		if(turn == 1){
			// hero attacks monster
			int hero_dmg = heroes.at(curHero)->getDmg() * 0.89;
			int monster_hp = monsters.at(curMonster)->getHp() - hero_dmg;
			cout << heroes.at(curHero)->getName() << " strikes " << monsters.at(curMonster)->getName() << " for " << hero_dmg << " damage!" << endl;
			monsters.at(curMonster)->setHp(monster_hp);
			cin.get();
			if(monster_hp < 0) cout << monsters.at(curMonster)->getName() << " health is now: " << 0 << endl;//HP bound check to 0
			else cout << monsters.at(curMonster)->getName() << " health is now: " << monster_hp << endl;//
			cin.get();
			// check if monster is still alive
			if (monsters.at(curMonster)->getHp() <= 0) {
				cout << monsters.at(curMonster)->getName() << " has been defeated!" << endl;     
				curMonster++;
				break;
			}
			turn = 2;
		}
		if (turn == 2){
			// monster attacks hero
			int monster_dmg = monsters.at(curMonster)->getDmg() * 0.89;
			int hero_hp = heroes.at(curHero)->getHp() - monster_dmg;
			cout << monsters.at(curMonster)->getName() << " strikes " << heroes.at(curHero)->getName() << " for " << monster_dmg << " damage!" << endl;
			cin.get();
			heroes.at(curHero)->setHp(hero_hp);
			if(hero_hp < 0)cout << heroes.at(curHero)->getName() << " health is now: " << 0 << endl;//HP bound check to 0
			else cout << heroes.at(curHero)->getName() << " health is now: " << hero_hp << endl;//
			cin.get();
			// check if hero is still alive
			if (heroes.at(curHero)->getHp() <= 0) {
				cout << heroes.at(curHero)->getName() << " has been defeated!" << endl;
				curHero++;
				break;
			}
			turn = 1;
			}
		}
	}
}

