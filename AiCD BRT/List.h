#pragma once
#include <iostream>
using namespace std;

template<class T> class ElList {
public:
	T data;
	ElList* next;

	ElList() {
		this->data = 0;
		this->next = NULL;
	}
};

template<class T> class List {
public:
	ElList<T>* head;
	ElList<T>* tail;

	bool isEmpty() {
		if (head == NULL && tail == NULL) return true;
		else if (head != NULL && tail != NULL) return false;
		else throw logic_error("List is error!");
	}

	void pushback(T data) {
		ElList<T>* Node = new ElList<T>();
		Node->data = data;

		if (isEmpty()) {
			head = Node;
			tail = Node;
		}
		else {
			tail->next = Node;
			tail = Node;
		}
	}

	void pushfront(T data) {
		ElList<T>* Node = new ElList<T>();
		Node->data = data;

		if (isEmpty()) {
			head = Node;
			tail = Node;
		}
		else {
			Node->next = head;
			head = Node;
		}
	}

	void popback() {
		if (isEmpty()) throw logic_error("List is empty!");
		else {
			if (head == tail) {
				delete head;
				head = NULL;
				tail = head;
			}
			else {
				ElList<T>* cur = head;
				while (cur->next != tail) {
					cur = cur->next;
				}
				delete tail;
				tail = cur;
			}
		}
	}

	void popfront() {
		if (isEmpty()) throw logic_error("List is empty!");
		else {
			if (head == tail) {
				delete head;
				head = NULL;
				tail = head;
			}
			else {
				ElList<T>* tmp = head;
				head = tmp->next;
				delete tmp;
			}
		}
	}

	void clear() {
		ElList<T>* cur = head;
		while (cur != NULL) {
			cur = cur->next;
			delete head;
			head = cur;
		}
	}

	List() {
		this->head = NULL;
		this->tail = NULL;
	}
};