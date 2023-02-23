//Put your name(s) here: Rene Hernandez
//What bullet points did you do: 1, 2, 3, 4, 5 + 2 extra credit bullets
//Delete this next line to let the code compile
//#error Delete This!
#include "map.h"
#include <unistd.h>
#include "actors.h"
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
	clear();
	noecho();
	cbreak();
	timeout(TIMEOUT); //Set a max delay for key entry
}

//Exit full screen mode - also do this if you ever want to use cout or gtest or something
void turn_off_ncurses() {
	clear();
	endwin(); // End curses mode
	if (system("clear")) {}
}
void check() {
cout << "BAD INPUT! Please select a valid Hero" << endl;
exit(1);
}
void interact(Map& curMap, int x, int y, char collision, vector<unique_ptr<Hero>>& heroes, vector<unique_ptr<Monster>>& monsters) {
    turn_off_ncurses();
	if (curMap.get_character(x, y) == collision) {
        if (collision == 'M') {
			turn_off_ncurses();
            cout << "There is a MONSTER! The Monster is unknown. PREPARE TO FIGHT!!" << endl;
			cin.get(); //wait for user to read the prompt and press enter when ready to continue, so the output wont be messy 
	  }	else if (collision == '$') {
            cout << "You found LOOT!" << endl;
        } else if (collision == '#') {
            cout << "You hit a WALL!" << endl;
		}
		 int choice = 0;
        cout << "Chose your Hero to fight the monster: " << endl;
		cin.get();
        cout << "Heroes: " << endl;
		print_Heroes(heroes);
		cout << "Monsters: " << endl;
		print_Monsters(monsters);
		cout << "1) Supa " << endl;
		cout << "2) Agent-K " << endl;
        cin >> choice;
        if (!cin or choice > heroes.size() or choice < 1) check();
        //Hero* selectedHero points to the object of heroes[choice - 1]
		//Since index start at 1, we subtrcat 1 from the users choice to get the right index 
		//NOTE: selectedHero now holds the users hero choice and holds the heros stats
		//Finally .get() gets the pointer that was stored in the unique_ptr vector 
		Hero* selectedHero = heroes[choice - 1].get();
        cout << "You have selected: "<< selectedHero->getName() << " as your Hero!" << endl;
		cin.get();
		int ready = 0;
		cout << "Press 5) to fight the monster or 6) to Quit" << endl;
		cin >> ready;
		if (ready == 5) { 
		clear();
		//This will be our combat function
		}
		else if (ready == 6) {
			save_Heroes(heroes);
			save_Monsters(monsters);
			curMap.save_map();
			exit(1);
		}
        curMap.set_character(y, x, '.');
	}
		sleep(10);
        turn_on_ncurses();
		
	}
	
	void combat(vector<unique_ptr<Hero>> &heroes, vector<unique_ptr<Monster>>& monsters) {
	//combat function between heroes vs monsters
	
	}

int main() {
vector<unique_ptr<Hero>> heroes; //Holds data for the heroes
populate_Heroes(heroes);

vector<unique_ptr<Monster>> monsters; //Holds data for the monsters 
populate_Monsters(monsters);	
    turn_on_ncurses(); //DON'T DO CIN or COUT WHEN NCURSES MODE IS ON
	Map map;
	int x = Map::SIZE / 2, y = Map::SIZE / 2; //Start in middle of the world
	int old_x = -1, old_y = -1;
  	map.set_character(20,20,'$');
	map.set_character(20,21,'L');
	map.set_character(45,45,'M');
	map.set_character(20,23,'L');
	map.set_character(20,24,'M');
	map.set_character(20,25,'L');
	map.set_character(21,20,'#');
	map.set_character(21,22,'#');
	bool quit = false;
	while (true) {
		int ch = getch(); // Wait for user input, with TIMEOUT delay
		if (ch == 'q' || ch == 'Q') { 
			quit == true; break; 
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
			/*If you want to do cin and cout, turn off ncurses, do your thing, then turn it back on
			turn_off_ncurses();
			string s;
			cin >> s;
			cout << s << endl;
			sleep(1);
			turn_on_ncurses();
			*/
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
			interact(map,x,y,'M', heroes, monsters);
			}
			if (map.get_character(x,y) == Map::WALL) {
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
