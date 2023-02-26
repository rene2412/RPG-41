#pragma once
#include "actors.h"
#include <string>
#include <memory>
#include <vector>
using namespace std;
//vector <shared_ptddr<Actor>> myList; //this holds our data for the linked list 

class linkedList {
		struct Node{
		//Actor *a; //holds a ptr to either a hero or monster?
		shared_ptr<Actor> a;
		Node *next = nullptr;
		Node *prev = nullptr;
		Node(shared_ptr<Actor> newa = nullptr, Node *new_next = nullptr, Node *new_prev = nullptr) : a(newa), next(new_next), prev(new_prev){}
		};
	public:
	Node *head = nullptr;
	Node *tail = nullptr;

	 linkedList(){};
	~linkedList(){
		while (head){
		Node* temp = head->next;
		delete head;
		head = temp;
		}
	}

	void push_back(shared_ptr<Actor> x) {
		Node* new_node = new Node(x, nullptr, tail); // new tail node whos prev is old tail and next is head node
		if (tail != nullptr) {  // if list is not empty, then the next tail is set to new node
			tail->next = new_node; 
		}
			tail = new_node; // else new node equal to tail
		
		if (head == nullptr) { // if list is empty then new node is equal to head 
			head = new_node;
		}
	}

	void printLL() {
	if(head != nullptr) { // checks if the head pointer is pointing to a valid memory address, in basic terms checking if list is not empty so it can do stuff
	Node* temp = head; // temp ptr it set to head
	cout << temp-> a << " "; // prints out the temp value which is the head (first point of list), and gets the variable of a
	temp = temp->next; // temp is now set to the next node
	while(temp != nullptr) { 
		cout << temp->a << " ";
		temp = temp->next;
		}
		cout << endl;
	}
}
	
};

	 void all_linkedlist (vector<shared_ptr<Actor>> &all, linkedList &list) {
        for (const auto &everything : all) {
            list.push_back(everything);
        }
    }


