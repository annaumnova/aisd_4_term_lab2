#pragma once
#include <iostream>

template <typename KEY>
class Stack
{
private:
	class Element
	{
	public:
		KEY data;
		Element* previous;

		Element(const int element) //constructor
		{
			this->data = element;
			previous = 0;
		}
	};
	Element* top_element;
	size_t size;

public:

	Stack()//constructor
	{
		this->top_element = 0;
		size = 0;
	}

	~Stack()//destructor
	{
		while (top_element)
			pop();
	}

	KEY getTop() //get top
	{
		return top_element->data;
	}


	bool isEmpty()//check the emptiness
	{
		return !size;
	}

	size_t getSize()//get size
	{
		return size;
	}

	void push_back(const KEY element)//add to the end
	{
		Element* buffer = top_element;
		top_element = new Element(element);
		top_element->previous = buffer;
		size++;
	}

	void pop() //remove top
	{
		if (size) {
			Element* temp = top_element->previous;
			delete top_element;
			top_element = temp;
			size--;
		}
		else
			throw std::out_of_range("Empty!");
	}
};
