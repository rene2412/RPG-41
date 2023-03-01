//Put your name(s) here: Rene Hernandez
//What bullet points did you do: 1, 2, 3, 4, 5 + 2 extra credit bullets
#include "map.h"
#include "linked_list.h"
#include "combat.h"
#include <unistd.h>
#include "actors.h"
#include <algorithm>
#include <cctype>
const int MAX_FPS = 90; //Cap frame rate 
const unsigned int TIMEOUT = 10; //Milliseconds to wait for a getch to finish
const int UP = 65; //Key code for up arrow
const int DOWN = 66;
const int LEFT = 68;
const int RIGHT = 67;

//Turns on full screen text mode
void turn_on_ncurses() {
	initscr();//Start curses mode
	start_color(); //Enable Colors if possible
	init_pair(1,COLOR_WHITE,COLOR_BLACK); //Set up some color pairs
	init_pair(2,COLOR_CYAN,COLOR_BLACK);
	init_pair(3,COLOR_GREEN,COLOR_BLACK);
	init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	init_pair(5,COLOR_RED,COLOR_BLACK);
	init_pair(6,COLOR_MAGENTA,COLOR_BLACK);
	init_pair(7,COLOR_BLACK,COLOR_BLACK);// FLOOR COLOR
	init_pair(8,COLOR_MAGENTA,COLOR_BLACK);// GREEN
	clear();
	noecho();
	cbreak();
	timeout(TIMEOUT); //Set a max delay for key entry
}

void die(){cout << "SOmEtHinG WenT wRoNG " << endl; exit (0);} 
//Exit full screen mode - also do this if you ever want to use cout or gtest or something
void turn_off_ncurses() {
	clear();
	endwin(); // End curses mode
	if (system("clear")) {}
}
void check() {
	cout << "Cmon Man" << endl;
	exit(1);
}

int money = 0; // keep track of main characters money

void interact(Map& curMap, int x, int y, char collision, vector<shared_ptr<Hero>>& heroes, vector<shared_ptr<Monster>>& monsters) {
	turn_off_ncurses();
	int select = 0;
	if (curMap.get_character(x, y) == collision) {
		if (collision == 'M') {
			cout << "There is a MONSTER! The Monster is unknown. PREPARE TO FIGHT!!" << endl;
			//combat	
		}
		if (collision == '?') { 
			money += 50;
			cout << "You found Money! You now have $" << money << " eddies!" << endl;
			sleep(3); 
			cout <<"Go enjoy a nice a bowl of Ramen or spend some time at the spa to heal your Heroes!" << endl;
			sleep(6);
		}
		if (collision == 'F') {
			string choice;
			cout << "Welcome to the Chinese Ramen!" << endl;
			cin.get();
			cout << "Are you here to try our special Ramen that heals Heroes!?" << endl;
			cout << "Yes or No" << endl;
			cin >> choice;
			if (choice == "Yes" || choice == "yes") {
				if (money < 45) {
					cout << "You don't have enough money to buy ramen!" << endl;
				}
				else {
					for (const auto& hero : heroes) {
						hero->setHp(100);
					}
					money -= 45;
					cout << "Your Heroes are all healed! You now have $" << money << " eddies!" << endl;
				}
			}
			else if (choice == "No" || choice == "no") {
				cout << "Your LOSS!" << endl;
			}
		}

	if (collision == 'S') {
		string choice;
		cout << "Welcome to the Spa!" << endl;
		cin.get();
		cout << "Are you here to get one of our legendary spas that heals Heroes!?" << endl;
		while (true) {
			cin >> choice;
			if (choice == "Yes" || choice == "yes") {
				for (const auto& hero : heroes) {
					hero->setHp(100);
				}
				cout << "Your Heroes are all healed!" << endl;
				break; 
			}
			else if (choice == "No" || choice == "no") {
				cout << "Your LOSS!" << endl;
				break; 
			}
			else {
				cout << "Invalid input. Please enter Yes or No." << endl;
			}
		}
	}
	if (select == 6) {
		save_Heroes(heroes);
		save_Monsters(monsters);
		curMap.save_map();
		exit(1);
	}
	curMap.set_character(y, x, '.');
	sleep(1);
	turn_on_ncurses();
		}
	}

bool speed_sort(const shared_ptr<Actor> &lhs, const shared_ptr<Actor> &rhs){
	return lhs->getSpeed() <  rhs->getSpeed();
}
bool speed_sort2(const shared_ptr<Hero> &lhs, const shared_ptr<Hero> &rhs){
	return lhs->getSpeed() <  rhs->getSpeed();
}
bool speed_sort3(const shared_ptr<Monster> &lhs, const shared_ptr<Monster> &rhs){
	return lhs->getSpeed() <  rhs->getSpeed();
}
int main() {
	linkedList list;
	Hero_linkedList list2;
	Monster_linkedList list3;
    vector<shared_ptr<Hero>> heroes; //Holds data for the heroes

	vector<shared_ptr<Monster>> monsters; //Holds data for the monsters 
	populate_Heroes(heroes,0); //test
	populate_Monsters(monsters,0); //test
	vector<shared_ptr<Actor>> all; //Holds data for all
	populate_all(all,monsters,heroes);
	sort(all.rbegin(), all.rend(), speed_sort);
	sort(heroes.rbegin(), heroes.rend(), speed_sort2);
	sort(monsters.rbegin(), monsters.rend(), speed_sort3);
	//cout << "This is sorted: "  << endl;
	//print_all(all); cout << endl;
	//cout << "This is the sorted Heroes: " << endl;
	//print_Heroes(heroes); cout << endl;
	//cout << "This is the sorted Monsters: " << endl;
	//print_Monsters(monsters); cout << endl;
	for (const auto& x : all){
		list.push_back(x);
	}
	for (const auto& y : heroes) { 
		list2.push_back(y);
	}
	for (const auto& z : monsters) {
		list3.push_back(z);
	}
	//begin_combat(list, list2, list3, all, heroes, monsters);	

	//list.printLL();

	cout << "WELCOME TO THE GAME\n" << "Press: 0 for a New game, Press: 1 to load a game" << endl;
	int slct = 0;
	cin >> slct;
	if (slct>1 || slct < 0){cout << "SOmEtHinG WenT wRoNG " << endl; exit (0);} 
	if (!cin){cout << "SOmEtHinG WenT wRoNG " << endl; exit (0);} 
	Map map(slct);
	populate_Heroes(heroes,slct);
	populate_Monsters(monsters,slct);

	turn_on_ncurses(); //DON'T DO CIN or COUT WHEN NCURSES MODE IS ON
	int x = Map::SIZE / 2, y = Map::SIZE / 2; //Start in middle of the world
	int old_x = -1, old_y = -1;
	bool quit = false;
	while (true) {
		int ch = getch(); // Wait for user input, with TIMEOUT delay
		if (ch == 'q' || ch == 'Q') { 
			save_Heroes(heroes);
			save_Monsters(monsters);
			map.save_map();
			exit(1);
		} 
		else if (ch == RIGHT) {
			x++;
			if (x >= Map::SIZE) x = Map::SIZE - 1; //Clamp value
		}
		else if (ch == LEFT) {
			x--;
			if (x < 0) x = 0;
		}
		else if (ch == UP) {
			y--;
			if (y < 0) y = 0;
		}
		else if (ch == DOWN) {
			y++;
			if (y >= Map::SIZE) y = Map::SIZE - 1; //Clamp value
		}
		else if (ch == ERR) { //No keystroke
			; //Do nothing
		}
		//Stop flickering by only redrawing on a change
		if (x != old_x or y != old_y) {
			if (map.get_character(x,y) == 'M') {
				turn_off_ncurses();	
				begin_combat(list, list2, list3, all, heroes, monsters);
				for (auto& monster : monsters) {
                monster-> setHp(100);
				}
			    map.set_character(x, y, '.');	
				turn_on_ncurses();
			}
			if (map.get_character(x,y) == '?') {
				turn_off_ncurses();
				interact(map,x,y,'?', heroes, monsters);
				 map.set_character(x, y, '.');
				turn_on_ncurses();
			}
			if (map.get_character(x,y) == 'F') {
				turn_off_ncurses(); 
				interact(map,x,y,'F', heroes, monsters);
				 map.set_character(x, y, '.');
				turn_on_ncurses();
			}
			if (map.get_character(x,y) == 'S') {
				turn_off_ncurses();
				interact(map,x,y,'S', heroes, monsters);
				 map.set_character(x, y, '.');
				turn_on_ncurses(); 
			}
			if (map.get_character(x,y) == '/' or map.get_character(x,y) == '-' or map.get_character(x,y) == '+' or map.get_character(x,y) == '|' or map.get_character(x,y) == '\\') {
				x = old_x;
				y = old_y;
			}
			//clear(); //Put this in if the screen is getting corrupted
			map.draw(x,y);
			mvprintw(Map::DISPLAY+1,0,"X: %i Y: %i\n",x,y);
			refresh();
		}
		old_x = x;
		old_y = y;
		usleep(1'000'000/MAX_FPS);
	}
	turn_off_ncurses();
}

