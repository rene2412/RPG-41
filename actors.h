#pragma once
#include<string>
#include <vector>
#include <memory>
using namespace std;


class Actor{
	protected: 
	string actorName;
	int hp = 0;
	int speed = 0;
	int dmg = 0;
	public:
	Actor(){//No parameter cstor
		actorName = "";
		hp = 0;
		speed = 0;
	}
	Actor(string newName, int newHp, int newSpeed, int newDmg){//3 parameter cstor
		actorName = newName;
		hp = newHp;
		speed = newSpeed;
		dmg = newDmg;
	}
	const int getHp(){return hp;}// HP getter/setter
	void setHp(int newHp){
		hp = newHp;
	}
	
	const int getSpeed(){return speed;}// speed getter/setter
	void setSpeed(int newSpeed){
		speed = newSpeed;
	}
	const string getName(){return actorName;}//name getter/setter
	void setName(string newName){
		actorName = newName;
	}
	const int getDmg(){return dmg;}// dmg getter/setter
	void setDmg(int newDmg){
		dmg = newDmg;
	}
	

};

class Monster : public Actor{
	private:
		string MonsterType;
		int MonsterLvl = 0;// MIGHT DO DIFFERENT LEVEL MONSTER FOR DIFFERENT LEVEL DIFFICULTY
	public:
	Monster() :  MonsterLvl(1) {} //defualt 
	Monster (string newName, string newMonsterType, int newHp, int newSpeed, int newDmg, int newMonsterLvl) : Actor (newName, newHp, newSpeed, newDmg) {
	MonsterType = newMonsterType;
	MonsterLvl = newMonsterLvl;
	}
	string getMonsterType() const { return MonsterType; }
	void setMonsterType(string newType){
		MonsterType = newType;
	}
	int getMonsterLevel() const { return MonsterLvl; }
	void setMonsterLevel(int level) { 
		MonsterLvl = level;
	} 
};

class Hero : public Actor{
	private:
		string heroType;
		int money = 0;
		int lvl = 1;
	public:
	Hero() : money(0), lvl(1) {} 
 	Hero(string newName, string newHeroType, int newHp, int newSpeed, int newDmg, int newMoney)  : Actor(newName, newHp, newSpeed, newDmg) {
    heroType = newHeroType;
    money = newMoney;
} 
	 int getMoney() const { return money; }
	void setMoney(int newMoney) {
		money = newMoney;
	}
	const int getLevel() const { return lvl; }
 const string getHeroType() const { return heroType; }
	};

void populate_Heroes(vector<unique_ptr<Hero>>& heroes) {
  // create heroes and add them to the vector
  heroes.push_back(make_unique<Hero>("Agent K", "Blade-Runner", 100, 23, 50, 10));
  heroes.push_back(make_unique<Hero>("John Wick", "Hitman", 150, 30, 70, 20));
}
void populate_Monsters(vector<unique_ptr<Monster>>& monsters) {
	// create monsters and add them to a vector 
	monsters.push_back(make_unique<Monster>("Bowser", "Turtle", 200, 10, 45, 15));  
	 monsters.push_back(make_unique<Monster>("Calculus-3", "Math", 1, 1, 999, 3));
}

 void print_Heroes(const vector<unique_ptr<Hero>>& heroes) {
	for (const auto& hero : heroes) {
	cout << "Name: " << hero->getName() <<  " | Type: " << hero->getHeroType() << " | HP: " << hero->getHp() << " | Speed: " << hero->getSpeed() << " | Damage: " << hero->getDmg() << " | Money: " << hero->getMoney() << " | Level: " << hero->getLevel() << endl; 
	}
 }
	void print_Monsters (vector<unique_ptr<Monster>>& monsters) { 
		for (const auto& monster : monsters) { 
			cout << "Name: " << monster->getName() << " | Type: " << monster->getMonsterType() << " | HP: " << monster->getHp() << " | Speed: " << monster->getSpeed() << " | Damage: " << monster->getDmg() << " | Level: " << monster-> getMonsterLevel() << endl;
		}
	}
//WE NEED TO MAEK THE DIFFERENT TYPES FOR MONSTERS AND HEROS AND JUST GIVE THEM MULTIPLIERS TO DAMAGE ETC BANDITS CAN STEAL MONEY AND MONSTERS DO EXTRA DMG // MAGES DO EXTRA MAGIC DMG AND ARE WEAKER DEFENSE // CHADS ARE GOOD AT DMG THTHATS IT
