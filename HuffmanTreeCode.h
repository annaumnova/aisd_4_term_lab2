#pragma once
#include <iostream>
#include <stdio.h>
#include "Map.h"

//consts
const char sign = '\0';
const char zero = '0';
const char one = '1';

//template<typename T>
class HuffmanTreeCode {
private:
	//node
	class Node {
	public:
		char character; //the character
		size_t frequency; //the frequency which every character meet

		Node* left; //pointer to the leftChild
		Node* right; //pointer to the rightChild
		Node* parent; //the pointer to the parent

		//constructor
		Node(char character = sign, size_t frequency = 0, Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr) {
			this->character = character;
			this->frequency = 0;
			this->left = nullptr;
			this->right = nullptr;
			this->parent = nullptr;
		}

		//destructor
		~Node() {
			character = sign;
			frequency = 0;
			left = nullptr;
			right = nullptr;
			parent = nullptr;
		}
	};

	Node* root; //root
	size_t size; //size

	//help to clear tree
	void clearHelper(Node* node) {
		if (node != nullptr) {
			clearHelper(node->left);
			clearHelper(node->right);

			delete node;
			size--;
		}
		else return;
	}

	//get size of the tree
	size_t getSizeHuffmanTree() {
		return size;
	}

public:
	//constructor
	HuffmanTreeCode() {
		root = nullptr;
		size = 0;
	}
	//destructor
	~HuffmanTreeCode() {
		clearHuffmanTree();
	}

	//clear for destructor
	void clearHuffmanTree() {
		if (getSizeHuffmanTree() == 0)
			return;
		else {
			clearHelper(root);
			root = nullptr;
			size = 0;
		}
	}

	//get node
	Node* getNode(char ch, size_t frec, Node* left, Node* right) {
		Node* modernNode = new Node;

		modernNode->character = ch;
		modernNode->frequency = frec;
		modernNode->left = left;
		modernNode->right = right;

		return modernNode;
	}

	//build the node 
	Node* buildHuffmanTreeNode(char character, unsigned frequency) {
		Node* modern = new Node(character, frequency);
		size++;
		return modern;
	}

	//code
	//std::string encoded;
	//std::string encodeString() {
	//	return encoded;}

	//code characters in tree (0 - left subtree, 1 - right subtree)
	std::string codeChacters(Node* chCurr) {
		Node* previous = chCurr;
		std::string codes = "";
		
		while (chCurr->parent != nullptr) //it's parent?
		{
			previous = chCurr;
			chCurr = chCurr->parent; //parent

			if (chCurr->left == previous) //left subtree
				codes = zero + codes;
			else codes = one + codes; //right subtree
		}

		if (chCurr->parent== nullptr && chCurr->left == nullptr && chCurr->right == nullptr) //empty?
			codes = zero;
	
		return codes;
	}


	//decode
	std::string decodeString(std::string& encoded) {
		Node* current = root;
		std::string decoded = ""; //empty string

		for (int i = 0; encoded[i] != sign; i++) {
			if (getSizeHuffmanTree() > 1) { //string consists more than 1 character
				if (encoded[i] == zero) //== 0
					current = current->left; //-> left subtree
				else current = current->right; //->right subtree
			}

			if (current->character != sign) { //not '\0'
				decoded = decoded + current->character; //add character to decoded string
				current = root;
			}
		}
		return decoded;
	}


	//to form Huffman's tree
	//like List.h but another functions
	class List {

		class Element //Node 
		{
		public:

			Node* data; //the information part of the beginning element
			Element* next;

			Element(HuffmanTreeCode::Node* data = nullptr, Element* next = nullptr) { //costructor
				this->data = data;
				this->next = next;
			}

			~Element() { //destructor
				data = nullptr;
				next = nullptr;
			}
		};

		size_t size; //size of list
		Element* head; //the pointer of the beginning
		Element* end; //the pointer of the end

		//get head
		Element* getHead(){
			return head;
		}

		//get size
		size_t getSize() {
			return size;
		}

	public:

		List(size_t size = 0, Element* head = nullptr, Element* end = nullptr) { //costructor
			this->size = size;
			this->head = head;
			this->end = end;
		}
		
		~List() {//destructor
			clear();
			size = 0;
			head = nullptr;
			end = nullptr;
		}

		//clear
		void clear()
		{
			if (getSize() == 0) //already cleared
				return;
			else {
				Element* current = head;
				while (current != nullptr)
				{
					current = current->next;
					delete head;
					head = current;
				}
				head = nullptr;
				end = nullptr;
				size = 0;
			}
		}
		
		//sort nodes, bubble sort
		void sortListElements()
		{
				for (int i = 0; i < getSize(); i++)
				{
					for (Element* current = head; current->next != nullptr; current = current->next) {
						if (current->data->frequency < current->next->data->frequency) // previous < next
						{
							HuffmanTreeCode::Node* temporaryElement = current->data;
							current->data = current->next->data;
							current->next->data = temporaryElement;
						}
					}
				}
		}

		//nodes to list, form tree's new node (child + child = new parent)
		Node* formTree(HuffmanTreeCode& Tree) {
			Element* first = head;
			Element* second = head->next;
			int modernWeight;

			//count new parent's weight
			modernWeight = first->data->frequency + second->data->frequency;

			Node* modernNode = Tree.buildHuffmanTreeNode(sign, modernWeight);

			first->data->parent = modernNode;
			modernNode->left = first->data;

			second->data->parent = modernNode;
			modernNode->right = second->data;

			return modernNode;
		}


		//add 
		void push(Node* node) {
			
			if (head == nullptr) { //add to empty
				Element* modern = new Element(node, nullptr);
				head = modern;
				end = modern;
				size++;
			}
			else { //to not empty
				Element* modern = new Element(node, nullptr);
				end->next = modern;
				end = modern;
				size++;
			}
		}

		//delete
		Node* pop() {
			
			if (getSize() > 0) { //size of list > 0
				if (getSize() == 1) //lenght = 1 character
					clear();
				else {
					Element* current = head;
					head = head->next;
					size--;
					return current->data;
				}
			}
			else throw std::out_of_range("Empty");
		}
	};

	//print?????
	//void printHuffmanTree(){}
	//??copied??
};