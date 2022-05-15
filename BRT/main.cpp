#include <iostream>
#include "RBT.h"
using namespace std;
int main() {
	RBT<int, int> tree;
	tree.insert(13, 5);
	tree.insert(8, 2);
	tree.insert(17, 12);
	tree.insert(1, 4);
	tree.insert(11, 8);
	tree.insert(15, 7);
	tree.insert(25, 22);
	tree.insert(5, 8);
	tree.insert(22, 9);
	tree.insert(27, 10);
	cout << "Red Black Tree:\n";
	tree.print();
	cout << ".\n\nList of keys: ";
	List<int>* keys = tree.getKeys();
	EoList<int>* cur = keys->head;
	while (cur != NULL) {
		cout << cur->data;
		cur = cur->next;
		if (cur != NULL) cout << ", ";
	}
	cout << ".\n\nList of values: ";
	List<int>* values = tree.getValues();
	cur = values->head;
	while (cur != NULL) {
		cout << cur->data;
		cur = cur->next;
		if (cur != NULL) cout << ", ";
	}
	cout << ".\n\nTree after remove 8 and 22:\n";
	tree.remove(8);
	tree.remove(22);
	tree.print();
	tree.clear();
	cout << endl;
}