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
	
	 void push_back(shared_ptr<Actor> x) {
		Node* new_node = new Node(x, nullptr, tail); // new tail node whos prev is old tail and next is head node
		if (tail != nullptr) {  // if list is not empty, then the next tail is set to new node
			tail->next = new_node; 
		}
			tail = new_node; // else new node equal to tail
		
		if (head == nullptr) { // if list is empty then new node is equal to head 
			head = new_node;
		}
		head->prev = tail;
		tail->next = head;
	}

	void printLL() {
	    if (head != nullptr) { //checks if list is valid 
        Node* temp = head; // temp pointer is set to head  
        do {
            cout << temp->a->getName() << " " << endl; //prints the name of the current Actor that temps points too
            temp = temp->next; // make temp get the next node
        } while (temp != head); //checks until we reach the end of the circ linked list
        cout << endl;
    	}
	}
};
class Hero_linkedList {
        struct Node{
        //Actor *a; //holds a ptr to either a hero or monster?
        shared_ptr<Hero> a;
        Node *next = nullptr;
        Node *prev = nullptr;
        Node(shared_ptr<Hero> newa = nullptr, Node *new_next = nullptr, Node *new_prev = nullptr) : a(newa), next(new_next), prev(new_prev){}
        };
    public:
    Node *head = nullptr;
    Node *tail = nullptr;

    Hero_linkedList(){};

     void push_back(shared_ptr<Hero> x) {
        Node* new_node = new Node(x, nullptr, tail); // new tail node whos prev is old tail and next is head node
        if (tail != nullptr) {  // if list is not empty, then the next tail is set to new node
            tail->next = new_node;
        }
            tail = new_node; // else new node equal to tail

        if (head == nullptr) { // if list is empty then new node is equal to head
            head = new_node;
        }
        head->prev = tail;
        tail->next = head;
    }

    void printLL() {
        if (head != nullptr) { //checks if list is valid
        Node* temp = head; // temp pointer is set to head
        do {
            cout << temp->a->getName() << " " << endl; //prints the name of the current Actor that temps points too
            temp = temp->next; // make temp get the next node
        } while (temp != head); //checks until we reach the end of the circ linked list
        cout << endl;
        }
    }
};

class Monster_linkedList {
        struct Node{
        //Actor *a; //holds a ptr to either a hero or monster?
        shared_ptr<Monster> a;
        Node *next = nullptr;
        Node *prev = nullptr;
        Node(shared_ptr<Monster> newa = nullptr, Node *new_next = nullptr, Node *new_prev = nullptr) : a(newa), next(new_next), prev(new_prev){}
        };
    public:
    Node *head = nullptr;
    Node *tail = nullptr;

     Monster_linkedList(){};

     void push_back(shared_ptr<Monster> x) {
        Node* new_node = new Node(x, nullptr, tail); // new tail node whos prev is old tail and next is head node
        if (tail != nullptr) {  // if list is not empty, then the next tail is set to new node
            tail->next = new_node;
        }
            tail = new_node; // else new node equal to tail

        if (head == nullptr) { // if list is empty then new node is equal to head
            head = new_node;
        }
        head->prev = tail;
        tail->next = head;
    }

    void printLL() {
        if (head != nullptr) { //checks if list is valid
        Node* temp = head; // temp pointer is set to head
        do {
            cout << temp->a->getName() << " " << endl; //prints the name of the current Actor that temps points too
            temp = temp->next; // make temp get the next node
        } while (temp != head); //checks until we reach the end of the circ linked list
        cout << endl;
        }
    }
};
