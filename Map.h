#pragma once
// #.. -- the paragraph in the presentation
#include <stdio.h>
#include <iostream>
#include "List.h"
#include "Stack.h"

//consts
const int red = 1;
const int black = 0;

template <typename KEY, typename VALUE>
class Map {
private:
	//rbtree
	class RBtreeNode {
	public:
		KEY key; //the key
		VALUE value; //the value
		RBtreeNode* left; //the pointer to the leftChild
		RBtreeNode* right; //the pointer to the rightChild
		RBtreeNode* parent; //the pointer to the parent
		int color; //red=true=1 and black=false=0
	};

	RBtreeNode* root; //the root
	RBtreeNode* nil; //the nil (leaf)


	//left rorate
	void left_rotate(RBtreeNode* x_node) {
		RBtreeNode* y_node = x_node->right; //first tree: X(root)---Y(rightChild)
		x_node->right = y_node->left;

		//??????? #2
		if (y_node->left != nil)
			y_node->left->parent = x_node;
		y_node->parent = x_node->parent;

		//#3-5
		if (x_node->parent == nullptr)
			root = y_node;
		else if (x_node == x_node->parent->left)
			x_node->parent->left = y_node;
		else x_node->parent->right = y_node;

		//#6
		y_node->left = x_node;
		x_node->parent = y_node;
	}

	//right rorate
	void right_rotate(RBtreeNode* y_node) {
		RBtreeNode* x_node = y_node->left; //first tree: X(leftChild)---Y(root)
		y_node->left = x_node->right;

		//#2
		if (x_node->right != nil)
			x_node->right->parent = y_node;
		x_node->parent = y_node->parent;

		//#3-5
		if (y_node->parent == nullptr)
			root = x_node;
		else if (y_node == y_node->parent->right)
			y_node->parent->right = x_node;
		else y_node->parent->left = x_node;

		//#6
		x_node->right = y_node;
		y_node->parent = x_node;
	}

	//insert the new node and restore properties of rbtree (repaint, rorates)
	void insertNewNode(RBtreeNode* inserted_Newnode) {
		//RBtreeNode* p = inserted_Newnode->parent;
		//RBtreeNode* grandParent = p->parent;

		RBtreeNode* uncle; //parent's brother

		//repeate if parent has color red, p.1 slide 23
		while (inserted_Newnode->parent->color == red) { //red

			if (inserted_Newnode->parent == inserted_Newnode->parent->parent->right) {
				uncle = inserted_Newnode->parent->parent->left;
				//first case
				if (uncle->color == red) {
					uncle->color = black;
					inserted_Newnode->parent->color = black;
					inserted_Newnode->parent->parent->color = red;
					inserted_Newnode = inserted_Newnode->parent->parent;
				}

				//second case
				else {
					if (inserted_Newnode == inserted_Newnode->parent->left) {
						inserted_Newnode = inserted_Newnode->parent;
						right_rotate(inserted_Newnode);
					}

					inserted_Newnode->parent->color = black;
					inserted_Newnode->parent->parent->color = red;
					left_rotate(inserted_Newnode->parent->parent);
				}
			}
			else { //third case

				uncle = inserted_Newnode->parent->parent->right;

				if (uncle->color == red) {
					uncle->color = black;
					inserted_Newnode->parent->color = black;
					inserted_Newnode->parent->parent->color = red;
					inserted_Newnode = inserted_Newnode->parent->parent;
				}
				else {
					if (inserted_Newnode == inserted_Newnode->parent->right) {
						inserted_Newnode = inserted_Newnode->parent;
						left_rotate(inserted_Newnode);
					}

					inserted_Newnode->parent->color = black;
					inserted_Newnode->parent->parent->color = red;
					right_rotate(inserted_Newnode->parent->parent);
				}
			}

			if (inserted_Newnode == root)
				break;
		}
		root->color = black;
	}
	//remove the node and save rbtree's properties
	void removeNodeToBeDeleted(RBtreeNode* nodeToBeDeleted) { //nodeToBeDeleted = x
		RBtreeNode* w; // x's brother

		while (nodeToBeDeleted != root && nodeToBeDeleted->color == black) {

			if (nodeToBeDeleted == nodeToBeDeleted->parent->left) {
				w = nodeToBeDeleted->parent->right;

				//first case
				if (w->color == red) {
					w->color = black;
					nodeToBeDeleted->parent->color = red;
					left_rotate(nodeToBeDeleted->parent);
					w = nodeToBeDeleted->parent->right;
				}

				//second case
				if (w->left->color == black && w->right->color == black) { //black
					w->color = red;
					nodeToBeDeleted = nodeToBeDeleted->parent;
				}

				//third case
				else {
					if (w->right->color == black) {
						w->left->color = black;
						w->color = red;
						right_rotate(w);
						w = nodeToBeDeleted->parent->right;
					}

					w->color = nodeToBeDeleted->parent->color;
					nodeToBeDeleted->parent->color = black;
					w->right->color = black;
					left_rotate(nodeToBeDeleted->parent);
					nodeToBeDeleted = root;
				}
			}
			else { //x is rightChild
				w = nodeToBeDeleted->parent->left;

				//first case
				if (w->color == red) {
					w->color = black;
					nodeToBeDeleted->parent->color = red;
					right_rotate(nodeToBeDeleted->parent);
					w = nodeToBeDeleted->parent->left;
				}

				//second case
				if (w->left->color == black && w->right->color == black) { //black
					w->color = red;
					nodeToBeDeleted = nodeToBeDeleted->parent;
				}

				//third case
				else {
					if (w->left->color == black) {
						w->right->color = black;
						w->color = red;
						left_rotate(w);
						w = nodeToBeDeleted->parent->left;
					}

					w->color = nodeToBeDeleted->parent->color;
					nodeToBeDeleted->parent->color = black;
					w->left->color = black;
					right_rotate(nodeToBeDeleted->parent);
					nodeToBeDeleted = root;
				}

			}
		}
		nodeToBeDeleted->color = black;
	}

	//find tree, then find map
	RBtreeNode* findTree(RBtreeNode* node, KEY key) {
		if (key == node->key) //key matched with node
			return node;
		if (node == nil) //exist?
			throw std::out_of_range("it doesn't exist in this tree!");
		if (key < node->key) //the left subtree
			return findTree(node->left, key);
		return findTree(node->right, key);
	}

	//avoid C2248; make stack to delete
	void makeStackToDel(RBtreeNode* node, Stack<KEY>& stackDel) {
		if (node != nil) {
			stackDel.push_back(node->key);

			//left and right subtrees
			makeStackToDel(node->left, stackDel);
			makeStackToDel(node->right, stackDel);
		}
	}

	//replace nodes
	void replaceNodes(RBtreeNode* first, RBtreeNode* second) {
		if (first->parent == nullptr)
			root = second;
		else if (first == first->parent->left)
			first->parent->left = second;
		else
			first->parent->right = second;
		second->parent = first->parent;
	}

	//return list of keyes (helper)
	void get_keys(RBtreeNode* node, List<KEY>& listNode) {

		if (node != nil) {
			listNode.push(node->key);
			get_keys(node->left, listNode);
			get_keys(node->right, listNode);
		}
	}

	//return list of values (helper)
	void get_values(RBtreeNode* node, List<VALUE>& listNode) {

		if (node != nil) {
			listNode.push(node->value);
			get_values(node->left, listNode);
			get_values(node->right, listNode);
		}
	}

	//print tree, then print map
	void printTree(RBtreeNode* node, int indent = 0) {
		//indent = 0; //between parents and children, then +1
		if (node != nil) {
			printTree(node->left, indent + 1); //left subtree
			std::cout << "\n";
			for (int i = 0; i < indent; i++)
				std::cout << " ";
			std::cout << node->key;
			std::cout << " " << '(' << node->value << ')';

			std::cout << "\n ";
			printTree(node->right, indent + 1); //right subtree
		}
	}

public:
	//constructor
	Map() {
		nil = new RBtreeNode;
		root = nil;
		nil->color = black;
		nil->left = nullptr;
		nil->right = nullptr;

	}

	//destructor
	~Map() {
		clear();
	}

	//add the element with key and value
	void insert(KEY key, VALUE value) {

		RBtreeNode* inserted_NewNode = new RBtreeNode;

		//properties of new node
		inserted_NewNode->parent = nullptr;
		inserted_NewNode->color = red;
		inserted_NewNode->left = nil;
		inserted_NewNode->right = nil;
		inserted_NewNode->key = key;
		inserted_NewNode->value = value;

		RBtreeNode* x = root;
		RBtreeNode* y = nullptr; //???nullptr


		while (x != nil) { //empty?
			y = x;
			if (inserted_NewNode->key < x->key) //newKey < rootKey
				x = x->left;
			else
				x = x->right; //newKey < rootKey
		}
		inserted_NewNode->parent = y; //leaf's parent is parent of newNode

		if (y == nullptr) //empty tree?
			root = inserted_NewNode; // G(V = 1 = newNode, E = 0); 1 element
		else
			if (inserted_NewNode->key < y->key) //newKey < leafKey we got the rightChild
				y->left = inserted_NewNode;
			else
				y->right = inserted_NewNode; // we got the leftChild

		if (inserted_NewNode->parent == nullptr) { //root?
			inserted_NewNode->color = black;
			return;
		}

		if (inserted_NewNode->parent->parent == nullptr)
			return;

		insertNewNode(inserted_NewNode); //recover after insertion
	}

	//find the element with key
	RBtreeNode* find(KEY key) {
		return findTree(root, key);
	}

	//delete the element with key
	void remove(KEY key) {

		RBtreeNode* nodeToDel = nil;

		RBtreeNode* x;
		RBtreeNode* y;
		nodeToDel = find(key);
		y = nodeToDel;

		//origin color
		int originColor;
		originColor = y->color;

		if (nodeToDel->left == nil) { //#3 slide 31

			x = nodeToDel->right;

			//replace x and nodeToDel
			replaceNodes(nodeToDel, nodeToDel->right);
		}
		else if (nodeToDel->right == nil) { //#4

			x = nodeToDel->left;

			//replace x and nodeToDel
			replaceNodes(nodeToDel, nodeToDel->left);
		}
		else { //children are NOT NULL, #5 slide 34

			//the leftmost element in the right subtree
			y = nodeToDel->right;
			while (y->left != nil)
				y = y->left;

			originColor = y->color; //origin color

			x = y->right;

			if (y->parent == nodeToDel)
				x->parent = y;
			else {
				//replace y's rightChild to y
				replaceNodes(y, y->right);

				y->right = nodeToDel->right;
				y->right->parent = y;
			}

			//replace y and nodeToDel
			replaceNodes(nodeToDel, y);

			y->left = nodeToDel->left;
			y->left->parent = y;

			y->color = nodeToDel->color; //origin color
		}
		delete nodeToDel;

		if (originColor == black) //#6 slide 34
			removeNodeToBeDeleted(x);
	}

	//clear the map
	void clear() {
		Stack<KEY> stackDel;
		makeStackToDel(root, stackDel); //make stack, write in stack nodes and keys

		//clear operation
		while (stackDel.getSize()) {
			remove(stackDel.getTop());
			stackDel.pop();
		}
	}

	//get keys
	List<KEY> getKeys() {
		List<KEY> listKey;
		get_keys(root, listKey);
		return listKey;
	}

	//get values
	List<VALUE> getValues() {
		List<VALUE> listVal;
		get_values(root, listVal);
		return listVal;
	}

	//outputting
	void print() {
		return printTree(root);
	}
};