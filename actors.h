#pragma once
#include<string>
#include <vector>
#include <memory>
#include<fstream>
#include<sstream>
using namespace std;


class Actor {
	protected: 
		string actorName;
		int hp = 0;
		int speed = 0;
		int dmg = 0;
		int def = 0;
	public:
	Actor(){//No parameter cstor
		actorName = "";
		hp = 0;
		speed = 0;
	}
	Actor(string newName, int newHp, int newSpeed, int newDmg,int newDef){//3 parameter cstor
		actorName = newName;
		hp = newHp;
		speed = newSpeed;
		dmg = newDmg;
		def = newDef;
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
	const int getDef(){return def;}// def getter/setter
	void setDef(int newDef){
		def = newDef;
	}
	

};

class Monster : public Actor {
	private:
		string MonsterType;
		int MonsterLvl = 0;// MIGHT DO DIFFERENT LEVEL MONSTER FOR DIFFERENT LEVEL DIFFICULTY
	public:
	Monster() :  MonsterLvl(1) {} //defualt 
	Monster (string newName, string newMonsterType, int newHp, int newSpeed, int newDmg, int newDef, int newMonsterLvl) : Actor (newName, newHp, newSpeed, newDmg, newDef) {
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
 	Hero(string newName, string newHeroType, int newHp, int newSpeed, int newDmg,int newDef, int newMoney)  : Actor(newName, newHp, newSpeed, newDmg, newDef) {
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

void populate_Heroes(vector<shared_ptr<Hero>>& heroes,int x) {
 	string fileInput;// file stream for heroes and objects of it
	string choice;
	if (x == 0) choice = "dheroes.txt";
	if (x == 1) choice = "heroes.txt";
	ifstream fs(choice);
	if(fs.is_open()){
		while(!fs.eof()){
			string name;string heroType;
			string hp; string speed; string dmg; string def; string money;
			getline(fs, fileInput);
			stringstream s(fileInput);
			s >> name >> heroType >> hp >> speed >> dmg >> def >> money;
			if(name == "")break;//check eof
	heroes.push_back(make_shared<Hero>(name, heroType, stoi(hp) , stoi(speed), stoi(dmg),stoi(def),stoi(money)));
		}
	fs.close();
	}
	//WHEN MAKING HEROES OR MONSTERS DO NOT USE SPACES SO USE SINGLE NAME FOR NOW BOTH HERO AND MONSTER
	// create heroes and add them to the vector
  	//  heroes.push_back(make_unique<Hero>("Agent K", "Blade-Runner", 100, 23, 50,25, 10));
}

void save_Heroes(vector<shared_ptr<Hero>>& heroes){
	ofstream ofs("heroes.txt");
	//ofs << endl;
	if(ofs.is_open()){
		for (const auto& hero : heroes){
			ofs << hero->getName() << " " << hero->getHeroType() << " "<< hero->getHp() << " " << hero->getSpeed() << " " << hero->getDmg() << " " << hero->getDef()<< " " << hero->getMoney() << endl;
		}
	ofs.close();
	}
}


void populate_Monsters(vector<shared_ptr<Monster>>& monsters,int x) {
 	string fileInput;// Block of code to read in monsters from monsters.txt
	string choice;
	if (x == 0) choice = "dmonsters.txt";
	if (x == 1) choice = "monsters.txt";
	ifstream fs(choice);
	if(fs.is_open()){
		while(!fs.eof()){
			string name;string monsterType;
			string hp; string speed; string dmg; string def; string monsterLvl;
			getline(fs, fileInput);
			stringstream s(fileInput);
			s >> name >> monsterType >> hp >> speed >> dmg >> def >> monsterLvl;
			if(name == "")break;//check eof
monsters.push_back(make_shared<Monster>(name, monsterType, stoi(hp) , stoi(speed), stoi(dmg),stoi(def),stoi(monsterLvl)));
		}
	fs.close();
	}
	// create monsters and add them to a vector 
   //monsters.push_back(make_unique<Monster>("Bowser", "Turtle", 200, 10, 45, 25, 15));  
}

void save_Monsters(vector<shared_ptr<Monster>>& monsters){
	ofstream ofs("monsters.txt");
	//ofs << endl;
	if(ofs.is_open()){
		for (const auto& monster : monsters){
			ofs << monster->getName() << " " << monster->getMonsterType() << " "<< monster->getHp() << " " << monster->getSpeed() << " " << monster->getDmg() << " " << monster->getDef()<< " " << monster-> getMonsterLevel() << endl;
		}
	ofs.close();
	}
}

 void print_Heroes(const vector<shared_ptr<Hero>>& heroes) {
	 for (const auto& hero : heroes) {
	cout << "Name: " << hero->getName() <<  " | Type: " << hero->getHeroType() << " | HP: " << hero->getHp() << " | Speed: " << hero->getSpeed() << " | Damage: " << hero->getDmg() << " | Money: " << hero->getMoney() << " | Defense:" << hero->getDef() <<  " | Level: " << hero->getLevel() << endl; 
	}\
 }
	void print_Monsters (vector<shared_ptr<Monster>>& monsters) { 
		for (const auto& monster : monsters) { 
				cout << "Name: " << monster->getName() << " | Type: " << monster->getMonsterType() << " | HP: " << monster->getHp() << " | Speed: " << monster->getSpeed() << " | Damage: " << monster->getDmg() << " | Level: " << monster-> getMonsterLevel() << endl;
		}
	}
void populate_all(vector<shared_ptr<Actor>>& all,vector<shared_ptr<Monster>>& monsters,vector<shared_ptr<Hero>>& heroes){

	for (const auto& x : heroes){
	all.push_back(make_shared<Hero>(*x)); //Basically, shared pointers mean that it contains pointers to objects 
	//we take in a pointer x since an object of Hero cant be stored directly into the vector. However, shared_ptr derefences Hero and creates a new object that is valid to now enter the vector 
	//therefore to access a shared pointer (I only know one way at the moment lol) we cant use ->. Because the arrow operator allows access to all member functions. which is 
	//invalid for shared_pointers. We pretty much need special premission to access our new shared_ptr vector now. We do that by deferencing using the *. 
	//Which allows access for member function like getName to enter the new vector. Hope this little explanation helped :D
	//Now that Im reading it back it sounds confusing 🗿. I can explain better over call lol
	}
	for (const auto& x : monsters){
	all.push_back(make_shared<Monster>(*x));
	}
}
void print_all(vector<shared_ptr<Actor>>& all){
	for (const auto&x : all){
	cout << "Name: " <<  (*x).getName() << " | HP: " <<  (*x).getHp()  << " | Speed: " << (*x).getSpeed() << " | Damage: " << (*x).getDmg() <<  endl;
	}
}

