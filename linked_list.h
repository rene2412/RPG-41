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
		//Actor *a; //holds a ptr to either a hero or monster?
		int a = 0;
		Node *next = nullptr;
		Node *prev = nullptr;
		Node(int newa = 0, Node *new_next = nullptr, Node *new_prev = nullptr) : a(newa), next(new_next), prev(new_prev){}
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

	void push_back(int x) {
		Node* new_node = new Node(x, nullptr, tail); // new tail node whos prev is old tail and next is head node
		if (tail != nullptr) {  // if list is not empty, then the next tail is set to new node
			tail->next = new_node; 
		}
			tail = new_node; // else new node equal to tail
		
		if (head == nullptr) { // if list is empty then new node is equal to head 
			head = new_node;
		}
	}
void printLL(){
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
