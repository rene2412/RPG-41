#pragma once
#include "actors.h"
#include <string>
#include <memory>
#include <vector>
using namespace std;
//vector <shared_ptr<Actor>> myList; //this holds our data for the linked list 

class linkedList {
	private:
		struct Node{
		Actor *a;
		Node *next = nullptr;
		Node *prev = nullptr;
		Node(Actor *newa = 0, Node *new_next = 0, Node *new_prev = 0) : a(newa), next(new_next), prev(new_prev){}
		};
	public:


};
