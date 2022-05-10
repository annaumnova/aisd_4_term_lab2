#pragma once
#include <iostream>

template <typename VALUE>
class List {

	class Node { //L-1 list
	public:
		VALUE inf; //the information part of the beginning element
		Node* next;
	};
	int size;//size of list
	Node* head;//the pointer of the beginning
//	Node* end;//the pointer of the end

	void deleteHead() { //delete head
		if (head != NULL)
		{
			size--;
			Node* to_delete = head;
			to_delete = head;
			head = head->next;
			delete to_delete;
		}
		else
			throw std::out_of_range("List is empty");
	}

public:

	~List()//destructor
	{
		size = 0;
	}

	List() { //constructor
		head = NULL;
		size = 0;
	}

	VALUE getHead() { //get head
		if (size != 0)
			return head->inf;
		else
			throw std::out_of_range("Empty");
	}

	void setNext() { //to next
		if (head != NULL)
			head = head->next;
		else
			throw std::out_of_range("No next");
	}

	int getSize() { //get size
		return size;
	}

	void push(VALUE inf) { //add

		Node* new_node = new Node;
		new_node->inf = inf;
		new_node->next = NULL;
		size++;

		if (head == NULL) { //head?
			head = new_node;
			return;
		}

		Node* endCurr = head; //to the end
		while (endCurr->next != NULL)
			endCurr = endCurr->next;

		endCurr->next = new_node;
	}
};