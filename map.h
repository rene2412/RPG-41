#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include<fstream>
#include <ncurses.h>
using namespace std; //Boo hiss

class Map {
	vector<vector<char>> map;
	default_random_engine gen;
	public:
	//TODO: Write a getter and a setter to get/set the characters in the map
	void set_character(int x, int y, char temp){
		map.at(x).at(y) = temp;
	}
	char get_character(int x , int y){
		return map.at(y).at(x);
	}

	void load_map(int x){
	string choice;
	if (x == 0) choice = "dmap.txt";// reset and load default map
	if (x == 1) choice = "map.txt";// load the saved map
	ifstream ifs(choice);
	int i = 0;
	int j = 0;
	while(!ifs.eof()){
			char temp;
			ifs >> temp;
			if (i == SIZE/2 and j == SIZE/2){map.at(i).at(j) = HERO;}
			else map.at(i).at(j) = temp; 
			if (j < 100) j++;
			if (j == 100){i++; j = 0;}
			if (i >= 100) break;
	}
	ifs.close();
}

	void save_map(){
		ofstream ofs("map.txt");
		if(ofs.is_open()){
		for (size_t i = 0; i < SIZE; i++) {
			for (size_t j = 0; j < SIZE; j++) {
			ofs << map.at(i).at(j);
			}
		ofs << endl;
		}
	ofs.close();
	}
}


	//TODO: Write a function to save the map and reload the map
	static const char HERO     = 'H';
	static const char MONSTER  = 'M';
	static const char WALL     = '#';
	static const char WATER    = '~';
	static const char OPEN     = '.';
	static const char TREASURE = '?';
	static const char Food     = 'F';
	static const char Spa	   = 'S';
	static const size_t SIZE = 100; //World is a 100x100 map
	static const size_t DISPLAY = 99; //Show a 30x30 area at a time
	//Randomly generate map
	void init_map() {
		uniform_int_distribution<int> d100(1,100);
		map.clear();
		map.resize(SIZE); //100 rows tall
		for (auto &v : map) v.resize(SIZE,'.'); //100 columns wide
		for (size_t i = 0; i < SIZE; i++) {
			for (size_t j = 0; j < SIZE; j++) {
				//Line the map with walls
				if (i == 0 or j == 0 or i == SIZE-1 or j == SIZE-1) 
					map.at(i).at(j) = WALL;
				else if (i == SIZE/2 and j == SIZE/2) 
					map.at(i).at(j) = HERO;
				else {/*
					//5% chance of monster
					if (d100(gen) <= 5) {
						map.at(i).at(j) = MONSTER;
					}
					else if (d100(gen) <= 3) {
						map.at(i).at(j) = TREASURE;
					}
					else if (d100(gen) <= 10) { //10% each spot is wall
						map.at(i).at(j) = WALL;
					}
					else if (d100(gen) <= 3) { //3% each spot is water
						map.at(i).at(j) = WATER;
					}
					else if (d100(gen) <= 40) { //40% chance of water near other water
						if (map.at(i-1).at(j) == WATER or map.at(i+1).at(j) == WATER or map.at(i).at(j-1) == WATER or map.at(i).at(j+1) == WATER)
							map.at(i).at(j) = WATER;
					}*/
					map.at(i).at(j) = OPEN;
				}
			}
		}
	}
	//Draw the DISPLAY tiles around coordinate (x,y)
	void draw(int x, int y) {
		int start_x = x - DISPLAY/2;
		int end_x = x + DISPLAY/2;
		int start_y = y - DISPLAY/2;
		int end_y = y + DISPLAY/2;

		//Bounds check to handle the edges
		if (start_x < 0) {
			end_x = end_x - start_x;
			start_x = 0;
		}
		if (end_x > SIZE-1) {
			start_x = start_x - (end_x - (SIZE-1));
			end_x = SIZE-1;
		}
		if (start_y < 0) {
			end_y = end_y - start_y;
			start_y = 0;
		}
		if (end_y > SIZE-1) {
			start_y = start_y - (end_y - (SIZE-1));
			end_y = SIZE-1;
		}

		//Now draw the map using NCURSES
		for (size_t i = start_y; i <= end_y; i++) {
			for (size_t j = start_x; j <= end_x; j++) {
				if (i == y && j == x) {
					attron(A_UNDERLINE | A_BOLD);
					mvaddch(i-start_y,j-start_x,'H');
					attroff(A_UNDERLINE | A_BOLD);
				}
				else {
					int color = 1;
					if (map.at(i).at(j) == WALL)
						color =8 ;
					else if (map.at(i).at(j) == WATER)
						color = 2;
					else if (map.at(i).at(j) == HERO)
						color = 3;
					else if (map.at(i).at(j) == TREASURE)
						color = 4;
					else if (map.at(i).at(j) == MONSTER)
						color = 6;
					else if (map.at(i).at(j) == OPEN)
						color = 7;
					else if (map.at(i).at(j) == '+')
						color = 5;

					attron(COLOR_PAIR(color));
					mvaddch(i-start_y,j-start_x,map.at(i).at(j));
					attroff(COLOR_PAIR(color));
				}
			}
		}
	}
	Map(int x) {
		init_map();
		load_map(x);
	}
};
