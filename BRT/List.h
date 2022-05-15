#pragma once
#pragma once
#include <iostream>
using namespace std;

template<class T> class EoList {   // Element of List
public:
	T data;
	EoList* prev;
	EoList* next;

	EoList() {
		this->data = 0;
		this->prev = NULL;
		this->next = NULL;
	}
};

template<class T> class List {
public:
	EoList<T>* head;
	EoList<T>* tail;
	size_t size;

	bool isEmpty() {
		if (head == NULL && tail == NULL) return true;
		else if (head != NULL && tail != NULL) return false;
		else throw logic_error("List is error!");
	}

	void pushback(T data) {
		EoList<T>* Node = new EoList<T>();
		Node->data = data;

		if (isEmpty()) {
			head = Node;
			tail = head;
		}
		else {
			Node->prev = tail;
			tail->next = Node;
			tail = Node;
		}

		size++;
	}

	void pushfront(T data) {
		EoList<T>* Node = new EoList<T>();
		Node->data = data;

		if (isEmpty()) {
			head = Node;
			tail = head;
		}
		else {
			head->prev = Node;
			Node->next = head;
			head = Node;
		}

		size++;
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
				EoList<T>* tmp = tail->prev;
				tmp->next = NULL;
				delete tail;
				tail = tmp;
			}
			size--;
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
				EoList<T>* tmp = head->next;
				tmp->prev = NULL;
				delete head;
				head = tmp;
			}

			size--;
		}
	}

	EoList<T>* find(T data) {
		EoList<T>* needNode = NULL;
		EoList<T>* cur = head;
		while (cur != NULL) {
			if (cur->data == data) {
				needNode = cur;
				break;
			}
			else cur = cur->next;
		}
		if (needNode == NULL) throw invalid_argument("No this node in list!");
		else return needNode;
	}

	void pop(T data) {
		EoList<T>* popNode = find(data);
		if (popNode == head) popfront();
		else if (popNode == tail) popback();
		else {
			popNode->prev->next = popNode->next;
			popNode->next->prev = popNode->prev;
			delete popNode;
		}

		size--;
	}

	EoList<T>* getIndex(size_t index) {
		if (head == NULL) throw logic_error("List is empty!");
		else {
			EoList<T>* needNode = head;
			if (index >= size) throw logic_error("Error index!");
			else {
				index++;
				while (index > 0) {
					needNode = needNode->next;
					index--;
				}
			}
			return needNode;
		}
	}
	void clear() {
		EoList<T>* cur = head;
		while (cur != NULL) {
			cur = cur->next;
			delete head;
			head = cur;
		}
		head = NULL;
		tail = NULL;
		size = 0;
	}

	List() {
		this->head = NULL;
		this->tail = NULL;
		this->size = 0;
	}
};
