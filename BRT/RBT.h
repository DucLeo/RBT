#pragma once
#include <iostream>
#include "Queue.h"
#include "List.h"
using namespace std;
enum class Color {
	RED,
	BLACK
};
template<class K, class V> class Element {
public:
	Color color;
	K key;
	V value;
	Element* parent;
	Element* left;
	Element* right;
	Element() {
		this->color = Color::RED;
		this->key = 0;
		this->value = 0;
		this->parent = NULL;
		this->left = NULL;
		this->right = NULL;
	};
};
template<class K, class V> class RBT {
public:
	Element<K, V>* root;
	Element<K, V>* nil;
	void leftRotate(Element<K, V>* X) {
		Element<K, V>* Y = X->right;
		X->right = Y->left;
		if (Y->left != nil) Y->left->parent = X;
		Y->parent = X->parent;
		if (X->parent == nil) root = Y;
		else {
			if (X == X->parent->left) X->parent->left = Y;
			else X->parent->right = Y;
		}

		X->parent = Y;
		Y->left = X;
	};
	void rightRotate(Element<K, V>* Y) {
		Element<K, V>* X = Y->left;
		Y->left = X->right;
		if (X->right != nil) X->right->parent = Y;
		X->parent = Y->parent;
		if (Y->parent == nil) root = X;
		else {
			if (Y == Y->parent->right) Y->parent->right = X;
			else Y->parent->left = X;
		}
		Y->parent = X;
		X->right = Y;
	};
	void fixupInsert(Element<K, V>* newNode) {
		while (newNode->parent->color == Color::RED) {
			if (newNode->parent == newNode->parent->parent->left) {
				Element<K, V>* Y = newNode->parent->parent->right;
				if (Y->color == Color::RED) {
					newNode->parent->color = Color::BLACK;
					Y->color = Color::BLACK;
					newNode->parent->parent->color = Color::RED;
					newNode = newNode->parent->parent;
				}
				else {
					if (newNode == newNode->parent->right) {
						newNode = newNode->parent;
						leftRotate(newNode);
					}
					newNode->parent->color = Color::BLACK;
					newNode->parent->parent->color = Color::RED;
					rightRotate(newNode->parent->parent);
				}
			}
			else {
				Element<K, V>* Y = newNode->parent->parent->left;
				if (Y->color == Color::RED) {
					newNode->parent->color = Color::BLACK;
					Y->color = Color::BLACK;
					newNode->parent->parent->color = Color::RED;
					newNode = newNode->parent->parent;
				}
				else {
					if (newNode = newNode->parent->left) {
						newNode = newNode->parent;
						rightRotate(newNode);
					}
					newNode->parent->color = Color::BLACK;
					newNode->parent->parent->color = Color::RED;
					leftRotate(newNode->parent->parent);
				}
			}
		}
		root->color = Color::BLACK;

	};
	void insert(K newKey, V newValue) {
		Element<K, V>* newNode = new Element<K, V>;
		newNode->key = newKey;
		newNode->value = newValue;
		newNode->left = nil;
		newNode->right = nil;
		Element<K, V>* X = root;
		Element<K, V>* Y = nil;
		while (X != nil) {
			Y = X;
			if (newNode->key == X->key) throw logic_error("This key is exist!");
			else if (newNode->key < X->key) X = X->left;
			else X = X->right;
		}
		newNode->parent = Y;
		if (Y == nil) {
			root = newNode;
		}
		else {
			if (newNode->key < Y->key) Y->left = newNode;
			else Y->right = newNode;
		}
		fixupInsert(newNode);
	};
	Element<K, V>* find(K key) {
		Element<K, V>* cur = root;
		while (cur != nil) {
			if (key < cur->key) cur = cur->left;
			else if (key > cur->key) cur = cur->right;
			else break;
		}
		if (cur->key == key) return cur;
		else throw invalid_argument("This key does not exist in the tree!");
	};
	void fixupRemove(Element<K, V>* X) {
		Element<K, V>* W;
		while (X != root && X->color != Color::BLACK) {
			if (X->parent->left = X) {
				W = X->parent->right;
				if (W->color == Color::RED) {
					W->color = Color::BLACK;
					X->parent->color = Color::RED;
					leftRotate(X->parent);
					W = X->parent->right;
				}
				else if (W->left->color == Color::BLACK && W->right->color ==

					Color::BLACK) {

					W->color = Color::RED;
					X = X->parent;
				}
				else if (W->right->color == Color::BLACK) {
					W->left->color = Color::BLACK;

					W->color = Color::RED;
					rightRotate(W);
					W = X->parent->right;
				}
				else {
					W->color = X->parent->color;
					X->parent->color = Color::BLACK;
					W->right->color = Color::BLACK;
					leftRotate(X->parent);
					X = root;
				}
			}
			else if (X->parent->right = X) {
				W = X->parent->left;
				if (W->color == Color::RED) {
					W->color = Color::BLACK;
					X->parent->color = Color::RED;
					rightRotate(X->parent);
					W = X->parent->left;
				}
				else if (W->left->color == Color::BLACK && W->right->color ==

					Color::BLACK) {

					W->color = Color::RED;
					X = X->parent;
				}
				else if (W->left->color == Color::BLACK) {
					W->right->color = Color::BLACK;
					W->color = Color::RED;
					leftRotate(W);
					W = X->parent->left;
				}
				else {
					W->color = X->parent->color;
					X->parent->color = Color::BLACK;
					W->left->color = Color::BLACK;
					rightRotate(X->parent);
					X = root;
				}
			}
			X->color = Color::BLACK;
		}
	};
	void remove(K keyToBeDeleted) {
		Element<K, V>* nodeToBeDeleted = find(keyToBeDeleted);
		Color originalColor = nodeToBeDeleted->color;
		Element<K, V>* x;
		if (nodeToBeDeleted->left == nil) {
			x = nodeToBeDeleted->right;
			delete nodeToBeDeleted->left;
			if (nodeToBeDeleted->parent->left == nodeToBeDeleted)
				nodeToBeDeleted->parent->left = x;
			else if (nodeToBeDeleted->parent->right == nodeToBeDeleted)
				nodeToBeDeleted->parent->right = x;
			x->parent = nodeToBeDeleted->parent;
		}
		else if (nodeToBeDeleted->right == nil) {
			x = nodeToBeDeleted->left;

			delete nodeToBeDeleted->right;
			if (nodeToBeDeleted->parent->left == nodeToBeDeleted)
				nodeToBeDeleted->parent->left = x;
			else if (nodeToBeDeleted->parent->right == nodeToBeDeleted)
				nodeToBeDeleted->parent->right = x;
			x->parent = nodeToBeDeleted->parent;
		}
		else {
			Element<K, V>* y = nodeToBeDeleted->right;
			while (y->left != nil) y = y->left;
			if (y == nodeToBeDeleted->right)
				originalColor = nodeToBeDeleted->color;
			else
				originalColor = y->color;
			x = y->right;
			if (y->parent == nodeToBeDeleted) {
				x->parent = y;
				y->left = nodeToBeDeleted->left;
				y->right = x;
			}
			else {
				if (y->parent->right == y)
					y->parent->right = x;
				else if (y->parent->left == y)
					y->parent->left = x;
				y->left = nodeToBeDeleted->left;
				y->right = nodeToBeDeleted->right;
			}
			if (nodeToBeDeleted->parent->right == nodeToBeDeleted)
				nodeToBeDeleted->parent->right = y;
			else if (nodeToBeDeleted->parent->left == nodeToBeDeleted)
				nodeToBeDeleted->parent->left = y;
			y->parent = nodeToBeDeleted->parent;
			y->color = originalColor;
		}
		if (originalColor == Color::BLACK) fixupRemove(x);
		delete nodeToBeDeleted;
	};
	Queue<Element<K, V>*>* allElementsByBFT() {
		Queue<Element<K, V>*>* mainQueue = new Queue<Element<K, V>*>;
		Queue<Element<K, V>*>* subQueue = new Queue<Element<K, V>*>;
		Element<K, V>* tmp = root;
		subQueue->enQueue(tmp);
		while (!subQueue->isEmpty()) {
			tmp = subQueue->deQueue();
			mainQueue->enQueue(tmp);
			if (tmp->left != nil) subQueue->enQueue(tmp->left);
			if (tmp->right != nil) subQueue->enQueue(tmp->right);
		}
		delete subQueue;
		return mainQueue;
	}
	void clear() {
		if (root == nil) throw logic_error("This tree is already empty!");
		else {
			Queue<Element<K, V>*>* subQueue = new Queue<Element<K, V>*>;

			Element<K, V>* tmp = root;
			subQueue->enQueue(tmp);
			while (!subQueue->isEmpty()) {
				tmp = subQueue->deQueue();
				if (tmp->left != nil) subQueue->enQueue(tmp->left);
				if (tmp->right != nil) subQueue->enQueue(tmp->right);
				delete tmp;
			}
			delete subQueue;
			root = nil;
		}
	};
	void print() {
		if (root == nil) cout << "This tree is empty!";
		else {
			Element<K, V>* tmp = nil;
			Queue<Element<K, V>*>* elements = allElementsByBFT();
			while (!elements->isEmpty()) {
				tmp = elements->deQueue();
				cout << "Key: " << tmp->key << " ,with values [" << tmp->value

					<< "]";

				if (!elements->isEmpty()) cout << ",\n";
			}
		}
	};
	List<K>* getKeys() {
		List<K>* keys = new List<K>;
		Queue<Element<K, V>*>* elements = allElementsByBFT();
		while (!elements->isEmpty()) {
			keys->pushback(elements->deQueue()->key);
		};
		delete elements;
		return keys;
	};
	List<V>* getValues() {
		List<V>* values = new List<V>;
		Queue<Element<K, V>*>* elements = allElementsByBFT();
		while (!elements->isEmpty()) {
			values->pushback(elements->deQueue()->value);
		};
		delete elements;
		return values;
	};
	RBT() {
		nil = new Element<K, V>();
		nil->color = Color::BLACK;
		root = nil;
	};
};