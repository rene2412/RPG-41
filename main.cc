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

void interact(Map& curMap,int x , int y, char z){
	if(curMap.get_character(x,y) == z){
		turn_off_ncurses();
//		string s;
//		cin >> s;
//		cout << s << endl;
		if(z == '$'){
			cout << "you picked up moneees " << endl;
			curMap.set_character(y,x,'.');//set spot empty
		}
		if(z == 'M'){//if collision is with monster
			cout << "time to fight" << endl;
			cout << "you slayed the beast" << endl;
			curMap.set_character(y,x,'.');//set spot empty
		}
		sleep(1);
		turn_on_ncurses();		
	}
}


int main() {
vector<unique_ptr<Hero>> heroes;
populateHeroes(heroes);
turn_on_ncurses(); //DON'T DO CIN or COUT WHEN NCURSES MODE IS ON
	Map map;
	int x = Map::SIZE / 2, y = Map::SIZE / 2; //Start in middle of the world
	int old_x = -1, old_y = -1;
	map.set_character(20,20,'$');
	map.set_character(20,21,'L');
	map.set_character(20,22,'M');
	map.set_character(20,23,'L');
	map.set_character(20,24,'M');
	map.set_character(20,25,'L');
	map.set_character(21,20,'#');
	map.set_character(21,22,'#');
	while (true) {
		int ch = getch(); // Wait for user input, with TIMEOUT delay
		if (ch == 'q' || ch == 'Q') break;
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
			interact(map,x,y,'M');
			interact(map,x,y,'$');
			/*Do something like this, idk 
			if (map.get_character(x,y) == 'L') {
				turn_off_ncurses();
				string s;
				cout << "ITS A MONSTER" << endl;
				cin >> s;
				cout << s << endl;
				sleep(1);
				turn_on_ncurses();
			} */
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
