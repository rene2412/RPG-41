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

	void push_back(Actor* actPtr){
		tail = new Node(actPtr, head,tail); // new tail node whos prev is old tail and next is head node
		if(head = nullptr){// if head is null ie: list is empty then head or prev's next is the new tail
			head = tail;
		}	
		tail->prev->next = tail;
		head->prev = tail;
	}
void printLL(){
	if(head != nullptr){
	Node* temp = head;
	cout << temp;
	temp = temp->next;
	while(temp != head){
		cout << temp;
		temp = temp->next;
		}
	}
}

};
