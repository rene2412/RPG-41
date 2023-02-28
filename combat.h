#pragma once
#include "actors.h"
#include "linked_list.h"
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

void begin_combat(linkedList &list, vector<shared_ptr<Actor>> &all, vector<unique_ptr<Hero>> &heroes, vector<unique_ptr<Monster>> &monsters) {
  	 	
	cout << "List ALL: " << endl;
	list.printLL();
	cin.get();
	cout << "List Heroes: " << endl;
	// We need to sort via heroes and monsters SEPERATELY or else the combat will not ordered 
	cin.get();
	cout << "List Monsters: " << endl;
	
	cin.get();
	cout << "WELCOME TO THE FIGHT ZONE" << endl;
	cin.get();
	cout << "Hero: " << heroes.at(0)->getName() << " VS Monster: " << monsters.at(0)->getName() << endl;
    cin.get();
	cout << heroes.at(0)->getName() << " HP: " << heroes.at(0)->getHp() << " | " << monsters.at(0)->getName() << " HP: " << monsters.at(0)->getHp() << endl;

	while (heroes.at(0)->getHp() > 0 and monsters.at(0)->getHp() > 0) {
    // hero attacks monster
    int hero_dmg = heroes.at(0)->getDmg() * 0.89;
    int monster_hp = monsters.at(0)->getHp() - hero_dmg;
    cout << heroes.at(0)->getName() << " strikes " << monsters.at(0)->getName() << " for " << hero_dmg << " damage!" << endl;
    monsters.at(0)->setHp(monster_hp);
    cin.get();
	cout << monsters.at(0)->getName() << " health is now: " << monster_hp << endl;
	cin.get();
    // check if monster is still alive
    if (monsters.at(0)->getHp() <= 0) {
        cout << monsters.at(0)->getName() << " has been defeated!" << endl;     
	break;
    }

    // monster attacks hero
    int monster_dmg = monsters.at(0)->getDmg() * 0.89;
    int hero_hp = heroes.at(0)->getHp() - monster_dmg;
    cout << monsters.at(0)->getName() << " strikes " << heroes.at(0)->getName() << " for " << monster_dmg << " damage!" << endl;
    cin.get();
	heroes.at(0)->setHp(hero_hp);
    cout << heroes.at(0)->getName() << " health is now: " << hero_hp << endl;
	cin.get();
    // check if hero is still alive
    if (heroes.at(0)->getHp() <= 0) {
        cout << heroes.at(0)->getName() << " has been defeated!" << endl;
        break;
    	}
	}
}

